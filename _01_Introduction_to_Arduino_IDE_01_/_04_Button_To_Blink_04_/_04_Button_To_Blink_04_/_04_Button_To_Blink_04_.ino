/*
 * This lab will draw on knowledge from previous labs. Please reference your questions to previous
 * labs with any functions you are not familiar with.
 * 
 * The following is required to complete this lab:
 * - Arduino Device 
 * - a switch or button
 * - an LED
 * 
 * If you do not know where to obtain these pieces by consult your colleagues or
 * supervisor. 
 * 
 * Begin by connecting the external LED to the board by placing one pin on the ground
 * connect the other pin to pin 13 on the board. 
 * 
 * Then connect your switch/button on one end to a 5V source pin. Connect the other 
 * side to a pin that can be read, here we have chosen pin 5. 
 * 
 * In this lab you will be creating a button that when pressed turns on a light and 
 * when released the light turns off. 
 * 
 * - Maintenance 
 */
 
int led = 0; //Here we define the LED location, please change this to your chosen pin (13)
int blinkButton = 0; //Here we define where the button will be located, please change this to your chosen pin (5)

void setup() {
  pinMode(led, OUTPUT); 
}

void loop() {  
  if (digitalRead(___)){ // if the button/switch is closed place the variable for your button in the blank
    delay(20); // this is called debouncing, and is required for button pressing
    
    while (digitalRead(___)){ //this initializes a loop that will stay as long as the arguement is true. rechecks to ensure the button is pressed.
       
       // add code here to turn the light on
       
       }   
    }
  digitalWrite(led, LOW); // turn the light off if the button is not pressed. 
}
/*
 * In this lab you will use knowledge from previous labs to create a button that turns a light on
 * 
 * 
 * Instructions:
 * Change Led and button pin locations
 * Fill in digitalRead functions with the button variable
 * Tell the led to turn on while the button is pressed
 * 
 * Extra:
 * Add a Serial Command Window that tells the user when the state has changed. 
 * 
 * Questions for your notebook:
 * 1) Why did we use a digital write instead of an Analog write.
 * 2) What baudrate did you use for the Serial Console. 
 * 
 * The example code will be a great tool for you. If you are not familiar with a function,
 * you can right click on the highlighted specific function and click find in reference. This
 * if helpful when venturing into new tasks.
 * 
 * - Maintenance
 */
