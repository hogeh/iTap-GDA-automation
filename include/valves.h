
void openclosevalve(int valve, int valveopentime ,int valevedelay=0){
  if (valveopentime>=1){  //if valveopentim is positive..
    digitalWrite(valveno[valve-1], LOW);  //then open valve
    String message2= "Valve "+ String(valve) + "opened";       
    showtext(message2,1);
    delay(valveopentime);    //wait valveopentime 
  }
  if (valveopentime!=1){  // if valveopentime is NOT 1
    digitalWrite(valveno[valve-1], HIGH);  //then close valve
    String message2= "Valve "+ String(valve) + "closed";       
    showtext(message2,1);
   }
  delay(valevedelay); //delay a bit untl process continues
}

void closeallvalves(){  // close all valves
  openclosevalve(1,0);
  openclosevalve(2,0);
  openclosevalve(3,0);
  openclosevalve(4,0);
 }
