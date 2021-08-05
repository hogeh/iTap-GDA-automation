#define VALVE1 15
#define VALVE2 18
#define VALVE3 0
#define VALVE4 4
#define LOADCELL_DOUT_PIN  17
#define LOADCELL_SCK_PIN  5
#define LED01 16
#define LED02MAX 20
#define MQ_PIN  25     //define which analog input channel you are going to use




int valveno[]  = {VALVE1,VALVE2,VALVE3,VALVE4};
String valvename[] = {"CO2in","Beer in","CO2 slow out","CO2 fast out"};

const char* ssid = "iTap_bottlefiller";
const char* password = "Prost!#####";

const char* filename = "/configparams.json";

int defaultbottle[] = {500,380};
// RGB constances
int red[] = { 255, 0, 0 };
int yellow[] = { 255,255, 0 };
int beer[] = { 255,188, 0 };
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
int bianchioff[]={42, 137, 129};