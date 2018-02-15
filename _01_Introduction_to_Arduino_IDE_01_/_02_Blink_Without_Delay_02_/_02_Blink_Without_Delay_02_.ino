/* Blink without Delay
 
 Turns on and off a light emitting diode(LED) connected to a digital  
 pin, without using the delay() function.  This means that other code
 can run at the same time without being interrupted by the LED code.
 
 The circuit:
 * LED attached from pin 13 to ground.
 * Note: on most Arduinos, there is already an LED on the board
 that's attached to pin 13, so no hardware is needed for this example.

 
 http://www.arduino.cc/en/Tutorial/BlinkWithoutDelay
 */

// constants won't change. Used here to set pin numbers:
  // Pin 13: Arduino has an LED connected on pin 13
  // Pin 11: Teensy 2.0 has the LED on pin 11
  // Pin  6: Teensy++ 2.0 has the LED on pin 6
  // Pin 13: Teensy 3.0 has the LED on pin 13
const int ledPin =  13;      // the number of the LED pin

// Variables will change:
int ledState = LOW;             // ledState used to set the LED
long previousMillis = 0;        // will store last time LED was updated

// the follow variables is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long interval = 1000;           // interval at which to blink (milliseconds)

void setup() {
  // set the digital pin as output:
  pinMode(ledPin, OUTPUT);      
}

void loop()
{
  // here is where you'd put code that needs to be running all the time.

  // check to see if it's time to blink the LED; that is, if the 
  // difference between the current time and last time you blinked 
  // the LED is bigger than the interval at which you want to 
  // blink the LED.
  unsigned long currentMillis = millis(); // this line initializes a millisecond counter
 
  if(currentMillis - previousMillis > interval) { //if the current count - the last stored change count > your interval
    // save the last time you blinked the LED 
    previousMillis = currentMillis;   // set the counter for your new exchange time

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) // if led is off (could also use "ledState != HIGH", to say if led is not on)
      ledState = HIGH; // turn the led on
    else // otherwise
      ledState = LOW; // turn the led off

    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState); // write the LED as decided in previous if statement
  }
}

/*
 * Questions for your notebook:
 *  Why is blinking light this way better than using the Delay() function?
 *  Are there times using Delay may have advantages?
 *  Did this lab help you understand why using Delay() can be a bad thing??
 *  
 *  Please consult your supervisor or colleagues if any of the answers to these questions are confusing
 *  
 *  Assignment:
 *  Make the light blink for 2 seconds on and off. 
 *  
 *  Record any changes you made in your journal. 
 */

