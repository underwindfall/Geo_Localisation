#include <LiquidCrystal.h>
#include <EEPROM.h>  // read(address) write(address, value) :ecrit l'octet value à l'adresse address (0 à 1023) 
#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>

SoftwareSerial ss(3,2); 
File myFile,mycsvFile;
int i=0,tmp=0;
const int Cs=10;
char input;
char arrInput[10]={0};

void setup() {
  Serial.begin(19200);
    while (!Serial) {
  }
  ss.begin(9600);
  Serial.print("Initializing SD card...");  //Initializing SD card...
  pinMode(Cs, OUTPUT);

   if (!SD.begin(Cs)) {  //Card failed, or not present
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  
  Serial.println("Card Initialized."); 
  myFile=SD.open("listgps.txt");
  if(myFile){ 
    Serial.println("Vous avez les fichers dans le SD card:");
   while (myFile.available()) {
      Serial.write(myFile.read());
    }
    myFile.close();
  }else{
    Serial.println("Error openning listgps.txt");
  }
   Serial.println("Vous pouvez choisir quel ficher que vous voulez exporter:");
   memset(arrInput, 0x00, sizeof(arrInput));
}

void loop() {
  if(Serial.available()>0&&i<=10){
     input=(char)Serial.read();
    if(input != '\r')
      {
         arrInput[i]=input;
             i++;        
      }
        mycsvFile = SD.open(arrInput);
            if(mycsvFile){
              Serial.println("Les donnes de ficher:");
              while (mycsvFile.available()) {
              Serial.write(mycsvFile.read());
             }
             mycsvFile.close();
             Serial.println("Ce ficher a  ete lu totoallement");
            }else{
              Serial.println("En train de lire ce ficher ");
            }         
  }
  
   
  
}
