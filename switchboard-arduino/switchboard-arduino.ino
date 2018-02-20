/*
SwitchBoard 
 */

/** Control switchboard
 * Arduino receives commands from master and executes them.
 */


#include <SPI.h>
#include "RF24.h"

/*************  USER Configuration *****************************/
                                          // Hardware configuration
RF24 radio(7,8);                        // Set up nRF24L01 radio on SPI bus plus pins 7 & 8

/***************************************************************/

const uint64_t pipes[2] = { 0xABCDABCD71LL, 0x544d52687CLL };   // Radio pipe addresses for the 2 nodes to communicate.

byte data[32];                           //Data buffer for testing data transfer speeds
char rrxChar;

unsigned long counter, rxTimer;          //Counter and timer for keeping track transfer info

void setup(void) {

  Serial.begin(115200);

  radio.begin();                           // Setup and configure rf radio
  radio.setChannel(1);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_1MBPS);
  radio.setAutoAck(1);                     // Ensure autoACK is enabled
  radio.setRetries(2,15);                  // Optionally, increase the delay between retries & # of retries
  
  radio.setCRCLength(RF24_CRC_8);          // Use 8-bit CRC for performance
  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1,pipes[1]);
  
  radio.startListening();                 // Start listening
  radio.printDetails();                   // Dump the configuration of the rf unit for debugging
  
  Serial.println(F("\n\rRF24/examples/Transfer/"));
  Serial.println(F("*** PRESS 'T' to begin transmitting to the other node"));
  
  randomSeed(analogRead(0));              //Seed for random number generation
  
  for(int i=0; i<32; i++){
     data[i] = random(255);               //Load the buffer with random data
  }
  radio.powerUp();                        //Power up the radio
}

void loop(void){
  while(radio.available()){       
    radio.read(&rrxChar,sizeof(rrxChar));
    Serial.print(rrxChar);
  }     
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {  
  while (Serial.available()) {
    
    // get the new byte:
    char inChar = (char)Serial.read();

    radio.stopListening();
    if (!radio.write( &inChar, sizeof(inChar))) {
      Serial.print(F("failed : "));
      Serial.println(inChar);
    }    
  }
  radio.startListening();
}
