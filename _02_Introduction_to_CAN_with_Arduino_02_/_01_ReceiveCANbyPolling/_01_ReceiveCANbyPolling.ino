/*
 * In this lab we will be covering how to receive a can message and manage the received data.  
 * For this lab you will need a Teensy 3.6 and a CAN Transceiver (MCP2562 or MCP2558 or similar)
 * 
 * To communicate with the CAN transceiver the TX and RX pins of the Teensy 3.6 need to be wired
 * to the transceiver. The CAN Transceiver will also require Power and ground. Some will require
 * a logic reference voltage. 
 * 
 * On the Teensy 3.6, CAN0 is by default allocated to pins 3 & 4. This can be changed to 29 & 30,
 * but this will not be covered in this lab. 
 * 
 * Wire your CAN Transceiver in accordance with the following Diagram:
 * 
 *        Teensy 3.6                      MCP2562
 *           GND    --------------------  GND (2)
 *        CAN0TX (3)--------------------  TXD (1)
 *        CAN0RX (4)--------------------  RXD (4)
 *           VIN    --------------------  VDD (3)
 *           3.3V   --------------------  VIO (5)
 *           
 *           
 * From this point, your CAN Transceiver is ready to Connect to a CAN Bus. If you are not connecting
 * to a production CAN bus on a vehicle, you will need to connect two 120ohm resistors across CAN High
 * and CAN Low. This will aid in differintiating the signal between the two wires. 
 * 
 * If you do not have access to another CAN network you will need to refer to a later code in this 
 * section. The Teensy 3.6 has the ability to send and receive CANbus messages with itself as it has
 * two CAN channels. 
 * 
 * Good luck, and 
 *           
 */
 
 
#include <FlexCAN.h>

//Create a counter to keep track of message traffic
uint32_t RXCount = 0;

//Declare the CAN message variable that includes
//ID, Data Length Code, and Data Buffer
static CAN_message_t rxmsg;

void setup() {
  // put your setup code here, to run once:

  //Start the CAN message on the first CAN controller (works on both the Teensy 3.2 and Teensy 3.6)
  Can0.begin(250000);

  //The default filters exclude the extended IDs, so we have to set up CAN filters to allow those to pass.
  CAN_filter_t allPassFilter;
  allPassFilter.ext=1;
  for (uint8_t filterNum = 8; filterNum < 16;filterNum++){ //only use half the available filters for the extended IDs
    Can0.setFilter(allPassFilter,filterNum); 
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Can0.available()) {
    Can0.read(rxmsg);
    char CANdataDisplay[50];
    sprintf(CANdataDisplay, "%12lu %12lu %08X %d %d", RXCount++, micros(), rxmsg.id, rxmsg.ext, rxmsg.len);
    Serial.print(CANdataDisplay);
    for (uint8_t i = 0; i < rxmsg.len; i++) {
      char CANBytes[4];
      sprintf(CANBytes, " %02X", rxmsg.buf[i]);
      Serial.print(CANBytes);
    }
    Serial.println();
  }
}
