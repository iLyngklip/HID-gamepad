//##############################################
//#  DEBUGGING SETTINGS                        #
//##############################################
#define DEBUG 0

//##############################################
//#  Serial SETTINGS                           #
//##############################################
#define INTERNAL_BAUDRATE 2000000
#define NUMBER_OF_BYTES   17
    //-----------------------------------------|
    // Messages                                |
    //-----------------------------------------|
    #define OK_MSG    0xFF
    #define CFG_MSG   0xFE
    #define END_MSG   0xFD

//##############################################
//#  General SETTINGS                          #
//##############################################    
#define UPDATE_INTERVAL_MS  500

//##############################################
//#  Includes                                  #
//##############################################
#include <HID-Project.h>
#include <HID-Settings.h>


//##############################################
//#  Global variables                          #
//##############################################
uint16_t timeHolder = 0;


void setup() {
  Serial1.begin(INTERNAL_BAUDRATE);
  Gamepad.begin();
}// Setup

void loop() {
  
  if(millis() - timeHolder < UPDATE_INTERVAL_MS){
    Serial1.print(OK_MSG);
    
    // Wait for data to be sent
    while(Serial1.available() <= NUMBER_OF_BYTES);
    
    uint16_t temp = 0;
    temp |= Serial.read() << 8;
    temp |= Serial.read();
    Gamepad.xAxis(temp);
    temp = 0x00;
  
    temp |= Serial.read() << 8;
    temp |= Serial.read();
    Gamepad.yAxis(temp);
    temp = 0x00;
    
  }
}// Loop





