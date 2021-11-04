#include <WiFi.h>
#include <ESPAsyncWebServer.h>

IPAddress local_ip(192,168,4,1);
IPAddress gateway(192,168,4,1);
IPAddress subnet(255,255,255,0);


AsyncWebServer server(80);


void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}


void startwebserver(){
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    webmode=0;
    request->send(200, "text/html", mainmenu());
  });
  
  server.on("/settings", HTTP_GET, [](AsyncWebServerRequest *request){
    webmode=0;
    request->send(200, "text/html", settingform());
  });
  
  server.on("/reset", HTTP_GET, [](AsyncWebServerRequest *request){
    webmode=0;
    request->send(200, "text/html", mainmenu());
   });
  
  server.on("/scalecalib", HTTP_GET, [](AsyncWebServerRequest *request){
    webmode=3;
    request->send(200, "text/html", scalecalibform());
   });


   server.on("/testscale", HTTP_GET, [](AsyncWebServerRequest *request){
 //  webmode=3;
 //   request->send(200, "text/html", scalecalibform());
   });
 
  server.on("/setscale", HTTP_GET, [](AsyncWebServerRequest *request){
    if (request->hasParam("referenceweight")) {
      int referenceweight = request->getParam("referenceweight")->value().toInt();
      if (referenceweight) {
        setscalefactor(referenceweight);
       // webmode=0;
        message="Scale calibration succeed!";
        showtext(message);
      } else {
        String message3="Scale calibration failed!";
        showtext(message3,2);
      }
      request->send(200, "text/html", scalecalibform());
   }
  });

  server.on("/manuop", HTTP_GET, [](AsyncWebServerRequest *request){
    valvestat1=0;
    valvestat2=0;
    valvestat3=0;
    valvestat4=0;
    closeallvalves();
    webmode=2;
    request->send(200, "text/html", manuop());
  }); 
  
  server.on("/emergency", HTTP_GET, [](AsyncWebServerRequest *request){
    webmode=1;
    valvestat1=0;
    valvestat2=0;
    valvestat3=0;
    valvestat4=0;
    request->send(200, "text/html", emergencyform());
  });
 
 server.on("/manual0", HTTP_GET, [](AsyncWebServerRequest *request){
    webmode=0;
    request->send(200, "text/html", manuop());
  });
 
 server.on("/manual1", HTTP_GET, [](AsyncWebServerRequest *request){
    webmode=2;
    request->send(200, "text/html", manuop());
  });
 
 server.on("/manuop10", HTTP_GET, [](AsyncWebServerRequest *request){
    valvestat1=0;
    openclosevalve(1, valvestat1);
    request->send(200, "text/html", manuop());
  });
 
  server.on("/manuop11", HTTP_GET, [](AsyncWebServerRequest *request){
    valvestat1=1;
    openclosevalve(1, valvestat1);
    request->send(200, "text/html", manuop());
  });
 
  server.on("/manuop20", HTTP_GET, [](AsyncWebServerRequest *request){
    valvestat2=0;
    openclosevalve(2, valvestat2);
    request->send(200, "text/html", manuop());
  });
 
  server.on("/manuop21", HTTP_GET, [](AsyncWebServerRequest *request){
    valvestat2=1;
    openclosevalve(2, valvestat2);
    request->send(200, "text/html", manuop());
 });
 
  server.on("/manuop30", HTTP_GET, [](AsyncWebServerRequest *request){
    valvestat3=0;
    openclosevalve(3, valvestat3);
    request->send(200, "text/html", manuop());
  });
 
  server.on("/manuop31", HTTP_GET, [](AsyncWebServerRequest *request){
    valvestat3=1;
    openclosevalve(3, valvestat3);
    request->send(200, "text/html", manuop());
  });
 
  server.on("/manuop40", HTTP_GET, [](AsyncWebServerRequest *request){
    valvestat4=0;
    openclosevalve(4, valvestat4);
    request->send(200, "text/html", manuop());
  });
 
  server.on("/manuop41", HTTP_GET, [](AsyncWebServerRequest *request){
    valvestat4=1;
    openclosevalve(4, valvestat4);
    request->send(200, "text/html", manuop());
  });

server.on("/bottle1vol", HTTP_GET, [](AsyncWebServerRequest *request){
    scalesettle();
    bottle[0][0]=getweightfromscale()-bottle[0][1];
    writeconfigdatatofile();
    request->send(200, "text/html", scalecalibform());
  });
server.on("/bottle1weight", HTTP_GET, [](AsyncWebServerRequest *request){
    scalesettle();
    bottle[0][1]=getweightfromscale();
    writeconfigdatatofile();
    request->send(200, "text/html", scalecalibform());
  });
server.on("/bottle2vol", HTTP_GET, [](AsyncWebServerRequest *request){
    scalesettle();
    bottle[1][0]=getweightfromscale()-bottle[1][1];
    writeconfigdatatofile();
    request->send(200, "text/html", scalecalibform());
  });
server.on("/bottle2weight", HTTP_GET, [](AsyncWebServerRequest *request){
    scalesettle();
    bottle[1][1]=getweightfromscale();
    writeconfigdatatofile();
    request->send(200, "text/html", scalecalibform());
  });
server.on("/bottle3vol", HTTP_GET, [](AsyncWebServerRequest *request){
    scalesettle();
    bottle[2][0]=getweightfromscale()-bottle[2][1];
    writeconfigdatatofile();
    request->send(200, "text/html", scalecalibform());
  });
server.on("/bottle3weight", HTTP_GET, [](AsyncWebServerRequest *request){
    scalesettle();
    bottle[2][1]=getweightfromscale();
    writeconfigdatatofile();
    request->send(200, "text/html", scalecalibform());
  });

server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
  if (request->hasParam("purgecycles")) {
    purgecycles = request->getParam("purgecycles")->value().toInt();
  } 
  if (request->hasParam("language")) {
    language = request->getParam("language")->value().toInt();
  }
  if (request->hasParam("waitforfillbottle")) {
    waitforfillbottle = request->getParam("waitforfillbottle")->value().toInt();;
  }
  if (request->hasParam("purgein")) {
    purgein = request->getParam("purgein")->value().toInt();;
  }
  if (request->hasParam("purgeinpostdelay")) {
    purgeinpostdelay = request->getParam("purgeinpostdelay")->value().toInt();;
  }
  if (request->hasParam("purgeout")) {
    purgeout = request->getParam("purgeout")->value().toInt();;
  }
  if (request->hasParam("purgeoutpostdelay")) {
    purgeoutpostdelay = request->getParam("purgeoutpostdelay")->value().toInt();;
  }
  if (request->hasParam("bottletolerance")) {
    bottletolerance = request->getParam("bottletolerance")->value().toFloat();;
  }
 if (request->hasParam("bottle1vol")) {
    bottle[0][0] = request->getParam("bottle1vol")->value().toInt();;
  }
    if (request->hasParam("bottle1weight")) {
    bottle[0][1] = request->getParam("bottle1weight")->value().toInt();;
  }
  if (request->hasParam("bottle2vol")) {
    bottle[1][0] = request->getParam("bottle2vol")->value().toInt();;
  }
    if (request->hasParam("bottle2weight")) {
    bottle[1][1] = request->getParam("bottle2weight")->value().toInt();;
  }
  if (request->hasParam("bottle3vol")) {
    bottle[2][0] = request->getParam("bottle3vol")->value().toInt();;
  }
    if (request->hasParam("bottle3weight")) {
    bottle[2][1] = request->getParam("bottle3weight")->value().toInt();;
  }
  if (request->hasParam("waitforcalibrationbottle")) {
    waitforcalibrationbottle = request->getParam("waitforcalibrationbottle")->value().toInt();;
  }
  if (request->hasParam("waitforcipbottle")) {
    waitforcipbottle = request->getParam("waitforcipbottle")->value().toInt();;
  }
  if (request->hasParam("cleancycles")) {
    cleancycles = request->getParam("cleancycles")->value().toInt();;
  }
  if (request->hasParam("cleanpurgeout")) {
    cleanpurgeout = request->getParam("cleanpurgeout")->value().toInt();;
  }
  if (request->hasParam("cleanschmockeout")) {
    cleanschmockeout = request->getParam("cleanschmockeout")->value().toInt();;
  }
   writeconfigdatatofile();
   set_language();
   request->send(200, "text/html", mainmenu());
});
  
server.onNotFound(notFound);

server.begin();
}   