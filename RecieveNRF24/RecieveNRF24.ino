/*
* Author: Ariel Feliz
* Date: 11/10/16
* Recieving basic UDP style data over NRF240l1
* Run with reciever project: RecieveNRF24
*/

#include <SPI.h>
#include "RF24.h"

/****************** User Config **** ***********************/
/***      Set this radio as radio number 0 or 1         ***/
bool radioNumber = 1;
#define CE 7 //7 green
#define CS 8 //8 yellow
/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(CE,CS);
/**********************************************************/

byte addresses1[]= { 0xFF,0xFF,0xFF,0xFF,0xFF};
byte addresses2[]= { 0x01,0x01,0x01,0x01,0x01};

void setup() {
  Serial.begin(9600);
  //while (!Serial);
  //delay(1000);
  Serial.println(F("Recieving"));
  radio.begin();
  radio.setChannel(99);
  radio.setDataRate(RF24_2MBPS);

  // Set the PA Level low to prevent power supply related issues since this is a
 // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel( RF24_PA_MAX);
  
  // Open a writing and reading pipe on each radio, with opposite addresses
  if(radioNumber){
    radio.openWritingPipe(addresses1);
    radio.openReadingPipe(1,addresses2);
  }else{
    radio.openWritingPipe(addresses2);
    radio.openReadingPipe(1,addresses1);
  }
  if(radio.isValid())
  {
    Serial.println("radio is valid");
  }
  // Start the radio listening for data
  radio.startListening();
}

void loop() {
  radio.startListening();
  char type;
  uint32_t data;
  if( radio.available())
  {                                   // While there is data ready
      radio.read( &type, sizeof(char));//type, data
      if(type == 'Y')
      {
        //radio.flush_rx();
        //Serial.print("type: ");
        //Serial.println(type);// Get the payload
        radio.read(&data, sizeof(uint32_t));
        Serial.print("data: ");
        Serial.println(data);
      }
      
  }
  delay(1);
 }



