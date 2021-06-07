//I have modified this file to work with the HC-05 bluetooth serial module instead of the NRF24 radio modules(I have re-wrote the code from line 34 to 84)

#include "Arduino.h"
#include "config.h"
#include "def.h"
#include "types.h"
#include "MultiWii.h"
#include "NRF24_RX.h"
#include <SoftwareSerial.h>

#if defined(NRF24_RX)

SoftwareSerial BTserial(2, 4);   //RxD of Arduino, TxD of Arduino

int16_t nrf24_rcData[RC_CHANS];
String inputString="";

RF24Data MyData;

int step = 25;

void resetRF24Data() { //The defualt value of each of the channels
  MyData.throttle = 0;
  MyData.yaw = 127;
  MyData.pitch = 127;
  MyData.roll = 127;

  MyData.AUX1 = 0;
  MyData.AUX2 = 0;
  MyData.switches = 0;
}

void NRF24_Init() {

  resetRF24Data();

  BTserial.begin(9600);  //SoftwareSerial
  BTserial.println("Bluetooth mode");

}

void NRF24_Read_RC() {
  
  if (BTserial.available()) {
    inputString = (char)BTserial.read();  //define the data recived into a string
    // Command interpreter

    if(inputString == "w")  {  //once it's a string, then the Arduino can compare it the another string
      MyData.throttle = MyData.throttle + step;
    }
    else if(inputString == "s")  {  //the "s" character is the character that will trigger the event
      MyData.throttle = MyData.throttle - step;
    }
    else if(inputString == "a")  {
      MyData.roll = MyData.roll - step;
    }
    else if(inputString == "d")  {
      MyData.roll = MyData.roll + step;
    }

    else if(inputString == "1")  {
      MyData.pitch = MyData.pitch + step;
    }
    else if(inputString == "4")  {
      MyData.pitch = MyData.pitch - step;
    }
    else if(inputString == "3")  {
      MyData.yaw = MyData.yaw - step;
    }
    else if(inputString == "2")  {
      MyData.yaw = MyData.yaw + step;
    }

    else if(inputString == "v")  {
      MyData.AUX1 = !MyData.AUX1;
    }

    // Debug data is sent over software serial
    BTserial.print("THRO: ");
    BTserial.println(MyData.throttle);

  }

  // DO NOT write to these variables, write to MyData.<CHANNEL> instead
  nrf24_rcData[THROTTLE] =  map(MyData.throttle,      0, 255, 1000, 2000);
  nrf24_rcData[ROLL] =      map(MyData.yaw,      0, 255, 1000, 2000);
  nrf24_rcData[PITCH] =     map(MyData.pitch,    0, 255, 1000, 2000);
  nrf24_rcData[YAW] =       map(MyData.roll,     0, 255, 1000, 2000);

  nrf24_rcData[AUX1] =       map(MyData.AUX1,     0, 1, 1000, 2000);
  nrf24_rcData[AUX2] =       map(MyData.AUX2,     0, 1, 1000, 2000);
   //If your channels are inverted, reverse the map value. Example. From 1000 to 2000 ---> 2000 to 1000
}

#endif
