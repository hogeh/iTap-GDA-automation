  void startdisplay(){
    Serial.begin(115200);
  } 


void showtext(String &messagetext, int line=0){
 Serial.println("Displaytext: " + message + "    "+messagetext);
}