Arduino-Matlab-Communication
============================

Serial Communication interface between MATLAB and Arduino

This is a demonstration code for how MATLAB can be used to control Arduino via serial communication. In this example, MATLAB sends data to the Arduino to control an array of LEDs using 74HC595 shift registers. As to avoid errors from multiple serial communication signals on the Arduino Uno, the built-in Arduino SPI interface is used to shift bits into the shift registers.

This demonstration was originally created for the Duke Center for Metamaterials and Integrated Plasmonics to operate an Arduino Uno board that controls an array of RF transmitters while acquiring and analyzing data in MATLAB.
