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


uint8_t numberOfBytesToExpect = 6; // Define number of bytes to expect





void setup() {
  #if DEBUG
    Serial.begin(INTERNAL_BAUDRATE_DEBUG);
    // Serial.print("Hello world!");
    // delay(2000);
  #else
    Serial1.begin(INTERNAL_BAUDRATE);
  #endif

  #if DEBUG == 0
    Gamepad.begin();
  #endif
}// Setup




#if DEBUG == 1
  uint16_t xAxisVar = 0;
  uint16_t yAxisVar = 0;
  uint16_t zAxisVar = 0;
#endif



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
    xAxisVar = tempAxisVariable;
  #endif


  // Y-axis
  tempAxisVariable = 0x0000;
  tempAxisVariable |= Serial.read() << 8;
  tempAxisVariable |= Serial.read();
  #if DEBUG == 0
    Gamepad.yAxis = tempAxisVariable;
  #else
    yAxisVar = tempAxisVariable;
  #endif


  // Z-axis
  tempAxisVariable = 0x0000;
  tempAxisVariable |= Serial.read() << 8;
  tempAxisVariable |= Serial.read();
  #if DEBUG == 0
    Gamepad.zAxis = tempAxisVariable;
  #else
    zAxisVar = tempAxisVariable;
  #endif



  // Buttons - 10 stk.
  
  

    delay(500);
    repeat();
    
    // Now we wait for update interval
    delay(UPDATE_INTERVAL_MS);
}// Loop




void repeat(){
  Serial.write(xAxisVar >> 8);
  Serial.write(xAxisVar);
  
  Serial.write(yAxisVar >> 8);
  Serial.write(yAxisVar);

  Serial.write(zAxisVar >> 8);
  Serial.write(zAxisVar);
  
}











