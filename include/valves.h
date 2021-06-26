
void openclosevalve(int valve, int valveopentime ,int valevedelay=0){
  valve=valve-1;
  if (valveopentime>=1){  //if valveopentim is positive..
    digitalWrite(valveno[valve], LOW);  //then open valve
    String message= "Valve "+ String(valve) + "opened";       
    showtext(message);
    delay(valveopentime);    //wait valveopentime 
  }
  if (valveopentime!=1){  // if valveopentime is NOT 1
    digitalWrite(valveno[valve], HIGH);  //then close valve
    String message= "Valve "+ String(valve) + "closed";       
    showtext(message);
   }
  delay(valevedelay); //delay a bit untl process continues
}

void closeallvalves(){  // close all valves
  openclosevalve(1,0);
  openclosevalve(2,0);
  openclosevalve(3,0);
  openclosevalve(4,0);
 }
