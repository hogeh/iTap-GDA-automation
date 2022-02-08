#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(LED02MAX+1, LED01, NEO_GRB + NEO_KHZ800);

void startleds(){
  pixels.begin(); // This initializes the NeoPixel library.
}

void setledcolor(int color[]=black,int max=1,int dimvalue=1,int ledno=0,int ledp=1){
  int ledcolor[3];
  for (int i = 0; i <= 2; i++) { 
      ledcolor[i]=color[i]*abs(dimvalue)/max;
  }
  if (ledno){ //to be solved later!!  no clue why for the single LED the RGB colors are scrambled!!!!!
    pixels.setPixelColor(ledno, pixels.Color(int(ledcolor[0]*ledp),int(ledcolor[1]*ledp),int(ledcolor[2]*ledp)));
  } else {
    pixels.setPixelColor(ledno, pixels.Color(ledcolor[1],ledcolor[0],ledcolor[2]));
  }
  pixels.show(); // This sends the updated pixel color to the hardware.
}

void setfillleds(int current,int max,int thisledcolor[],int ledp=1){
  int steps=max/stripeleds;
  int ledno=0;
  for (int i = 0; i <= stripeleds/stripematrix-1; i++) { 
    for (int j = 1; j <= stripematrix; j++) { 
      ledno=i*stripematrix+j;
      if (current>=ledno*steps){
        setledcolor(thisledcolor,1,1,ledno,ledp);
      } else {
        setledcolor(black,1,1,ledno);
       }
    }
  }
  setledcolor(thisledcolor,max,current);
}

void testleds(){
  
}