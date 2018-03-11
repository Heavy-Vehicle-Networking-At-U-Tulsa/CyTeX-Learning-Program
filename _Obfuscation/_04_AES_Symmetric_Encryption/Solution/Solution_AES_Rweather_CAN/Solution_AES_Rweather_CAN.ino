/*
 * Copyright (C) 2015 Southern Storm Software, Pty Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

/*
This example sends and recieves any message accross the CAN bus encrypted.
Run this code on two Teenys to communicate between them
I loosely follow J1939 transport layer. This could be improved upon.
*/

#include <Crypto.h>
#include <AES.h>
#include <string.h>
#include <FlexCAN.h>
#include <kinetis_flexcan.h>

static CAN_message_t txmsg;
static CAN_message_t rxmsg;
int messageChar = -1;
int packetSize = 0;
int byteSize = 0;
int messageCount;
int id;
int blockNumber = 0;
int totalBlocks = 0;
int lastBlockSize = 0;
int i = 0;
int spot = 0;
int firstSent = 0;
uint8_t transmittedData[1024];
uint8_t recievedData[1024];
uint8_t test1[16];
byte buffer[16];

struct Block
{
    const char *name;
    byte key[32];
    uint8_t plaintext[16];
    uint8_t ciphertext[16];
};

Block encryptionBlock = {
    .name        = "AES-256-ECB",
    .key         = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
                    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
                    0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F},
    .plaintext   = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
                    0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF},
    .ciphertext  = {0x8E, 0xA2, 0xB7, 0xCA, 0x51, 0x67, 0x45, 0xBF,
                    0xEA, 0xFC, 0x49, 0x90, 0x4B, 0x49, 0x60, 0x89}
};

AES256 aes256;



void sendBlock(){
  
  txmsg.id = 0x18ECFF18;
  txmsg.ext = 1;
  txmsg.len = 8;
  
  Serial.print("Sending Encryption Block over CAN");
  Serial.println();
  //broadcast message with pgn of 65238, which is reserved value for Network managment
  //store all values to send
  //I need to vary the size of the message.
       byte transport0[8] = {32,0,16,3,totalBlocks,0xD6,0xFE,0};
       byte transport [3][8];  
       for( int i = 0; i < 3; i++){
        transport[i][0] = i+1;
        for( int j = 1; j < 8; j++){
        transport[i][j]= encryptionBlock.ciphertext[j-1+(7*i)];
        spot++;
        if(spot>16){
          transport[i][j] = 0xFF;
        }//end if
       }//end for
      }//end for
       spot = 0;
       //send those values
       for (int i = 0;i<8;i++) txmsg.buf[i]=transport0[i];
       Can0.write(txmsg);
       delay(3);
       
       for(int i = 0; i < 3; i++){
        for(int j = 0; j < 8; j++){
          txmsg.buf[j] = transport[i][j];
         }// end for
        Can0.write(txmsg);
        delay(3);
       }//end forsend
       
}//end send

   
void decryptBlock(BlockCipher *cipher,TestVector *test){
     Serial.println("Decryption ... ");
     cipher->decryptBlock( test1,test ->ciphertext );
     Serial.println("the decrypted block");
     for(int j = 0; j<16; j++){
      
      recievedData[(j)+(16*(blockNumber-1))] = test1[j];
      Serial.print(char(recievedData[(j)+(16*(blockNumber-1))]));
      test->ciphertext[j] = ' ';
     }
}

void encryptBlock(BlockCipher *cipher,  TestVector *test){
   
    Serial.println("Encryption ... ");
    
    cipher->setKey(test->key, cipher->keySize());
    cipher->encryptBlock(buffer, test->plaintext);
    for(int i = 0; i<16; i++){
      Serial.print(char(buffer[i]));
      Serial.print(" ");
      encryptionBlock.ciphertext[i] = buffer[i];
    }
     Serial.println();
}
void listenForSerial(){
   if (Serial.available()){
    Serial.println();
    Serial.println("Message to send");
    
    while(Serial.available()){
      messageChar = Serial.read();
      transmittedData[i] = messageChar;
      Serial.print(char(messageChar));
      i++;
    }
    for(int j = i;j<1024; j++){
      transmittedData[j] = ' ';
    }
    Serial.println();
    totalBlocks = i/16;
    if(i%16 !=0){
      totalBlocks++;
      lastBlockSize = i%16;
    }
   //send each block
   for(int k = 0; k<totalBlocks; k++){ 
    for(int j = 0; j<16; j++){
      encryptionBlock.plaintext[j] = transmittedData[j+(16*k)];
      //backfill with 1's after message
      if((k == totalBlocks) && (j >= lastBlockSize)){
        encryptionBlock.plaintext[j]= 0xFF;
      }
    }
    encryptBlock(&aes256, &encryptionBlock);
    sendBlock();
   }
   i = 0;
  } 
}

void listenForCan(){
  //function this out please
  if(Can0.read(rxmsg)){
    if (rxmsg.buf[5] == 0xD6 && rxmsg.buf[6] == 0xFE && rxmsg.buf[7] == 0x0){
            //first message find length here
            firstSent = 1;
            totalBlocks = rxmsg.buf[4];
            blockNumber++;
            packetSize = rxmsg.buf[3];
            byteSize = rxmsg.buf[2] + (16*rxmsg.buf[1]);
            Serial.println();
            Serial.println("Broadcast Message Recieved...");
            id = rxmsg.id;
            messageCount = 0;
            
     }
     if(firstSent && rxmsg.id == id){
    
      if (rxmsg.buf[0] == (messageCount+1)){
       
            messageCount = rxmsg.buf[0];
            for(int i = 1; i<8; i++){
              encryptionBlock.ciphertext[(i-1)+(7*(rxmsg.buf[0]-1))] = rxmsg.buf[i];
            }
      }
      //whole message seen
      if(rxmsg.buf[0] >= 3 && rxmsg.buf[0] != 32){
            firstSent = 0;
            decryptBlock(&aes256,&encryptionBlock);
      }
     }
     if(blockNumber >= totalBlocks && messageCount == 3){
      Serial.println();
      Serial.println("Message Finished");
      blockNumber = 0;
      for(int i = 0; i<(totalBlocks*16); i++){
        Serial.print(char(recievedData[i]));
        if(i%17 == 16){
          Serial.println();
        }
      }
      Serial.println();
      totalBlocks = 0;
     } 
    
  }
  
}


void setup()
{
    Serial.begin(9600);
    delay(100);
    
    Can0.begin(250000);
    CAN_filter_t allPassFilter;
    allPassFilter.id=0;
    allPassFilter.ext=1;
    allPassFilter.rtr=0;
  
  //leave the first 4 mailboxes to use the default filter. Just change the higher ones
  for (uint8_t filterNum = 4; filterNum < 16;filterNum++){
    Can0.setFilter(allPassFilter,filterNum);
  }
  Serial.println("AES encryption over CAN");
   
}

void loop()
{
 
  listenForSerial();
  listenForCan();
}
