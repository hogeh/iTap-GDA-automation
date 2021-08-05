#include <Arduino.h>
#include <ArduinoJson.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include "display.h"
#include "constants.h"
#include "default.h"
#include "leds.h"
#include "fileops.h"
#include "valves.h"
#include "language.h"
#include "scale.h"
#include "webpages.h"
#include "webserver.h"





void bottleerror(){
  String message="No known bottletype recognized!";
  showtext(message);
  setledcolor(red);
  delay(1500);
}

void emergencystop(){
  closeallvalves();
  while (webmode==1){
    setledcolor(red);
    setfillleds(1000,1000,red);
    delay(333);
    setledcolor(black);
    setfillleds(1000,1000,black);
    delay(333);
  }
  String message="Emergency stop";
  showtext(message);
}

void manualmode(){
  setledcolor(bianchi);
  int weight;
  while (webmode==2){
    weight=getweightfromscale();
    String message="Manual mode! Weight: "+ String(weight) +"g";
    setfillleds(weight,1000,bianchi);
    showtext(message); 
  }
  setledcolor(black);
}

void scalemode(){
  setledcolor(purple);
  int weight;
  while (webmode==3){
    scalesettle();
    weight=getweightfromscale();
    String message="Scale mode! Weight: "+ String(weight) + "g";
    setfillleds(weight,1000,purple);
    showtext(message); 
  }
  setledcolor(black);
}

void checkwebmode(int mode){
  if (mode==0){
    return;
  } else {
    if (mode==1){
      emergencystop();
    } else {
      if (mode==2){
         manualmode();
      } else {
        if (mode==3){
         scalemode();
      } else {
        Serial.println("mode not found "+ String(mode));
      }

      }
    }
  }
}


int getbottletype(int weight){
  int type=0;
  for (int i = 0; i <= bottletypes-1 ; i++) {
    if ((weight>=bottle[i][1]*(1-bottletolerance/100)) && (weight<=bottle[i][1]*(1+bottletolerance/100))){
      type=i+1;
      Serial.println(type);
      bottle[i][1]=weight;
    }
  }
  return type;
}


int  waitforload(int waitcycles,int threshold,int ledcolor[]){
  int wait=waitcycles;
  int load=0;
  String message="Waiting for load";
  showtext(message);
  while (wait  && !webmode){
    scalesettle();
    int currentweight = getweightfromscale();
    String message=String(wait)+" cycles left! Weight: " + String(currentweight) + "g";
    showtext(message);
    if (currentweight>threshold){
      message="Load detected! Weight: "+ String(currentweight) + "g";
      showtext(message);
      wait=0;
      load=currentweight;
   } else {
      wait--;
      setledcolor(ledcolor,waitcycles,wait);
      delay(500);
      setledcolor(black);
      delay(200);
    }
  }
  checkwebmode(webmode);
   return load;
}

void waitforloadrelease(){
  int loop=1;
  String message;
   while (getweightfromscale()>scaletolerance  && !webmode){
    String message="Release bottle! Weight " + String(getweightfromscale()) + "g";
    showtext(message);
    if (loop){
     setledcolor(green); 
    } else {
     setledcolor(black); 
    }
    loop=!loop;
    delay(750);
  }
  checkwebmode(webmode);
  setledcolor(black); 
  setfillleds(1,1,black);
  scalesettle();
  closeallvalves();
}

void  floodbottle(){  //CO2 purging
  setledcolor(gray);
  openclosevalve(1, purgein ,purgeinpostdelay); //Opens the CO2 in valve for certain time
  for (int i = 2; i <= purgecycles; i++) { 
   setledcolor(darkgray);
   openclosevalve(4, purgeout ,purgeoutpostdelay); //opens the fast CO2 out valve for a certain time
   setledcolor(gray);
   openclosevalve(1, purgein ,purgeinpostdelay); //Opens the CO2 in valve for certain time
 }
}

int manufillbottle(int bottle[]=defaultbottle,int ledcolor[]=beer){
  int filllevel=getweightfromscale()-bottle[1];
  int fillmax=filllevel;
  while (filllevel>scaletolerance  && !webmode){
    String message="Fill weight: "+String(filllevel) + "g";
    showtext(message);
    setfillleds(filllevel,bottle[0],ledcolor);
    filllevel=getweightfromscale()-bottle[1];
    if (filllevel>fillmax) {
      filllevel=fillmax;
    }
  }
  return filllevel;
}

void autofillbottle(int bottle[]=defaultbottle,int ledcolor[]=beer){
  setledcolor(black);
  int filllevel=getweightfromscale()-bottle[1];
  while (filllevel<bottle[0]  && !webmode){
    openclosevalve(2,1); //Opens the beer valve 
    openclosevalve(3,1); //Opens the CO2 in valve 
    while (filllevel<bottle[0]  && !webmode){
      String message="Füllgewicht: "+ String(filllevel) + "g";
      showtext(message);
      setfillleds(filllevel,bottle[0],ledcolor);
      if (filllevel<-scaletolerance){
        webmode=1;
      }
      filllevel=getweightfromscale()-bottle[1];
    }
    checkwebmode(webmode);
    openclosevalve(2,0); //Closes the beer valve 
    openclosevalve(3,0); //closes the CO2 in valve
    scalesettle();
  }
} 

void ventbottle(){
  setledcolor(darkgray);
  openclosevalve(4, purgeout ,purgeoutpostdelay); //opens the fast overflow valve for a certain time
}
///// Main Processes: Calibrate/Fill/CIP

int cipprocess(){ //bottle filler cleaining in place process
  int bottleweight=waitforload(waitforcipbottle,bottle[0][1]*(1-2*bottletolerance/100),blue);
  if (bottleweight){
    int bottletype=getbottletype(bottleweight);
    if (!bottletype){
      bottleerror();
    } else { 
      autofillbottle(bottle[bottletype-1],blue);
      openclosevalve(2, 1); //opens the beer valve 
      for (int i = 1; i <= cleancycles; i++) { 
        setledcolor(darkgray);
         openclosevalve(4, cleanpurgeout); //opens the overflow valve for a certain time
         setledcolor(steelblue);
         openclosevalve(3, cleanschmockeout); //opens the overflow valve for a certain time
      }
      openclosevalve(2, 0); //closes the beer valve
    }
    waitforloadrelease();
  }
  return bottleweight;
}     




int fillprocess(){  // bottle fill process
  int bottleweight=waitforload(waitforfillbottle,bottle[0][1]*(1-2*bottletolerance/100),yellow);
  if (bottleweight){
    int bottletype=getbottletype(bottleweight);
    if (!bottletype){
      bottleerror();
     } else { 
      floodbottle();
      autofillbottle(bottle[bottletype-1],beer);
      ventbottle();
    }
    waitforloadrelease();
 }
 return bottleweight;
}



void calibrateprocess(){
  setledcolor(purple);
  scalesettle();
  setzeroscale();
  String message="Calibration start";
  showtext(message);
  for (int i = 0; i <= bottletypes-1 ; i++) {
    int bottleweight=waitforload(waitforcalibrationbottle,bottle[0][1]*(1-2*bottletolerance/100),purple);
    if (bottleweight){
      bottle[i][1]=bottleweight;
      int fullweight=manufillbottle(bottle[i],purple);
      if (fullweight<0){
        fullweight=waitforload(waitforcalibrationbottle*2,bottle[i][1]*2,purple);
      }
      if (fullweight){
        bottle[i][0]=fullweight-bottle[i][1];
        message="Fill weight: "+ String(bottle[i][0]) + "g";
        showtext(message);
        waitforloadrelease();
        writeconfigdatatofile();
      } else {
        message="Calibration error";
        showtext(message);
        i=bottletypes;
        setledcolor(red);
        delay(2000);
      }
    } else {
      message="Skipped Calibration";
      showtext(message);
      i=bottletypes;
    }
  }
  delay(500);
  setledcolor(black);
}

void testscale(){
  scalesettle();
  setzeroscale();
  int pressure=abs(getweightfromscale());
  while (pressure<=500  && !webmode){
    String message="Weight: "+ String(pressure) +"g";
    showtext(message);
    setfillleds(pressure,500,beer);
    pressure=abs(getweightfromscale());
  }
  checkwebmode(webmode);
  String message="Scale test successful!";
  showtext(message);
  setfillleds(0,500,beer);
  setledcolor(green);
  delay(1000);
}



void setup() {
// 4 valve controles:
  pinMode(VALVE1, OUTPUT);
  pinMode(VALVE2, OUTPUT);
  pinMode(VALVE3, OUTPUT);
  pinMode(VALVE4, OUTPUT);
  startdisplay();
 // RGB LED for status indication
  startleds();
// Scale
  startscale();
  setledcolor(white);
  closeallvalves();
  setzeroscale();
  startspiffs(); 
  readconfigdatafromfile();
  set_language();
  setup_webserver();
  setledcolor(black);
}

void loop(){
  calibrateprocess();   //Mode=2: calibration process
  fillprocess(); // default process: bottle filling
  cipprocess();//Mode=1: cleaning process
}

