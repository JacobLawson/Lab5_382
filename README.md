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

#####Required Functionality
For required functionality, the biggest change to the program was creating if statements based off of button presses to toggle the LEDs. I also had to change the definitions of the the buttons so that they would match the button codes for the remote.

A video of the required functionality can be seen in the link below.

<embed width="440" height="420" type="application/x-shockwave-flash" src="http://v8.tinypic.com/player.swf?file=28mg4y0&s=8"><br><font size="1"><a href="http://tinypic.com/player.php?v=28mg4y0&s=8">Required Functionality</a>



###A Functionality

For A functionality, I ended up using the etch a sketch program from Lab 4. Nothing really had to be changed on the asm file. The c file had to have the BIT and PIN inputs changed to the button code definitions. I also had to include a block of code to determine the IR signal reciever by the IR reciever. I ended up having to seek help from C2C Thompson to implement this particular part of the code. It involved determining whether a packet signal was fully recieved, and then it shifted a 1 or 0 to the IrPacket depending on which state the array was in. The video of the functionality can be seen in the link below. The quality was degraded so that the video could fit, but you can still see the program work. Sorry about that!

<embed width="440" height="420" type="application/x-shockwave-flash" src="http://v8.tinypic.com/player.swf?file=21l796c&s=8"><br><font size="1"><a href="http://tinypic.com/player.php?v=21l796c&s=8">A Functionality</a>


###Conclusion

One of my earlier problems occured when I was not consistent in defining my buttons. I had VOL_DN and VOL_DW used interchangeably and that caused a bunch of errors to pop up. Also, I had to constantly check to make sure my wires were properly connected to ensure I got the correct signal.

###Documentation
C2C Wooden, along with Capt Trimble, helped explain how to make sense of the logic analyzer and distinguish the different types of pulses

C2C Thompson helped clarify how to get my A Functionality program to recieve IR signals by having a loop to detect packets and by including an ISR to notice when the pin changed.
