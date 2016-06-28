/*###################################################*/
/*#                                                 #*/
/*#   Software for the 32u2                         #*/
/*#   To actually make the gamepad work             #*/
/*#                                                 #*/
/*###################################################*/


// ----------------------------------------------------
// Debug settings -------------------------------------
#define DEBUG 1
#define INTERNAL_BAUDRATE_DEBUG 9600

// ----------------------------------------------------
// Serial settings ------------------------------------
#define INTERNAL_BAUDRATE 9600

    //-----------------------------------------|
    // Messages                                |
    //-----------------------------------------|
    #define OK_MSG    0xFF
    #define CFG_MSG   0xFE
    #define END_MSG   0xFD

// ----------------------------------------------------
// General settings -----------------------------------   
#define UPDATE_INTERVAL_MS        500
#define NUMBER_OF_BUTTONS_IN_USE  10

// ----------------------------------------------------
// Includes -------------------------------------------
#if DEBUG == 0
  #include <HID-Project.h>
  #include <HID-Settings.h>
#endif

// ----------------------------------------------------
// Global variables -----------------------------------
uint16_t timeHolder = 0;

<<<<<<< HEAD
uint8_t numberOfBytesToExpect = 8;

=======

uint8_t numberOfBytesToExpect = 2; // Define number of bytes to expect
>>>>>>> origin/master





void setup() {
  #if DEBUG
    Serial.begin(INTERNAL_BAUDRATE_DEBUG);
    Serial.print("Hello world!");
    delay(2000);
  #else
    Serial1.begin(INTERNAL_BAUDRATE);
  #endif

  #if DEBUG == 0
    Gamepad.begin();
  #endif
<<<<<<< HEAD

  // Add routine to set a new value for "numberOfBytesToExpect"!
  
  
  
  readDataFromSerial();
=======
>>>>>>> origin/master
}// Setup







void loop() {
<<<<<<< HEAD
    #if DEBUG

readDataFromSerial();
      
    #else
  
    Serial1.write(OK_MSG);
    
    // Wait for ALL the data to be sent
    while(Serial1.available() < NUMBER_OF_BYTES){ delay(1) };
    
    uint16_t temp = 0;
    // Get the most significant byte
    temp |= Serial1.read() << 8;    
    // Least significant
    temp |= Serial1.read();    
    // Store it
    Gamepad.xAxis(temp);

    // Clear temp
    temp = 0x00;
  
    temp |= Serial1.read() << 8;
    temp |= Serial1.read();
    Gamepad.yAxis(temp);
    temp = 0x00;

    // End the DEBUG case
    #endif 
=======


  // Send I'm rdy msg
  Serial.write(OK_MSG);


  // Wait for the whole msg to arraive
  while(Serial.available() < numberOfBytesToExpect);
  while(Serial.read() != OK_MSG);

// Read axis
  // X-axis
  uint16_t tempAxisVariable = 0x0000;
  tempAxisVariable |= Serial.read() << 8;
  tempAxisVariable |= Serial.read();
  #if DEBUG == 0
    Gamepad.xAxis = tempAxisVariable;
  #else
    Serial.write(tempAxisVariable >> 8);
    Serial.write(tempAxisVariable);
    Serial.write(0x00);
  #endif


  // Y-axis
  tempAxisVariable = 0x0000;
  tempAxisVariable |= Serial.read() << 8;
  tempAxisVariable |= Serial.read();
  #if DEBUG == 0
    Gamepad.yAxis = tempAxisVariable;
  #else
    Serial.write(tempAxisVariable >> 8);
    Serial.write(tempAxisVariable);
    Serial.write(0x00);
  #endif


  // Z-axis
  tempAxisVariable = 0x0000;
  tempAxisVariable |= Serial.read() << 8;
  tempAxisVariable |= Serial.read();
  #if DEBUG == 0
    Gamepad.zAxis = tempAxisVariable;
  #else
    Serial.write(tempAxisVariable >> 8);
    Serial.write(tempAxisVariable);
    Serial.write(0x00);
  #endif



  // Buttons - 10 stk.
  
  
>>>>>>> origin/master



    
    // Now we wait for update interval
    delay(UPDATE_INTERVAL_MS);
}// Loop

void readDataFromSerial(){
  #if DEBUG
      Serial.write(OK_MSG);
      // Wait for ALL the data to be sent
      while(Serial.available() < numberOfBytesToExpect);
      
      // An OK_MSG should be the first byte
      while(Serial.read() != OK_MSG);

      
      uint16_t temp = 0;

    // X-axis
      temp |= Serial.read() << 8;
      // Serial.print("Temp << 8: ");
      // Serial.print(temp);
      
      temp |= Serial.read();
      // Serial.print("Temp total: ");
      // Serial.print(temp);
      
      // Gamepad.xAxis(temp);
      temp = 0x00;
      
    // Y-axis
      temp |= Serial.read() << 8;
      temp |= Serial.read();
      // Gamepad.yAxis(temp);
      temp = 0x00;

    // Z-axis
      temp |= Serial.read() << 8;
      temp |= Serial.read();
      // Gamepad.zAxis(temp);
      temp = 0x00;


      uint8_t temp2;
      temp2 |= Serial.read();
      if(temp2 == END_MSG){
        // Success, all data recieved
          // Serial.println("DILLERMIS");
          Serial.write(0xAA);
      } else {
        // We need to fetch new data!
        // Serial.println("NOPW!");
        // Serial.print("I Read: ");
        Serial.write(0xBB);
      }
      #endif
}














