/*
 * For this lab you will need a potentiometer along with your teensy. Please connect the middle of the pot. to pin 
 * 5, then connect the outside pins to +5V and Ground. 
 * 
 * A potentiometer is a three-terminal resistor with a sliding or rotating contact that forms an adjustable voltage 
 * divider. If only two terminals are used, one end and the wiper, it acts as a variable resistor or rheostat.
 * 
 * In other words, in this lab a potentiometer will be used to vary the voltage entering the device. This will be 
 * displayed in the serial monitor as numbers between 0 and 1028. 
 * 
 * Please consult your colleagues to determine where to find these materials if you do not already know
 * where they are. 
 * 
 * 
 */

/*
 * In the following, you will learn how to read inputs. Additionally you will learn how to use the serial monitor 
 * Reads an analog input on pin 5, prints the result to the serial monitor.
 * 
 * The Serial Monitor can be quickly accessed by Ctrl+Shift+M or by clicking the magnifying glass in the top right
 * corner of the screen
 * 
 * Graphical representation is available using serial plotter (Tools > Serial Plotter menu)
 * 
 * 
 * Enjoy!
 * 
 * - Maintenance
*/

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second: (this is the speed at which data is transferred, other speed options
  // can be seen on the serial console. 
  Serial.begin(9600);
}


// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  
  int sensorValue = analogRead(A0); // change this to the pin that the middle output of your potentiometer is connected to
  
  // print out the value you read:
  
  //Serial.print("Sensor Value: "); // uncomment this line after running through the software once.
  Serial.println(sensorValue); // This uses the function println() from the Serial class to display on the console
  
  delay(1);        // delay in between reads for stability, this delay ensures that you do not overload anything by turning too quickly
}

/*
 * In this lab you will become familiar with the Analog Read function
 * You will also be introduced to the Serial console. 
 * 
 * Instructions:
 * Change sensorValue to read for your potentiometer. 
 * Run the code as is and find the serial console
 * Then uncomment line 38 and run the software again. 
 * 
 * 
 * 
 * Questions for your notebook:
 * 1) What is the difference between Serial.println() and Serial.print()
 * 2) What is the difference between the analogRead() function and digitalRead() function from previous labs
 * 
 * Feel free to play around with the Serial Console until you are comfortable with it. Try initializing at different Baud Rates (Data transfer speeds)
 * 
 * - Maintenance
 */
