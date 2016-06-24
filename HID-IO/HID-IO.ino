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

  // something else


  
// ----------------------------------------------------
// Debug settings -------------------------------------
#define DEBUG 0

// ----------------------------------------------------
// Serial settings ------------------------------------
#define INTERNAL_BAUDRATE 2000000
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
} gamePadData;













void setup() {
  // Initialize the connection to the 32u2
  Serial.begin(INTERNAL_BAUDRATE);


  setAxis(LOCAL_X_AXIS, random(0, 0xFF));
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
   *      Collection Axis-positions
   *    
   * 
   * Parameters:
   *      None
   *      
   * Returns:
   *      None
   */  
}

void getButtonData(){
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






