#define VALVE1 15  //ESP32 PIN
#define VALVE2 18  //ESP32 PIN
#define VALVE3 0   //ESP32 PIN
#define VALVE4 4   //ESP32 PIN
#define LOADCELL_DOUT_PIN  17   //ESP32 PIN
#define LOADCELL_SCK_PIN  5    //ESP32 PIN
#define LED01 16  //ESP32 PIN
#define LED02MAX 20  //Number of LEDs on LED stripe
#define Dis_PIN  25   //Display 




int valveno[]  = {VALVE1,VALVE2,VALVE3,VALVE4};
String valvename[] = {"CO2in","Beer in","CO2 slow out","CO2 fast out"};

const char* ssid = "iTap_bottlefiller";
const char* password = "Prost!#####";

const char* filename = "/configparams.json";

int defaultbottle[] = {500,380};
// RGB constances
int red[] = { 255, 0, 0 };
int yellow[] = { 255,255, 0 };
int beer[] = { 128,94, 0 };
int blue[] = { 0, 0 , 255};
int steelblue[] = { 99,184,255};
int green[] = { 0,255,  0 };
int purple[] = {  170,0, 255 };
int white[] = { 255, 255, 255 };
int orange[]={255,128,0};
int darkgray[]={80,80,80};
int gray[]={80,80,80};
int black[]={0,0,0};
int bianchi[]={61, 207, 194};

