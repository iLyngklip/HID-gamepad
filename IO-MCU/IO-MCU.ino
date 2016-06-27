/*###################################################*/
/*#                                                 #*/
/*#   Software for the 2560                         #*/
/*#   For collection data and sending it to 32u2    #*/
/*#                                                 #*/
/*###################################################*/
// ----------------------------------------------------
// General settings -----------------------------------
  // Gamepad mode
    #define USB_MODE  1
      // See "Defines for readability"

  // Input settings
    // Axis
      #define NUMBER_OF_AXIS                3
      #define USE_INTERNAL_PULLUP_ON_AXIS   0

      
    // Buttons
    #define NUMBER_OF_BUTTONS 10

    // Axis resolution
      #define AXIS_RESOLUTION 1024
        // This equals 16 bit

// ----------------------------------------------------
// Pin definetions ------------------------------------

  // Axis
    #define X_AXIS_PIN  0
    #define Y_AXIS_PIN  1
    #define Z_AXIS_PIN  2

  // Buttons
    // Buttons
      #define BUTTON_1    1
      #define BUTTON_2    2
      #define BUTTON_3    3
      #define BUTTON_4    4
      #define BUTTON_5    5
      #define BUTTON_6    6
      #define BUTTON_7    7
      #define BUTTON_8    8
      #define BUTTON_9    9
      #define BUTTON_10   10
      
      #define BUTTON_11   11
      #define BUTTON_12   12
      #define BUTTON_13   13
      #define BUTTON_14   14
      #define BUTTON_15   15
      #define BUTTON_16   16
      #define BUTTON_17   17
      #define BUTTON_18   18
      #define BUTTON_19   19
      #define BUTTON_20   20
      
      #define BUTTON_21   21
      #define BUTTON_22   22
      #define BUTTON_23   23
      #define BUTTON_24   24
      #define BUTTON_25   25
      #define BUTTON_26   26
      #define BUTTON_27   27
      #define BUTTON_28   28
      #define BUTTON_29   29
      #define BUTTON_30   30
      
      #define BUTTON_31   31
      #define BUTTON_32   32
  
  
  
// ----------------------------------------------------
// Debug settings -------------------------------------
#define DEBUG 1

// ----------------------------------------------------
// Serial settings ------------------------------------
#define INTERNAL_BAUDRATE 9600
  // Messages
    #define OK_MSG    0xFF
    #define CFG_MSG   0xFE
    #define END_MSG   0xFD


// ----------------------------------------------------
// Readablility ---------------------------------------

  // - USB modes
    #define GAMEPAD   1
  /*  NOT CURRENTLY USEABLE MODES 
    #define KEYBOARD  2
    #define MOUSE     3
  */

    
  // Data handlers
    // Axis
      #define LOCAL_X_AXIS  0
      #define LOCAL_Y_AXIS  1
      #define LOCAL_Z_AXIS  2

    
      
      
  
    

// ----------------------------------------------------
// Includes -------------------------------------------



// ----------------------------------------------------
// Global variables -----------------------------------
struct gamePadData{
  uint16_t _xAxis = 0;
  uint16_t _yAxis = 0;
  uint16_t _zAxis = 0;

  uint32_t _buttons = 0;
} gamePadData;













void setup() {
  // Initialize the connection to the USB-MCU
  Serial.begin(INTERNAL_BAUDRATE);

  #if DEBUG
    Serial.println("Hello world!");
  #endif



  #if USE_INTERNAL_PULLUP_ON_AXIS
    pinMode(X_AXIS_PIN, INPUT_PULLUP);
    pinMode(Y_AXIS_PIN, INPUT_PULLUP);
    pinMode(Z_AXIS_PIN, INPUT_PULLUP);
  #else
    pinMode(X_AXIS_PIN, INPUT);
    pinMode(Y_AXIS_PIN, INPUT);
    pinMode(Z_AXIS_PIN, INPUT);
  #endif
  
  
  
  // setAxis(LOCAL_X_AXIS, random(0, 0xFF));
} // setup





void loop() {

  // Check if it's time to send the data
  if(Serial.available() > 0){
    // Check if it's actually time to send
    if(Serial.read() == OK_MSG){
      // Send data!
      sendData();
    }
  } else {
    // It's not time to send data.
    // So let's collect data!
    collectData();
    
  }// if else


}// Loop





// ----------------------------------------------------
// Data Collectors ------------------------------------
void collectData(){
  /*
   * This function is for:
   *      Collection data
   *      It does so by calling the
   *      corresponding functions
   *    
   * 
   * Parameters:
   *      None
   *      
   * Returns:
   *      None
   */  
  getAxisData();
  getButtonData();
  getDPadData();
}

void getAxisData(){
  /*
   * This function is for:
   *      Collecting ALL Axis-positions
   *    
   * 
   * Parameters:
   *      None
   *      
   * Returns:
   *      None
   */  

  // Reading and mapping analog value
  gamePadData._xAxis = map(analogRead(X_AXIS_PIN), 0, 1024, 0, AXIS_RESOLUTION);
  gamePadData._yAxis = map(analogRead(Y_AXIS_PIN), 0, 1024, 0, AXIS_RESOLUTION);
  gamePadData._zAxis = map(analogRead(Z_AXIS_PIN), 0, 1024, 0, AXIS_RESOLUTION);
   
}

void getButtonData(){
  /*
   * This function is for:
   *      Reading the button-pins for presses. 
   *    
   * 
   * Parameters:
   *      None
   *      
   * Returns:
   *      None
   */  


   for(int i = 1; i < NUMBER_OF_BUTTONS; i++){
    // Read a button corresponding to "i"
    if(digitalRead(i)){
      // The pin is HIGH = not pressed
      // Set the bit to "0"
      bitClear(gamePadData._buttons, i);
    } else {
      // the pin is LOW = pressed
      // Set the bit to "1"
      bitSet(gamePadData._buttons, i);
    }
   }
}

void getDPadData(){
  /*
   * This function is for:
   *      
   *    
   * 
   * Parameters:
   *      
   *      
   * Returns:
   *      
   */  
}





// ----------------------------------------------------
// Data handlers --------------------------------------
void setAxis(byte axis, uint16_t data){
  /*
   * This function is for:
   *      Setting different analogue values
   *      to the variables.
   *    
   * 
   * Parameters:
   *      axis  - Defined name of the axis
   *      data  - Two bytes of unsigned data
   *      
   * Returns:
   *      None
   */

   
  switch(axis){
    case LOCAL_X_AXIS:
      gamePadData._xAxis = data;
      break;

    case LOCAL_Y_AXIS:
      gamePadData._yAxis = data;
      break;

    case LOCAL_Z_AXIS:
      gamePadData._zAxis = data;
      break;


    default:
      break;
  } // switch
}// setAxis


// ----------------------------------------------------
// Byte sending ---------------------------------------
void sendData(){
  /*
   * This function is for:
   *      Sending all the data of the gamecontroller
   *      to the USB_MCU
   *    
   * 
   * Parameters:
   *      None
   *      
   * Returns:
   *      None
   */

  // Let the 32u2 know data is comming
  Serial.write(OK_MSG);

   
  // Send axis data
  sendTwoUnsignedBytes(gamePadData._xAxis); // X
  sendTwoUnsignedBytes(gamePadData._yAxis); // Y
  sendTwoUnsignedBytes(gamePadData._zAxis); // Z


  // Let the 32u2 know we are done sending
  Serial.write(END_MSG);
}


void sendTwoUnsignedBytes(uint16_t data){
  /*
   * This function is for:
   *      Sending two bytes of data over serial
   *    
   * 
   * Parameters:
   *      uint16_t  The data
   *      
   * Returns:
   *      None
   */

   
  uint16_t mask   = B11111111;       
  uint8_t first_half   = data >> 8;  
  uint8_t sencond_half = data & mask;

  Serial.write(first_half);
  Serial.write(sencond_half);
} // sendTwoBytes


void sendOneUnsignedByte(uint8_t data){
  /*
   * This function is for:
   *      Just for writing one byte to serial
   *      It's more readable this way.
   *    
   * 
   * Parameters:
   *      uint8_t One byte of data
   *      
   * Returns:
   *      None
   */

   
  Serial.write(data);
}



/* TEMPLATE-FUNCTION
 

type functionNameInOneWord(type parameter1, type parameter2){
  /*
   * This function is for:
   *    Short description of the function
   *    
   * 
   * Parameters:
   *      Which parameters does it take?
   *      
   * Returns:
   *      What do it return?
   */

/*
}


*/   






