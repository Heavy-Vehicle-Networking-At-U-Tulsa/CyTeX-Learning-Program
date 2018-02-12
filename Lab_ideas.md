# CAN bus
	- The following are descriptions of labs that need to be written. I have included a general order I believe these should be compeleted. 
### Teensy Projects
* 1 Intro to Programming with Arduino
	- Getting Started
	- Introduction to Serial Console (~Serial Command Window~)
* 2 Intro to Teensy
	- Teensyduino Install and 3.2 vs. 3.6
	- LED Light control examples(PWM)
		-Button Press to turn on a light (Digital Read and Write)
* Introduction to CAN presentation and activity
* 3 Sending a Can Message (Teensy 3.6)
	- Using FlexCAN library
	- Provide Schematics
	- Send to and From yourself
* 6 Receive Messages from the Dash Display
	- Identify Tachometer and Speedometer (manipulate speedometer with tone ring)
	- Compare values with truck values
* 7 Playing with the dash - like the alarm clock
	- Using RTC functionality determine the time and display it on the Dash Display
	- Supervisor Sign off
*  DOS attack
	- Create a Device that when powered on crashes the bus using message priority (refer to the CAN powerpoint)
	- Create a Device that after 30 seconds crashes the bus
### Tools
# Vehicle Spy
* 5 Connect to the Truck (~Using J1939 Protocol~)
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
