  void startdisplay(){
    Serial.begin(115200);
  } 


void showtext(String &messagetext){
 Serial.println("Displaytext: "+ messagetext);
}