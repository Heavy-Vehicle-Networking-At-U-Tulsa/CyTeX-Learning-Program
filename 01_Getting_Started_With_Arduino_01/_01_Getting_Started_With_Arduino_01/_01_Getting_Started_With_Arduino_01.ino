/* 
 *  Hello and welcome to your first tutorial using the Arduino IDE. Congratulations on
 *  successfully downloading the IDE. 
 *  
 *  I hope you enjoy your time working with us, we look forward to seeing how far you 
 *  can go!
 *  
 *  - Maintenance
  */
 
/*  
 *  What you are currently reading is a comment. A comment is a block of code that is 
 *  overlooked by the compiler when you are writing your code. These are useful for 
 *  troubleshooting and communicating what you are trying to accomplish to your peers. 
 *  
 *  This is a rather large chunked comment and begins with a "/*" character. Anything
 *  After this character will not be considered when compiling code. To end this style
 *  of comment you can use the reverse, "* /" without the space in the middle. 
 *  
 *  Additionally comments can be over a single line by using a "//" this allows for 
 *  quick one line comments about what you are trying to accomplish in a specific 
 *  of your code. 
 *  
 *  - Maintenance
  */

 Begin by commenting this line out;

 /* 
  *  The other important piece of information in arduino is that all lines except loops
  *  must end with a semi-colon (;) This tells the computer that you have finished a 
  *  complete thought. Below you will find a provided sample code that blinks an LED on
  *  the board of your Arduino.
  * 
  *  -Maintenance
  */
  
/*
  This example is referred to as Blink. It can be accessed at any time under File->
  Examples->01.Basics->Blink for reference. 
  
  This code turns on an LED on for one second, then off for one second, repeatedly.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// Pin 11 has the LED on Teensy 2.0
// Pin 6  has the LED on Teensy++ 2.0
// Pin 13 has the LED on Teensy 3.0
// give it a name:
int led = 13; // Here you are telling the Arduino that your LED is connected to pin 13. 

// All arduino sketches come "from the factory" with a setup and loop routine.
// Put anything that you only want to run 1 time in the setup portion of the function. 

void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     //pinMode designated that led (pin 13) is going to be used as an output,
  //the other argument you can use is INPUT
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second (1000 ms) All other processes stop too!
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);               // wait for a second (1000 ms)
}

/*
 * Compile this code and ensure that it works on your device. You will need to select the proper
 * board under Tools->Board:....->Your board type. If you are unsure of what type of board you have, 
 * you will need to ask your supervisor or a colleague for guidance. 
 */


 /*
  * Once you have ensured that the On Board LED (OBL) is flashing, your first assignment is to make
  * the light stay on for 2 seconds and off for .5 seconds. 
  * 
  * Questions to record in your notebook:
  * Did you notice a difference?
  * What portion of the code did you change?
  * Why might the Delay() function not be useful in more complicated systems?
  * 
  * Once you have completed this sketch, please save your code as COMPLETE_filename to ensure your 
  * progress can be tracked. 
  */
