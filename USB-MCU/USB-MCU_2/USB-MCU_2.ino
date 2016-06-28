
#define DEBUG 0

#if DEBUG == 0
  #include <HID-Project.h>
  #include <HID-Settings.h>
#endif

    #define OK_MSG    0xFF
    #define CFG_MSG   0xFE
    #define END_MSG   0xFD

uint8_t bytesOfDataToExpect = 6;  // The number of data-bytes
                                  //  EXCLUSIVE head and tail

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(9600);
  Serial.begin(9600);

  Gamepad.begin();
}

void loop() {
  // IO-MCU
  if(Serial1.available() > 0){
    do{
      Serial.write(Serial1.read());
    } while(Serial1.available() > 0);
  }

/*
  // COMPUTER
  if(Serial.available() > 0){
    do{
      Serial1.write(Serial.read());
    }while(Serial.available());
  }


*/
  collectData();
  Gamepad.write();
  delay(20);
  
  
}


void collectData(){
  // Ask for data
  Serial1.write(OK_MSG);

  
  // Wait for the buffer to be filled
  while(Serial1.available() != bytesOfDataToExpect + 2) delay(1);
  if(Serial1.read() == OK_MSG){
    Serial.println("collectData: Got OK!");
  }
  uint16_t tempAxisVal = 0;
  
  tempAxisVal |= Serial1.read() << 8;
  tempAxisVal |= Serial1.read();
  Gamepad.xAxis(tempAxisVal);

  tempAxisVal = 0;
  tempAxisVal |= Serial1.read() << 8;
  tempAxisVal |= Serial1.read();
  Gamepad.yAxis(tempAxisVal);

  tempAxisVal = 0;
  tempAxisVal |= Serial1.read() << 8;
  tempAxisVal |= Serial1.read();
  Gamepad.zAxis(tempAxisVal);

  if(Serial1.read() == END_MSG){
    Serial.println("collectData: Got End");
  }
  
}

