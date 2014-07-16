
/* ShiftRegControlWithSPI.ino

      This sketch is to be used with the ShiftRegV2.m script in Matlab. This is
      a demonstration sketch to show the use of the built in SPI library and 
      serial communication with MATLAB to control a series of LEDs connected to
      any number of shift registers.
      
      Circuit:
      
      * 74HC595 Shift Registers
      * DataIn (Master Out Slave In)- Pin 11
      * Clock (Shift Register Clock)- Pin 13
      * Latch (Slave Select/Storage Clock)- Pin 10
      * .1uF capacitor connected in parallel from the latch to ground
      * Output Enable (OE) and Master Reset should both be pulled to ground
      * Other pins on the shift register can be configured according to 
        https://www.sparkfun.com/datasheets/IC/SN74HC595.pdf
        
      Created Friday June 27, 2014
      by Tommy Romano

*/

#include <SPI.h> //Includes SPI library

const int ssPin = 10; //Latch pin (slave select Pin)
int numSR = 3; //Number of shift registers
int zeros[] = {0,0,0};
int start;
//OTHER PINS NOT STATED IN DECLARATIONS:
/*  Data Pin: I/O 11
    Clock Pin: I/O 13
    THESE PINS ARE DEFAULT IN THE SPI ARDUINO LIBRARY (included above)
*/


void setup(){
  pinMode(ssPin,OUTPUT); 
  digitalWrite(ssPin,LOW); //Pulls latch high so no data can be sent
  SPI.begin(); //Starts SPI
  SPIwrite(zeros);
  Serial.begin(115200); //Starts serial with Baud Rate of 115200 (same as Matlab)
}

void loop(){
  if(Serial.available()>0){ //waits for communication from matlab
    start = Serial.parseInt(); //first number in string is the number of shift registers
    if(start != 0){
      int data[numSR]; //creates data array that stores bytes to be sent to each SR
      for(int i = 0;i<numSR;i++){
        data[i] = Serial.parseInt(); //next numbers in string specify the bytes to be sent
      }
      SPIwrite(data);
    }
  }
}

/* SPIwrite(int data[]) 
    Takes in an array of 8 bit integers and uses 
    SPI communication to sent the bytes to the shift
    registers. Slave Select pin must be pulled low then
    high for data to be transmitted.
*/

void SPIwrite(int data[]){
  digitalWrite(ssPin,LOW);
  for(int i = 0;i<numSR;i++){
    SPI.transfer(data[i]);
  }
  digitalWrite(ssPin,HIGH);
}

