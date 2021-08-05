// Variables to be stored in config file
int mode=1;
int language=1;
int purgecycles=2;
int purgein=1300;
int purgeinpostdelay=100;
int purgeout=1200;
int purgeoutpostdelay=100;
float bottletolerance=20;
int bottletypes=3;
int bottle[3][2]={{330,270},{500,380},{750,500}};
int cleancycles=5;
int cleanpurgeout=2000;
int cleanschmockeout=5000;
int waitforcalibrationbottle=5;
int waitforfillbottle=30;
int waitforcipbottle=5;
int settletolerance=11000;
int settlecycles=15;
int settlecycledelay=0;
int zeroscale=531033;
int scalefactor=1145;
int stripeleds=20;
int stripematrix=1;
int walvestat1=0;
int walvestat2=0;
int walvestat3=0;
int walvestat4=0;
int webmode=0;
int scaletolerance=20;
float coro =  10;                 //Co Ro is initialized to 10 kilo ohms



/***********************Software Related Macros************************************/
#define         CALIBARAION_SAMPLE_TIMES     (50)    //define how many samples you are going to take in the calibration phase
#define         CALIBRATION_SAMPLE_INTERVAL  (500)   //define the time interal(in milisecond) between each samples in the
                                                     //cablibration phase
#define         READ_SAMPLE_INTERVAL         (50)    //define how many samples you are going to take in normal operation
#define         READ_SAMPLE_TIMES            (5)     //define the time interal(in milisecond) between each samples in 
                                                     //normal operation
