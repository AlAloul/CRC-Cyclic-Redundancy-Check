# CRC-Cyclic-Redundancy-Check
Modeling of a simple Data Link Layer

The goal of this project is the modeling of the simple data link layer. 

The implementation consists of:

Sender:
-------
A sender program receives data from the upper layers (upper layers can be
simulated by the keyboard), then the sender construct a frame to be sent. A
frame has a fixed size, and data can be sent in multiple frames.
A frame should contain the following information:
• Source addresses
• Destination address
• Information data
• CRC code : a fixed generator polynomial should be fixed to be used by
the sender and the receiver.
• Any additional fields if needed

Channel:
--------
The frame is then sent to a noisy channel, the channel adds a random number
of errors in random locations in the frame.
Remark: multiple senders can be connected to the channel, and multiple
receivers can receive from the same channel.

Receiver:
---------
Finally the frame is forwarded from the channel to a receiver, the receiver
checks the destination addresses and then check for errors, the receiver
display the result on the screen.

