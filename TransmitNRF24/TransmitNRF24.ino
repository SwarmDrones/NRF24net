/*
* Author: Ariel Feliz
* Date: 11/10/16
* Basic UDP style of transmitting data over NRF240l1
* Run with reciever project: RecieveNRF24
*/

#include <SPI.h>
#include "RF24.h"

/****************** User Config ***************************/
/***      Set this radio as radio number 0 or 1         ***/
bool radioNumber = 0;
#define CE 40 // 7 
#define CS 41 // 8
/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(CE,CS);
/**********************************************************/

byte addresses1[]= { 0xFF,0xFF,0xFF,0xFF,0xFF};
byte addresses2[]= { 0x01,0x01,0x01,0x01,0x01};
uint32_t data3 = 10;
float data2 = 10.23;
char data = 'Y';
//char* data = "hello";
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setChannel(99);
  radio.setDataRate(RF24_2MBPS);
  // Set the PA Level low to prevent power supply related issues since this is a
 // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  //radio.setPALevel( RF24_PA_MAX);
  
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

void loop() 
{
  //Serial.println("Now sending ");

   // Take the time, and send it.  This will block until complete
  if(data3 > 100)
  {
    //data2 = -100;
    data3 = 0;
  }
  
  // First, stop listening so we can talk.
  radio.stopListening();  
  radio.flush_tx();
  //delay(5);
  radio.write(&data, sizeof(char));
  radio.flush_tx();
  //delay(5);
  radio.write(&data3, sizeof(uint32_t));
  
  delay(10);
  data3 = data3+1;
  //data2 += 10.1;
  // Try again 1s later
  
 }

