Lab 5 - Interrupts - "Remote Control Decoding"
========

###Objectives

In this lab, use knowledge of interrupts and the Timer_A subsytem to reverse engineer a remote control.

Lab day 1: learn the timing and bit patterns for your remote control

Lab day 2: demonstrate your code can receive and decode button presses from the remote control

Lab day 3: implement etch-a-sketch or pong

###Day 1 Activities

![alt text](http://i61.tinypic.com/2a7gcjk.png)

How long will it take the timer to roll over?
It should take roughly 64.5 microseconds.

How long does each timer count last? 
1 us.

###Data Packets

![alt text](http://i59.tinypic.com/1z380om.png)

###Means and Standard Deviations of Pulses
![alt text](http://i57.tinypic.com/2112vcj.png)

###Button Codes
![alt text](http://i59.tinypic.com/5wczfs.png)

###Day 2 Activities



###Required Functionality
For required functionality, the biggest change to the program was creating if statements based off of button presses to toggle the LEDs. I also had to change the definitions of the the buttons so that they would match the button codes for the remote.

A video of the functionality can be seen in the file list. Github did not support embedding of videos, so both the A and required functionality are uploaded in the file list

###A Functionality

For A functionality, I ended up using the etch a sketch program from Lab 4. Nothing really had to be changed on the asm file. The c file had to have the BIT and PIN inputs changed to the button code definitions. I also had to include a block of code to determine the IR signal reciever by the IR reciever. I ended up having to seek help from C2C Thompson to implement this particular part of the code. It involved determining whether a packet signal was fully recieved, and then it shifted a 1 or 0 to the IrPacket depending on which state the array was in. The video of the functionality can be found in the file list for this lab.


###Conclusion
