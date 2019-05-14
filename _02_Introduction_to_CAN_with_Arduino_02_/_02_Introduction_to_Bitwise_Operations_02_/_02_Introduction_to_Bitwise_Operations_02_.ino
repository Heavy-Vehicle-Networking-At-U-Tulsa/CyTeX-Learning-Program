/*
 * In the following lab we will create a program that teaches students the binary operators
 * and how they are used in arduino. 
 * 
 * This lab requires not but a arduino device to communicate with the Serial Console. 
 * 
 * -Maintenance
 */

//Setup the led to let you know that your board is on.
int led = 13; 

//Initialize two binary numbers. Notice the "B" before the number. This indicates that the following number is a Binary number and not a decimal number
uint8_t num1 = B11010101;
uint8_t num2 = B10101011;

//Initialize place holders for the operations we will be covering.
uint16_t andOp = 0;
uint16_t orOp = 0;
uint16_t xorOp = 0;
uint16_t notOp1 = 0;
uint16_t shiftLeft1 = 0;
uint16_t shiftRight1 = 0;
uint16_t notOp2 = 0;
uint16_t shiftLeft2 = 0;
uint16_t shiftRight2 = 0;

//Initialize number division holders
uint16_t upperHolder = 0;
uint16_t lowerHolder = 0;
uint16_t newNumber = 0;

//This sketch will only be done one time. Therefore; we only want it to run one time. 
void setup() {
  // put your setup code here, to run once:
  
  pinMode(led, OUTPUT); 
  digitalWrite(led, HIGH); //turn the onboard light on
  
  Serial.begin(9600); //intialize the Serial Connection
  delay(5000); //Wait 5 seconds, this gives you time to open the serial window after uploading. If you do not have the window open you will miss the output
  
  //Bitwise Operations in Arduino
  andOp = num1 & num2; //this is the AND operation
  orOp = num1 | num2; //this is the OR operation
  xorOp = num1 ^ num2; //this is the XOR operation
  notOp1 = ~num1; //this is the NOT operation

  //add your code here

  //Bit Shifting in Arduino
  shiftLeft1 = num1<<4; //Bit shift Left 4 digits
  shiftRight1 = num1>>4; //Bit shift Right 4 digits

  //add your code here


  //In the following we are going to output the calculated information to the Serial Console.
  
  Serial.println("Quick Maths"); //Header
  
  //Outputting the numbers can be changed. The default is as a base 10 number. Use ", BIN" to display as a binary
  
  Serial.print("A: "); Serial.print(num1); Serial.print(", "); Serial.println(num1, BIN); //num1 
  Serial.print("B: "); Serial.print(num2); Serial.print(", "); Serial.println(num2, BIN); //num2
  Serial.println("-----------------------------------------------------");  //divider
  Serial.print("A AND B: "); Serial.print(andOp); Serial.print(", "); Serial.println(andOp, BIN); //Displaying the AND operation
  Serial.print("A OR B: "); Serial.print(orOp); Serial.print(", "); Serial.println(orOp, BIN); //Displaying the OR operation
  Serial.print("A XOR B: "); Serial.print(xorOp); Serial.print(", "); Serial.println(xorOp, BIN); //Displaying the XOR operation
  Serial.print("NOT A: "); Serial.print(notOp1); Serial.print(", "); Serial.println(notOp1, BIN); //Displaying the NOT of num1
  Serial.print("Shift Left 4 A: "); Serial.print(shiftLeft1); Serial.print(", "); Serial.println(shiftLeft1, BIN); //Display shifting left 4 digits
  Serial.print("Shift Right 4 A: "); Serial.print(shiftRight1); Serial.print(", "); Serial.println(shiftRight1, BIN); //Display shifting right 4 digits  
  Serial.println("-----------------------------------------------------"); 
  
  //add your code here



  //You can use math to add numbers together too. Here we will use bit shifting and operators to move bits and reassemble the start number

  //To store large numbers in smaller data chunks we can use bit shifting to divide it into smaller units
  upperHolder = (num1& B11110000)>>4; //here we will use the AND operation to isolate the upper half of our 8 digit number
  lowerHolder = num1 & B00001111; //we will not use bit shifting here as we are only looking for the lower portion

  Serial.print("Upper Holder: "); Serial.print(upperHolder); Serial.print(", "); Serial.println(upperHolder, BIN);
  Serial.print("Lower Holder: "); Serial.print(lowerHolder); Serial.print(", "); Serial.println(lowerHolder, BIN);
  Serial.println("Notice these are not related to the original number");

  //Now we will reconstruct the data chunks back into the original number
  upperHolder = upperHolder<<4;// this moves the binary back to the original location ie 11110000
  newNumber = upperHolder | lowerHolder;

  //Now we will output the reconstructed number. With any success we will have returned to the original number
  Serial.print("Here is the reconstructed number: "); Serial.println(newNumber);
  Serial.print("Here is the original number: "); Serial.println(num1);

  //Add your script for num2 here

  Serial.println("-Maintenance");
}
void loop() {
//we will not be using the loop function as we only want this to run once as a demonstration. 
}

/*
 * In this lab you will have learned how to use bit operations in arduino
 * 
 * Assignment:
 * 1) Add code to perform the bitwise operations in the opposite order. Example: existing code is A&B, you need to create code that does B&A
 * 2) Add code to perform the binary shifting operations on the second number
 * 3) Add Serial Output to display your newly added code. Refer to existing code.
 * 4) Perform a bit wise sepeation for the second number and bring the second number back. Include Serial Ouput and verify that the two end numbers are the same
 * 
 * Questions:
 * -What happens to the lower bits when you bit shift right? 
 * -What happens to the upper bits when you bit shift left?
 * -Did this lab help visualize how bitwise operations can be useful in programming?
 * 
 * Thank you
 * -Maintenance
 * 
 */
