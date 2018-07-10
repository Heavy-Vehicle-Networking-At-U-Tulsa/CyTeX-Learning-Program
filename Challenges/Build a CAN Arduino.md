# Building an Arduino to communicate over CAN
______________________________________________
## Challenge: using the pieces below, send a CAN message.

 Materials:
 - Breadboard
 - Prototyping Wire
 - ATmega328P
 - MCP2551/MCP2562/MCP2558
 - MCP2515/MCP25625
 - LED
 - 120ohm (2) or 60 ohm (1) resistor
 - a 16MHz crystal
 - 6 pin straight header
 - a 10k resistor
 - 18-22 pF capacitor (2)

## Resources:
- Use Datasheets to determine how to connect everything
    - To find datasheets use google, digikey, and mouser
- Learning how to push code to the arduino: https://www.arduino.cc/en/Tutorial/ArduinoISP
- For help with SPI communication to MCP2515: http://avrbeginners.net/architecture/spi/spi.html

## Challenge:
- Send a CAN Message (Verify with oscilloscope)
- Decode the message from the oscilloscope to ensure that it is the mesage you told your arduino to send
    - This can be done with Python
- Create an Altium Schematic of the layout that you created
