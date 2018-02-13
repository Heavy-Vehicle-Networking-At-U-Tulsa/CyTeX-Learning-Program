# CAN bus
* The following are descriptions of labs that need to be written. I have included a general order I believe these should be compeleted. 
### Teensy Projects
* 1 Intro to Programming with Arduino
	- ~Getting Started (_Blink_)~
	- ~Blink without Delays~
	- ~Introduction to Serial Console (_Serial Command Window_)~
* 2 Intro to Teensy
	- Teensyduino Install and 3.2 vs. 3.6 (_This may need to be earlier on_)
	- LED Light control examples(_PWM_)
		-Button Press to turn on a light (_Digital Read and Write_)
* ~Introduction to CAN presentation and activity (_Presentations/Can Bus basics.pptx_)~
* 3 Sending a Can Message (_Teensy 3.6_)
	- Using FlexCAN library
	- Using MCP2515 Library
	- Using LIN
	- Provide Schematics
	- Send to and From yourself
* 6 Receive Messages from the Dash Display
	- Identify Tachometer and Speedometer (_manipulate speedometer with tone ring_)
	- Compare values with truck values
* 7 Playing with the dash - like the alarm clock
	- Using RTC functionality determine the time and display it on the Dash Display
	- Supervisor Sign off
*  DOS attack
	- Create a Device that when powered on crashes the bus using message priority (_refer to the CAN powerpoint_)
	- Create a Device that after 30 seconds crashes the bus
# Tools
### Vehicle Spy
* 5 Connect to the Truck (_Using J1939 Protocol_)
	- Key on RUN not start Identify CAN Messages
	- Start Truck
	- Compare before and After
	- Identify Tachometer and Speedometer messages

### Protocol
* 4 J1939 - Find info from traffic? - wheel speed, engine speed, door lock/unlock, etc, 
* Parsing traffic Data - network class assignment - (_need to learn python first_)
* Oscilliscope decode message
	- Do this by hand
	- Write a Python Script to do it for you

# Diagnostics
* UDS - Protocol traffic interactive
* RP1210 Devices - Connect, Use OEM software, Locate UDS traffic
* Seed-Key Exchange -etc.
* TU_RP120 

### Python
* Intro to python
* Introduce BBB and build on top of James examples?





# Encryption
* Obfuscation - plot different sudo random generators
### Hashing
* powershell comparing hash files- what are they
* Power of hash- Windows password crack
### Private/Public Keys
* What is DH? DH over CAN
* PKI? etc.
### AES
* What is. Case use example

# Internet
### Protocol?
* Recreate network class?
* Python Server 
* Teensy Ethernet
* Teensy Wifi
### TU_RP1210
* Learn about the server?
