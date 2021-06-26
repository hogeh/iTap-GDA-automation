#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(LED02MAX+1, LED01, NEO_GRB + NEO_KHZ800);

void startleds(){
  pixels.begin(); // This initializes the NeoPixel library.
}

void setledcolor(int color[]=white,int max=1,int dimvalue=1,int ledno=0){
  int ledcolor[3];
  for (int i = 0; i <= 2; i++) { 
      ledcolor[i]=color[i]*dimvalue/max;
  }
  pixels.setPixelColor(ledno, pixels.Color(ledcolor[1],ledcolor[0],ledcolor[2]));
  pixels.show(); // This sends the updated pixel color to the hardware.
}

void setfillleds(int current,int max,int ledcolor[]){
  int steps=max/stripeleds;
  int ledno=0;
  for (int i = 0; i <= stripeleds/stripematrix-1; i++) { 
    for (int j = 1; j <= stripematrix; j++) { 
      ledno=i*stripematrix+j;
      if (current>=ledno*steps){
        setledcolor(ledcolor,1,1,ledno);
      } else {
        setledcolor(black,1,1,ledno);
       }
    }
  }
  ledcolor[0]=(255-current*255/max);
  setledcolor(ledcolor);
}