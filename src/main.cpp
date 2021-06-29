#include <Arduino.h>
#include "constants.h"
#include "default.h"
#include "HX711.h"

HX711 scale;


void initializesystem();



void setup() {
  Serial.begin(115200);
 // 4 valve controles:
  pinMode(VALVE1, OUTPUT);
  pinMode(VALVE2, OUTPUT);
  pinMode(VALVE3, OUTPUT);
  pinMode(VALVE4, OUTPUT);
// RGB LED for status indication
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(LED01, ledChannel);
  ledcAttachPin(LED02, ledChannel);
  ledcAttachPin(LED03, ledChannel);
// Scale
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
   initializesystem();
}

void openclosevalve(int valveno, int valveopentime ,int valevedelay){
  if (valveopentime>=1){  //if valveopentim is positive..
    digitalWrite(valveno, LOW);  //then open valve
    Serial.print("Valve ");
    Serial.print(valveno);       
    Serial.println(" is opened");
    delay(valveopentime);    //wait valveopentime 
  }
  if (valveopentime!=1){  // if valveopentime is NOT 1
    digitalWrite(valveno, HIGH);  //then close valve
    Serial.print("Valve ");
    Serial.print(valveno);
    Serial.println(" is closed");
   }
  delay(valevedelay); //delay a bit untl process continues
}


void initializesystem(){
  openclosevalve(VALVE1,-1,0);// close all valves
  Serial.println("Close valve 1");
  openclosevalve(VALVE2,-1,0);
  Serial.println("Close valve 2");
  openclosevalve(VALVE3,-1,0);
  Serial.println("Close valve 3");
  openclosevalve(VALVE4,-1,0);
  Serial.println("Close valve 4");
  delay(1000);
  if (scale.is_ready()) {
    Serial.println("HX711 ready");
  } else {
    Serial.println("HX711 not found.");
  }   
  
}

void contactserver(){

}
void  waitforbottle(){
  while (true){
    Serial.print("Waiting for bottle: ");
    if (scale.is_ready()) {
      long reading = scale.read();
      Serial.print("HX711 reading: ");
      Serial.println(reading);
    } else {
      Serial.println("HX711 not found.");
    }
    delay(1000); 
  }
}

 
void  purgebottle(){
  for (int i = 1; i < purgecycles; i++) { 
   openclosevalve(VALVE1, purgein ,purgeinpostdelay); //Opens the CO2 in valve for certain time
   openclosevalve(VALVE2, purgeout ,purgeoutpostdelay); //opens the overflow valve for a certain time
 }
}

void fillbottle(){
   openclosevalve(VALVE3,1,0); //Opens the CO2 in valve for certain time

} 

void waitforbottlerelease(){
  Serial.println("Close valve 2");
  while (true){}

}
void fill(){  // bottle fill process
  waitforbottle();
  purgebottle();
  fillbottle();
  waitforbottlerelease();
 }

void calibrate(){ // calibrate the scale
}

void cip(){ //bottle filler cleaining in place process
}

void loop(){
  contactserver();
  if (mode == 2 ){
    calibrate();   //Mode=2: calibration process
   } else {
   if (mode == 3){
      cip();//Mode=1: cleaning process
    } else {
      fill(); // default process: bottle filling
    }
  }
}