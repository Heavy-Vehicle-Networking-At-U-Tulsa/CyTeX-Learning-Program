//Implementation of the Diffie-Hellman Key Exchange between two CAN nodes
//Only produces a single byte of "Shared Secret" and would be ineffiecient to use in a finished design
//It also fails to generate shared secrets of high values because they overloaded memory locations 
//The intended purpose of this sketch is an educational tool to learn about DH Key Exchange

//Note: The Bob sketch also must be running on a seperate Teensy simultaniously connected via a CAN network

//For anyone unfarmiliar with DH here's a helpful example on Khan Academy that explains the process: 
//https://www.khanacademy.org/computing/computer-science/cryptography/modern-crypt/v/diffie-hellman-key-exchange-part-2

//Randomness was produced using Rhys Weatherley's arduinolibs: https://github.com/rweather/arduinolibs

//John Maag
//July 2017
//University of Tulsa: Student CyberTruck Experience


#include <FlexCAN.h>
#include <RNG.h>
#include <TransistorNoiseSource.h>

static CAN_message_t txmsg;
static CAN_message_t rxmsg;

long lastmillis;
long delaymillis;

TransistorNoiseSource noise(A1);
unsigned long bobResponse = 0;
unsigned long generator;
long primeMod;
unsigned long aliceSecretNum;
unsigned long alicePublicNum;
unsigned long bobPublicNum;
long sharedSecret;
uint8_t randNum;
byte primes[]={ 
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101,
    102, 107, 109, 113, 127, 131,  137 , 139, 149, 151, 157, 163, 167, 173,  179, 181, 191, 193, 197, 
    199, 211, 223, 227, 229, 233, 239, 241, 251 };


void setup() {
  
  delay(1000);
  Serial.println(F("Alice in Diffie-Hellman Key Exchange over CAN"));
  Can0.begin(250000);

  //initilizes randomness using a noise source
  RNGClass();
  RNG.begin("Alice is random",950);
  RNG.addNoiseSource(noise);
  
  lastmillis = millis();

  //in order to recieve extended Id's without dropping any messages
  CAN_filter_t allPassFilter;
  allPassFilter.id=0;
  allPassFilter.ext=1;
  allPassFilter.rtr=0;
  //leave the first 4 mailboxes to use the default filter. Just change the higher ones
  for (uint8_t filterNum = 4; filterNum < 16;filterNum++){
    Can0.setFilter(allPassFilter,filterNum); 
      }
     
  }


void loop() {


  
  delaymillis = millis()-lastmillis;

  //section Where Alice begins communication with Bob
  //Regenerate and Resend Alice's public number and generator/primemod pair
  //In the event Bob does not respond Alice tries again after 5 seconds
  if(bobResponse == 0  && delaymillis >= 5000){
    
    //generate primemod; /this can be any prime number from the array of primes defined above
    do{
      RNG.rand(&randNum,1);
    }while (randNum > 20);
    primeMod = primes[randNum];
    
    //generate generator
    do{
      RNG.rand(&randNum,1);
    }while (randNum > 20);
    generator = randNum;
    
    //generate alice's secret number
    do{
      RNG.rand(&randNum,1);
    }while (randNum > 20);
    aliceSecretNum = randNum;

    //DH operation to generate Alice's shared number
    alicePublicNum = (int(pow(generator,aliceSecretNum)))%primeMod;



    //Structure Alice's message
    //It is your decision on how exactly this data will be formatted
    //You may want to consider J1939 and attempt to follow address standards (not necessary)
    txmsg.ext = 1;
    txmsg.id = 0x0000000; //Alice
    txmsg.len = 4;
    txmsg.buf[0] = 0;
    txmsg.buf[1] = 0;
    txmsg.buf[2] = 0;
    txmsg.buf[3] = 0;
    Can0.write(txmsg);
    //Send Alice's information to Bob
  
    lastmillis = millis();
    Serial.println("sent");
  }

  //Listen for Bob's Response
  while(Can0.read(rxmsg)){

    //check if the message on the bus is from Bob
    //For this, use unique identifiers you chose when sending from Bob.
    //This may be a unique ID, a unique data bit, etc
    if("bobs unique message is recieved"){
    
        bobResponse = 1;

        //save bob's number
        
        //DH operation to generate SS
        sharedSecret =   (int(pow(bobPublicNum,aliceSecretNum)))%primeMod;

        //output all values to verify results
        Serial.print("Alice's secret: ");
        Serial.println(aliceSecretNum);
        Serial.print("Alice's public number: ");
        Serial.println(alicePublicNum);
        Serial.print("PrimeMod: ");
        Serial.println(primeMod);
        Serial.print("Bob's public number: ");
        Serial.println(bobPublicNum);
        Serial.print("Generator: ");
        Serial.println(generator);
        Serial.print("The Shared Secret is: ");
        Serial.println(sharedSecret);
        
    }
  }
  
  
}
