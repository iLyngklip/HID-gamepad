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
#define INTERNAL_BAUDRATE 2000000
#define NUMBER_OF_BYTES   17
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


uint8_t numberOfBytesToExpect = 2; // Define number of bytes to expect





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
}// Setup







void loop() {


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
  
  



    
    // Now we wait for update interval
    delay(UPDATE_INTERVAL_MS);
}// Loop
















