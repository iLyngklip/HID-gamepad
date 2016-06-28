//
//  main.cpp
//  ProgramForTesting
//
//  Created by Mathias Lyngklip Kjeldgaard on 28/06/2016.
//
//

#include <iostream>
#include <stdio.h>    /* Standard input/output definitions */
#include <stdlib.h>
#include <stdint.h>   /* Standard types */
#include <string.h>   /* String function definitions */
#include <unistd.h>   /* UNIX standard function definitions */
#include <fcntl.h>    /* File control definitions */
#include <errno.h>    /* Error number definitions */
#include <termios.h>  /* POSIX terminal control definitions */
#include <sys/ioctl.h>
#include <getopt.h>
#include <chrono>

using namespace std;

int fd;
int numberOfTimesRan = 0;


#define NUMBER_OF_TESTS 100
#define OK_MSG          0xFF
#define END_MSG         0xFD






bool initPort(const char *serialport, int baud);
uint8_t readInt();
uint16_t    readLongInt();


void writeInt(uint8_t val){
    write(fd, &val, 1);
    usleep(5 * 1 * 1000); // Aparrently we have to wait for the port to do stuff...
}




uint8_t dataToSend[] = {0xFF, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06};



int main() {
    initPort("/dev/tty.usbmodem1421", 9600);
    cout << "Hello world!" << endl;
    while(numberOfTimesRan < NUMBER_OF_TESTS){
        if(readInt() == OK_MSG){
            cout << "Got OK" << endl;
            for(int i = 0; i <= sizeof(dataToSend); i++){
                writeInt(dataToSend[i]);
                cout << "Writing" << endl;
                
            }
            usleep(500);
            for(int i = 0; i <= sizeof(dataToSend); i++){
                cout << "listening" << endl;
                uint8_t temp = readInt();
                if(temp == dataToSend[i]){
                    cout << "Got it" << endl;
                } else {
                    cout << "nope, i got: " << temp << endl;
                }
            }
            
            numberOfTimesRan++;
        } else {
            // Do nothing...
        };
        
    }
    
    
    
}


bool initPort(const char *serialport, int baud){
    struct termios toptions;
    
    //fprintf(stderr,"init_serialport: opening port %s @ %d bps\n",
    //        serialport,baud);
    
    fd = open(serialport, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1)  {
        perror("init_serialport: Unable to open port ");
        return -1;
    }
    
    if (tcgetattr(fd, &toptions) < 0) {
        perror("init_serialport: Couldn't get term attributes");
        return -1;
    }
    speed_t brate = baud; // let you override switch below if needed
    switch(baud) {
        case 4800:   brate=B4800;   break;
        case 9600:   brate=B9600;   break;
#ifdef B14400
        case 14400:  brate=B14400;  break;
#endif
        case 19200:  brate=B19200;  break;
#ifdef B28800
        case 28800:  brate=B28800;  break;
#endif
        case 38400:  brate=B38400;  break;
        case 57600:  brate=B57600;  break;
        case 115200: brate=B115200; break;
    }
    cfsetispeed(&toptions, brate);
    cfsetospeed(&toptions, brate);
    
    // 8N1
    toptions.c_cflag &= ~PARENB;
    toptions.c_cflag &= ~CSTOPB;
    toptions.c_cflag &= ~CSIZE;
    toptions.c_cflag |= CS8;
    // no flow control
    toptions.c_cflag &= ~CRTSCTS;
    
    toptions.c_cflag |= CREAD | CLOCAL;  // turn on READ & ignore ctrl lines
    toptions.c_iflag &= ~(IXON | IXOFF | IXANY); // turn off s/w flow ctrl
    
    toptions.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // make raw
    toptions.c_oflag &= ~OPOST; // make raw
    
    // see: http://unixwiz.net/techtips/termios-vmin-vtime.html
    toptions.c_cc[VMIN]  = 0;
    toptions.c_cc[VTIME] = 20;
    
    if( tcsetattr(fd, TCSANOW, &toptions) < 0) {
        perror("init_serialport: Couldn't set term attributes");
        return false;
    }
    return true;
}

uint16_t readLongInt(){
    uint16_t tempInt;
    tempInt |= readInt() << 8;
    tempInt |= readInt();
    
    return tempInt;
}

uint8_t readInt(){
    uint8_t tempInt = '\0';
    do{
        read(fd, &tempInt, 1);
    } while(tempInt == '\0');
    
    usleep(2 * 10 * 1000); // Aparrently we have to wait for the port to do stuff...
    cout << "TempInt: " << tempInt << endl;
    return tempInt;
}













