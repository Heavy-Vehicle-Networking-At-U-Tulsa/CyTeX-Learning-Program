//Implementation of the Diffie-Hellman Key Exchange between two CAN nodes
//Only produces a single byte of "Shared Secret" and would be ineffiecient to use in a finished design
//It also fails to generate shared secrets of high values because they overloaded memory locations 
//The intended purpose of this sketch is an educational tool to learn about DH Key Exchange

//Note: The Alice sketch also must be running on a seperate Teensy simultaniously connected via a CAN network

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

TransistorNoiseSource noise(A1);
long generator;
long primeMod;
long bobSecretNum;
long bobPublicNum;
long alicePublicNum;
long sharedSecret;
uint8_t randNum;
int notrecieved = 1;

void setup() {
   
  delay(1000);
  Serial.println(F("Bob in Diffie-Hellman Key Exchange over CAN"));
  Can0.begin(250000);

  //initilizes randomness using a noise source
  RNGClass();
  RNG.begin("Bob is random",950);
  RNG.addNoiseSource(noise);
  
  //find random number under 20
  do{
     RNG.rand(&randNum,1);
  }while (randNum > 20);
  bobSecretNum = randNum;

  //in order to recieve extended Id's without dropping any messages
  CAN_filter_t allPassFilter;
  allPassFilter.id=0;
  allPassFilter.ext=1;
  allPassFilter.rtr=0;
  for (uint8_t filterNum = 4; filterNum < 16;filterNum++){
    Can0.setFilter(allPassFilter,filterNum);
  }
    
}



void loop() {

   //listening for Alice's public number
   while(Can0.read(rxmsg)){
    
    if(rxmsg.buf[3] == 1 && notrecieved && rxmsg.id == 0x12345678){
        //alice's public number recieved  
        notrecieved = 0;

        //reading and saving her public number for use in calculation
        alicePublicNum = rxmsg.buf[2];

        //reading generator and primeMod so calculations will equal Alice's
        generator = rxmsg.buf[1];
        primeMod = rxmsg.buf[0];

        //DH operation to generate SS
        sharedSecret =   (int(pow(alicePublicNum,bobSecretNum)))%primeMod;

        //Respond to Alice with Bob's public number for her calculation of SS
        txmsg.ext = 1;
        txmsg.id = 0x18765432; //Bob
        txmsg.len = 4;
        bobPublicNum = (int(pow(generator,bobSecretNum)))%primeMod;
        txmsg.buf[0] = bobPublicNum;
        txmsg.buf[1] = 0;
        txmsg.buf[2] = 0;
        txmsg.buf[3] = 1;
        Can0.write(txmsg);

        //output all values to verify results
        Serial.print("Bob's secret: ");
        Serial.println(bobSecretNum);
        Serial.print("Bob's public number: ");
        Serial.println(bobPublicNum);
        Serial.print("PrimeMod: ");
        Serial.println(primeMod);
        Serial.print("Alice's public number: ");
        Serial.println(alicePublicNum);
        Serial.print("Generator: ");
        Serial.println(generator);
        Serial.print("The Shared Secret is: ");
        Serial.println(sharedSecret);
      
   }
  }
}
