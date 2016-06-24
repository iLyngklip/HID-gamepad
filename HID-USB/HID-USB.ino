#define DEBUG 0

#define OK_MSG  0xFF


#include <HID-Project.h>
#include <HID-Settings.h>

#define UPDATE_INTERVAL_MS  500

uint16_t timeHolder = 0;


void setup() {
  // put your setup code here, to run once:

  Serial1.begin(2000000);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(millis() - timeHolder < UPDATE_INTERVAL_MS){
    Serial1.print(OK_MSG);
    // Wait for data to be sent
    while(Serial1.available() <= 0){}
    
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
}
