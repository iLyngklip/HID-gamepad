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
#define NUMBER_OF_BYTES   17
    //-----------------------------------------|
    // Messages                                |
    //-----------------------------------------|
    #define OK_MSG    0xFF
    #define CFG_MSG   0xFE
    #define END_MSG   0xFD

// ----------------------------------------------------
// General settings -----------------------------------   
#define UPDATE_INTERVAL_MS  500

// ----------------------------------------------------
// Includes -------------------------------------------
#if DEBUG == 0
  #include <HID-Project.h>
  #include <HID-Settings.h>
#endif

// ----------------------------------------------------
// Global variables -----------------------------------
uint16_t timeHolder = 0;








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
    #if DEBUG
      Serial.print(OK_MSG);
      // Wait for ALL the data to be sent
      while(Serial.available() <= NUMBER_OF_BYTES);
      
      uint16_t temp = 0;
      temp |= Serial.read() << 8;
      Serial.print("Temp << 8: ");
      Serial.print(temp);
      
      temp |= Serial.read();
      Serial.print("Temp total: ");
      Serial.print(temp);
      
      // Gamepad.xAxis(temp);
      temp = 0x00;
    
      temp |= Serial.read() << 8;
      temp |= Serial.read();
      // Gamepad.yAxis(temp);
      temp = 0x00;
  

      Serial.println();
      Serial.println();
    #else
  
    Serial1.print(OK_MSG);
    
    // Wait for ALL the data to be sent
    while(Serial1.available() <= NUMBER_OF_BYTES);
    
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



    
    // Now we wait for update interval
    delay(UPDATE_INTERVAL_MS);
}// Loop





