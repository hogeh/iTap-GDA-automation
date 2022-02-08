#include "HX711.h"

HX711 scale;
 void checkwebmode(int mode);

void startscale(){
   scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
}

int getweightfromscale(){
   return (scale.read()-zeroscale)/scalefactor;
}


void scalesettle(){
   int cycleno=1;
   long currentscale = scale.read();
    int tobesettled=0;

   while (cycleno<settlecycles){
      int delta=abs(currentscale - scale.read());
      if (delta>settletolerance){
         String message2="Scale sattling: "+ String(delta);
         showtext(message2,1);
         setledcolor(red);
         cycleno=1;
         currentscale = scale.read(); 
         tobesettled=1;
      } else {
         cycleno++;
         setledcolor(black);
      }
      delay(settlecycledelay);
   }
   if (tobesettled){
      message="Scale settled!";
      showtext(message);
   }
}

void setzeroscale(){
 scalesettle();
 zeroscale=scale.read();
}

void setscalefactor(int referenceweight){
   Serial.println("referenceweight: "  );
   scalesettle();
   Serial.println("Scalefactor: "  );
    scalefactor= (scale.read()-zeroscale)/referenceweight;
   writeconfigdatatofile();
   readconfigdatafromfile();
}