#include <SPIFFS.h>


void startspiffs(){
  if(!SPIFFS.begin(true)){
   String message3="Error  mounting SPIFFS";
   showtext(message3,2);
   return;
  }
}

String readFile(fs::FS &fs, const char * path){
  //Serial.printf("Reading file: %s\r\n", path);
  File file = fs.open(path, "r");
  if(!file || file.isDirectory()){
    String message3="Error reading file";
    showtext(message3,2);
    return String();
  }
  //Serial.println("- read from file:");
  String fileContent;
  while(file.available()){
    fileContent+=String((char)file.read());
  }
  file.close();
  //Serial.println(fileContent);
  return fileContent;
}


int writeFile(fs::FS &fs, const char * path, const char * message){
  //Serial.printf("Writing file: %s\r\n", path);
  File file = fs.open(path, "w");
  if(!file){
    //Serial.println("- failed to open file for writing");
    return 0;
  }
  int written=0;
  if(file.print(message)){
    written=1;
  } 
  file.close();
  return written;
}


void writeconfigdatatofile(){
  DynamicJsonDocument doc(1024);
   // Set the values in the document
  doc["language"] = language;
  doc["purgecycles"] = purgecycles;
  doc["purgein"] = purgein;
  doc["purgeinpostdelay"] = purgeinpostdelay;
  doc["purgeout"] = purgeout;
  doc["purgeoutpostdelay"] = purgeoutpostdelay;
  doc["bottletolerance"] = bottletolerance;
  doc["bottletypes"] = bottletypes;
  doc["bottle1vol"]=bottle[0][0];
  doc["bottle1weight"]=bottle[0][1];
  doc["bottle2vol"]=bottle[1][0];
  doc["bottle2weight"]=bottle[1][1];
  doc["bottle3vol"]=bottle[2][0];
  doc["bottle3weight"]=bottle[2][1];
  doc["cleancycles"] = cleancycles;
  doc["cleanpurgeout"] = cleanpurgeout;
  doc["cleanschmockeout"] = cleanschmockeout;
  doc["waitforcalibrationbottle"] = waitforcalibrationbottle;
  doc["waitforfillbottle"] = waitforfillbottle;
  doc["waitforcipbottle"] = waitforcipbottle;
  doc["settletolerance"] = settletolerance;
  doc["settlecycles"] = settlecycles ;
  doc["settlecycledelay"] = settlecycledelay;
  doc["zeroscale"] = zeroscale;
  doc["scalefactor"] = scalefactor;
  String JSONMessage;
  serializeJson(doc, JSONMessage);
  if (!writeFile(SPIFFS, filename, JSONMessage.c_str())){
    String message3="Parameters saving failed";
    showtext(message3,2);
  } else {
    message="Parameters saved";
    showtext(message);
  }
}

void readconfigdatafromfile(){
  String JSONMessage = readFile(SPIFFS, filename);
  StaticJsonDocument<1024>doc;                        //Memory pool
  auto error = deserializeJson(doc, JSONMessage); 
  if (error) {   //Check for errors in parsing
     String message3="Parameter loading failed";
     showtext(message3,2);
  } else {
    purgecycles=doc["purgecycles"]  ;
    language=doc["language"]  ;
    purgein=doc["purgein"]  ;
    purgeinpostdelay=doc["purgeinpostdelay"]  ;
    purgeout=doc["purgeout"]  ;
    purgeoutpostdelay=doc["purgeoutpostdelay"]  ;
    bottletolerance=doc["bottletolerance"]  ;
    bottletypes=doc["bottletypes"]  ;
    bottle[0][0]=doc["bottle1vol"] ;
    bottle[0][1]=doc["bottle1weight"];
    bottle[1][0]=doc["bottle2vol"] ;
    bottle[1][1]=doc["bottle2weight"];
    bottle[2][0]=doc["bottle3vol"];
    bottle[2][1]=doc["bottle3weight"];
    cleancycles=doc["cleancycles"]  ;
    cleanpurgeout=doc["cleanpurgeout"]  ;
    cleanschmockeout=doc["cleanschmockeout"]  ;
    waitforcalibrationbottle=doc["waitforcalibrationbottle"]  ;
    waitforfillbottle=doc["waitforfillbottle"]  ;
    waitforcipbottle=doc["waitforcipbottle"]  ;
    settletolerance=doc["settletolerance"]  ;
    settlecycles=doc["settlecycles"]   ;
    settlecycledelay=doc["settlecycledelay"]  ;
    zeroscale=doc["zeroscale"]  ;
    scalefactor=doc["scalefactor"]  ;
    message="Parameters loaded!";
    showtext(message);
  }
}
