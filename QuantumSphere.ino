#include <SPI.h>
#include <SdFat.h>
#include <SdFatUtil.h>
#include <SFEMP3Shield.h>
#include <Bounce2.h>


SdFat sd;
SFEMP3Shield MP3player;

 //Use 1kΩ resistors, connect sensor between resistor-ground
 
const int Sensor0 = A0; 
const int Sensor1 = A1; 
const int Sensor2 = A2; 
const int Sensor3 = A3; 

const int Threshold0 = 200;
const int Threshold1 = 200;
const int Threshold2 = 200;
const int Threshold3 = 200;

const long period1 = 240000; 
const long period2 = 180000;


 void setup() { 
  
  Serial.begin(9600);
  if(!sd.begin(9, SPI_HALF_SPEED)) sd.initErrorHalt();
  if (!sd.chdir("/")) sd.errorHalt("sd.chdir");
  MP3player.begin();
 } 

 void loop() {
   MP3player.setVolume(20,20);
   
   int Celda0 = analogRead(Sensor0);
     Serial.print("Sensor0 "); 
     Serial.println(Celda0);
    
   int Celda1 = analogRead(Sensor1); 
     Serial.print("Sensor1 "); 
     Serial.println(Celda1); 
    
   int Celda2 = analogRead(Sensor2);  
     Serial.print("Sensor2 "); 
     Serial.println(Celda2); 
     
   int Celda3 = analogRead(Sensor3); 
     Serial.print("Sensor3 "); 
     Serial.println(Celda3);
     Serial.println(" ");   
     
  if (Celda0 >= Threshold0){
    MP3player.stopTrack();
      while (Celda0 >= Threshold0){
      MP3player.playTrack(1);
        Celda0 = analogRead(Sensor0);
      } 
    delay (1000);
  }
  
   if (Celda0 <= Threshold0) {
   MP3player.stopTrack();
  
   unsigned long tStart1 = millis();
   for( tStart1;  (millis()-tStart1) < period1;){
     Celda0 = analogRead(Sensor0);
     Celda1 = analogRead(Sensor1);
     Celda2 = analogRead(Sensor2);
     Celda3 = analogRead(Sensor3);
     
     Serial.print("Sensor1.1 "); 
     Serial.println(Celda1);
     Serial.print("Sensor2.1 "); 
     Serial.println(Celda2);
     Serial.print("Sensor3.1 "); 
     Serial.println(Celda3);
     Serial.println(" ");
     delay (1000);
 
     if (Celda1 <= Threshold1 && Celda2 >= Threshold2 && Celda3 >= Threshold3){ 
      MP3player.stopTrack();
      
      while (Celda1 <= Threshold1 && Celda2 >= Threshold2 && Celda3 >= Threshold3){
      MP3player.playTrack(2);
        Celda0 = analogRead(Sensor0);
        Celda1 = analogRead(Sensor1); 
        Celda2 = analogRead(Sensor2); 
        Celda3 = analogRead(Sensor3);
      }
      delay (1000);
    } 
    
    if (Celda2 <= Threshold2 && Celda1 >= Threshold1 && Celda3 >= Threshold3){ 
      MP3player.stopTrack();
      
      while (Celda2 <= Threshold2 && Celda1 >= Threshold1 && Celda3 >= Threshold3){
      MP3player.playTrack(3);
        Celda0 = analogRead(Sensor0);
        Celda1 = analogRead(Sensor1); 
        Celda2 = analogRead(Sensor2); 
        Celda3 = analogRead(Sensor3);
      }
      delay (1000);
    } 
    
    if(Celda3 <= Threshold3 && Celda1 >= Threshold1 && Celda2 >= Threshold2){
      MP3player.stopTrack();
      
      while (Celda3 <= Threshold3 && Celda1 >= Threshold1 && Celda2 >= Threshold2){
      MP3player.playTrack(4);
        Celda0 = analogRead(Sensor0);
        Celda1 = analogRead(Sensor1); 
        Celda2 = analogRead(Sensor2); 
        Celda3 = analogRead(Sensor3);
      }
     delay (1000);

    } 
    else {
    MP3player.stopTrack();
    }
    
  }
  }
  MP3player.stopTrack();
     delay (1000);

   int randNumber = random(1, 6);
   unsigned long tStart2 = millis();
   for( tStart2;  (millis()-tStart2) < period2;){
    Celda0 = analogRead(Sensor0);
    Serial.print("Sensor0.2 "); 
    Serial.println(Celda0);
    Serial.println(" ");
    delay (1000);
    float fraction = ((millis()-tStart2)*90/period2);
    int i = 100 - (int)fraction;  
    MP3player.setVolume(i,i);
    
    if (Celda0 <= Threshold0){
      MP3player.stopTrack();
      while (Celda0 <= Threshold0 && (millis()-tStart2) < period2){
       MP3player.playTrack(randNumber);
       Celda0 = analogRead(Sensor0);
       delay (1000);
      }
    delay (1000);
    }
    else {
    MP3player.stopTrack();
    }
    MP3player.stopTrack();
    }
  
  delay (30000);
 }
 

