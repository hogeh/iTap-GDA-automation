#include <Arduino.h>
#include <ArduinoJson.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include "default.h"
#include "display.h"
#include "constants.h"
#include "leds.h"
#include "fileops.h"
#include "valves.h"
#include "language.h"
#include "scale.h"
#include "webpages.h"
#include "webserver.h"


void calibrateCO2()
{
 }
 
void checkCO2level()
{
}


void bottleerror(){
  String message3="No known bottletype recognized!";
  showtext(message3,2);
  setledcolor(red);
  delay(1500);
}

void emergencystop(){
  closeallvalves();
  int count=0;
  int restartin=7;
  message="Emergency stop, restarting in "+String(restartin-count);
  showtext(message);
   while (webmode==1){
    setledcolor(red);
    setfillleds(1000,1000,black);
    delay(400);
    setledcolor(black);
    setfillleds(1000,1000,red);
    delay(400);
    count++;
    if (count==restartin){
       ESP.restart();
    }
  }
}

void manualmode(){
  setledcolor(bianchi);
  int weight;
  message="Manual mode! ";
  showtext(message);
  while (webmode==2){
    weight=getweightfromscale();
    String message2="Weight: "+ String(weight) +"g";
    setfillleds(weight,1000,bianchi);
    showtext(message2,1); 
  }
  setledcolor(black);
}

void scalemode(){
  setledcolor(purple);
  int weight;
  while (webmode==3){
    scalesettle();
    weight=getweightfromscale();
    String message2="Scale mode! Weight: "+ String(weight) + "g";
    setfillleds(weight,1000,purple);
    showtext(message2,1); 
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
  while (wait  && !webmode){
    scalesettle();
    int currentweight = getweightfromscale();
    String message2="Waiting for load! "+ String(wait) + " cycles left! Weight: " + String(currentweight) + "g";
    showtext(message2,1);
    if (currentweight>threshold){
      wait=0;
      load=currentweight;
    } else {
      wait--;
      setledcolor(ledcolor,waitcycles,wait);
      delay(333);
      setledcolor(black);
      delay(100);
    }
  }
  checkwebmode(webmode);
  return load;
}

void waitforloadrelease(){
  setledcolor(green); 
  while (getweightfromscale()>scaletolerance  && !webmode){
    String message2="Release bottle! Weight " + String(getweightfromscale()) + "g";
    showtext(message2);
  }
  checkwebmode(webmode);
  setledcolor(black); 
  setfillleds(1,1,black);
  scalesettle();
  closeallvalves();
}


void  floodbottle(){  //CO2 purging
  openclosevalve(1, purgein ,purgeinpostdelay); //Opens the CO2 in valve for certain time
  for (int i = 2; i <= purgecycles; i++) { 
   String message2="Flood CO2: "+String(i);
   showtext(message2,1);
   openclosevalve(4, purgeout ,purgeoutpostdelay); //opens the fast CO2 out valve for a certain time
   openclosevalve(1, purgein ,purgeinpostdelay); //Opens the CO2 in valve for certain time
  }
}


int manufillbottle(int bottle[]=defaultbottle,int ledcolor[]=beer){
  int filllevel=getweightfromscale()-bottle[1];
  int fillmax=filllevel;
  while (filllevel>-scaletolerance  && !webmode){
    String message2="Fill weight: "+String(filllevel) + "g";
    showtext(message2,1);
    setfillleds(filllevel,bottle[0],ledcolor);
    filllevel=getweightfromscale()-bottle[1];
    if (filllevel>fillmax) {
      fillmax=filllevel;
    }
  }
  return fillmax;
}

void autofillbottle(int bottle[]=defaultbottle,int ledcolor[]=beer){
  setledcolor(black);
  int filllevel=getweightfromscale()-bottle[1];
  while (filllevel<bottle[0]  && !webmode){
    openclosevalve(2,1); //Opens the beer valve 
    openclosevalve(3,1); //Opens the CO2 in valve 
    while (filllevel<bottle[0]  && !webmode){
      String message2="Füllgewicht: "+ String(filllevel) + "g";
      showtext(message2,1);
      setfillleds(filllevel,bottle[0],ledcolor);
      if (filllevel<-scaletolerance){
        webmode=1;
        String message2="Emergencystop: "+ String(-scaletolerance) + "g";
        showtext(message2,1);
      }
      filllevel=getweightfromscale()-bottle[1];
    }
    openclosevalve(2,0); //Closes the beer valve 
    openclosevalve(3,0); //closes the CO2 in valve
    scalesettle();
    filllevel=getweightfromscale()-bottle[1];
   }
  checkwebmode(webmode);
} 

///// Main Processes: Calibrate/Fill/CIP

int cipprocess(){ //bottle filler cleaining in place process
  message="CIP process" + String(bottletolerance);
  showtext(message);
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
  message="Fillprocess";
  showtext(message);
  setzeroscale();
  int bottleweight=waitforload(waitforfillbottle,bottle[0][1]*(1-2*bottletolerance/100),beer);
  if (bottleweight){
    int bottletype=getbottletype(bottleweight);
    if (!bottletype){
      bottleerror();
     } else { 
      floodbottle();
      autofillbottle(bottle[bottletype-1],beer);
      openclosevalve(4,1);
    }
    waitforloadrelease();
    openclosevalve(4,0);
 }
 return bottleweight;
}



void calibrateprocess(){
  message="Calibration prozess";
  showtext(message);
  setzeroscale();
  message="Calibration start";
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
        String message2="Fill weight: "+ String(bottle[i][0]) + "g";
        showtext(message2,1);
        waitforloadrelease();
        writeconfigdatatofile();
      } else {
        String message3="Calibration error";
        showtext(message3,3);
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
  setledcolor(black);
}

void testscale(){
  message="Testscale";
  showtext(message);
  while (getweightfromscale()>scaletolerance){
     String message2="Weight: "+ String(getweightfromscale()>scaletolerance) +"g" ;
     showtext(message2,1);
     setledcolor(red); 
  }  
  setledcolor(black);
  setzeroscale();
  int webserveron=0;
  int pressure=abs(getweightfromscale());
  unsigned long start = millis ();
  int maxweight=500;
   while ((millis () - start<3000 || webserveron)){
    String message2="Weight: "+ String(pressure) +"g - Webserver: " + webserveron;
    showtext(message2,1);
    if (webserveron){
      setfillleds(maxweight-pressure,maxweight,bianchi);
    } else {
      setfillleds(maxweight-pressure,maxweight,orange);
    }
    if (pressure>maxweight){
      if (webserveron){
        String message2="Webserver off";  showtext(message2,1);
        stopwebserver();
        setfillleds(maxweight,maxweight,orange);
        delay(1000); 
        webserveron=0;
      } else {
        String message2="Webserver ON";  showtext(message2,1);
        startwebserver();
        setfillleds(maxweight,maxweight,bianchi);
        delay(1000); 
        webserveron=1;
      }
    } 
    pressure=abs(getweightfromscale());
 }
  setfillleds(1,1,black);
}



void setup() {
  message="Initialization";
  showtext(message);
  startleds();
  pinMode(VALVE1, OUTPUT);
  pinMode(VALVE2, OUTPUT);
  pinMode(VALVE3, OUTPUT);
  pinMode(VALVE4, OUTPUT);
  closeallvalves();
  startdisplay();
  startscale();
  startspiffs(); 
  set_language();
  readconfigdatafromfile();
//  startwebserver();
  testscale();
  calibrateprocess();
  setledcolor(black);
  startwebserver();
}

void loop(){
  //calibrateprocess();   //Mode=2: calibration process
  int isbottle=fillprocess();
  while (isbottle){
    isbottle=fillprocess();// default process: bottle filling
  } 
  cipprocess();//Mode=1: cleaning process
}

