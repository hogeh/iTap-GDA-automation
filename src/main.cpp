#include <Arduino.h>
#include "constants.h"
#include "default.h"


void initializesystem();



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(VALVE1, OUTPUT);
  pinMode(VALVE2, OUTPUT);
  pinMode(VALVE3, OUTPUT);
  pinMode(VALVE4, OUTPUT);
  initializesystem();
}

void openclosevalve(int valveno, int valveopentime ,int valevedelay){
  if (valveopentime>=1){  /if valveopentim is positive..
    digitalWrite(valveno, LOW);  //then open valve
    Serial.print("Valve ");
    Serial.print(valveno);       
    Serial.println(" is opened");
    delay(valveopentime);    //wait valveopentime 
  }
  if (valveopentime!=1){  // if valveopentim is NOT 1
    digitalWrite(valveno, HIGH);  //then close valve
    Serial.print("Valve ");
    Serial.print(valveno);
    Serial.println(" is closed");
   }
  delay(valevedelay); //delay a bit untl process continues
}


void initializesystem(){
  Serial.println("initializehx711");  
  openclosevalve(VALVE1,-1,0);// close all valves
  Serial.println("Close valve 1");
  openclosevalve(VALVE2,-1,0);
  Serial.println("Close valve 2");
  openclosevalve(VALVE3,-1,0);
  Serial.println("Close valve 3");
  openclosevalve(VALVE4,-1,0);
  Serial.println("Close valve 4");
}

void contactserver(){

}
void  waitforbottle(){

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
    calibrate();
   } else {
   if (mode == 3){
      cip();
    } else {
      fill();
    }
  }
}