#include <LiquidCrystal.h>
#include <SPI.h>
#include <TinyGPS.h>
#include <SD.h>
#include <SoftwareSerial.h>
TinyGPS gps;
SoftwareSerial ss(3,2);
LiquidCrystal lcd(4,5,6,7,8,9);

int OnUse=0;
int count=0;
float distance=0,preflat=0,preflon=0;
const int BP0=16;
const int BP1=15;
const int BPEN=17;
const int CS=10;
const double EARTH_RADIUS=6378.137;
File myFile;
File mycsv;
int Triggerbuttonstart, Triggerbuttonend,TriggerbuttonBPEN;//confirmation quelle buttons on a appui
String SD_date,csvfile;
//TinyGPS
static void smartdelay(unsigned long ms);
static void print_float(float val, float invalid, int len, int prec);
static void print_int(unsigned long val, unsigned long invalid, int len);
static void printdate(TinyGPS &gps);
static void print_str(const char *str, int len);
static double change_degre(double d);
//obtenir la distance par longtitude et latitude
static double GetDistance(double lat1, double lng1, double lat2, double lng2);


void setup() {
  // put your setup code here, to run once:
 Serial.begin(19200); 
  while (!Serial) {
  }
  ss.begin(9600);
  pinMode(BP0,INPUT);
  pinMode(BP1,INPUT);
  pinMode(BPEN,INPUT);
  pinMode(CS,OUTPUT);
  
  lcd.begin(0,2); 
  lcd.print("Bonjour");
  lcd.setCursor(0,1);
  lcd.print("GPS");
  delay(1500);
  lcd.clear();
  //afficher l'etat des piles
  //valuer de retour entre 0 et 1023
  lcd.setCursor(0,0);
  lcd.print("Batterie:");
  lcd.setCursor(0,1);
  lcd.print(analogRead(A0)/1024.0*6.0);
  delay(3000);
  lcd.clear();

  Serial.println("Initializing SD card...");
  if(!SD.begin(CS)){
    Serial.println("Initialization failed");
    lcd.setCursor(0,0);
    lcd.print("SD:ERR");
    return;
    }
    lcd.setCursor(0,0);
    lcd.print("SD:OK");
    delay(2000);

    if(!SD.exists("listgps.txt")){
        myFile=SD.open("listgps.txt", FILE_WRITE);        
        myFile.close();
    }
//     if(SD.exists("listgps.txt"))Serial.println("listgps.txt has been created");
   
//    Serial.println("Sats HDOP date Latitude  Longitude  ");
// Serial.println("Sats HDOP Latitude  Longitude  Fix  Date       Time     Date Alt    Course Speed Card  Distance Course Card  Chars Sentences Checksum");
 // Serial.println("          (deg)     (deg)      Age                      Age  (m)    --- from GPS ----  ---- to London  ----  RX    RX        Fail");
//    Serial.println("-------------------------------------------------------------------------------------------------------------------------------------");
}

void loop() 
{
  char tmpcsv[10];
  TriggerbuttonBPEN= digitalRead(BPEN);
  Triggerbuttonstart = digitalRead(BP1);
  Triggerbuttonend=digitalRead(BP0);

  
    
  //en fonction de l'action de appuie de chaque button different, GPS va repondre des differents actions
   if(TriggerbuttonBPEN==1&&Triggerbuttonstart==0 && Triggerbuttonend==0){
    
    OnUse = 1;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("LanceGPS");
    myFile=SD.open("listgps.txt");
    if(myFile){
      int count=0;
     Serial.println("Succesfully open the listgps.txt");
                 while(myFile.available()){
                            char character=myFile.read();
                            if(character=='\n'){
                              count++;
                            }
            //                  Serial.println("myFile is available");
            //                  Serial.print("the current count is");
            //                  Serial.println(count);
                                           
                  }
                   //Serial.println("preparation for csv");
                  count++;
               
                  csvfile="GPS";
                  csvfile+=count;
                  csvfile+=".csv";                  
                 csvfile.toCharArray(tmpcsv,11);
                  myFile.close();
                  myFile=SD.open("listgps.txt",FILE_WRITE);
                  if(myFile){
                   // Serial.println(csvfile);
                    myFile.println(tmpcsv);
                    myFile.close();
                  }
                  else{
                       Serial.println("error writing to listgps.txt");
                  }
                 
    } 
    else{
              Serial.println("Error open the listgps.txt");
          }
 
                if(!SD.exists(tmpcsv)){
                  mycsv=SD.open(tmpcsv, FILE_WRITE);        
                  mycsv.close();
                  }
                   mycsv = SD.open(tmpcsv, FILE_WRITE);
                   if(mycsv){     
                      Serial.println("commence a ecrire le ficher dans"+csvfile);                   
                       mycsv.println("date,latitude,longitude,altitude,distance");
                       }
                     else{
                         // if the file didn't open, print an error:
                     Serial.println("error opening "+csvfile);
                     }
                   memset(tmpcsv, 0x00, sizeof(tmpcsv));
                   csvfile="";
                    
                   delay(1000);
                  lcd.clear();     
  }
  else if(TriggerbuttonBPEN==1&&Triggerbuttonstart==0 && Triggerbuttonend==1){
    //Terminer GPS
    OnUse = 0;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("GPS");
    lcd.setCursor(0,1);
    lcd.print("Terminer");
    Serial.println("GPS Terminer");
    mycsv.close();
    myFile.close();
  }

  else if((TriggerbuttonBPEN==1&&Triggerbuttonstart==1 && Triggerbuttonend==1)||(TriggerbuttonBPEN==1&&Triggerbuttonstart==1 && Triggerbuttonend==0)){
    //
    // afficher l'etat des piles sur l'ecran LCD
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Batterie:");
      lcd.setCursor(0, 1);
      lcd.print(analogRead(A0)/ 1024.0*6.0);
  }
  
  /******
  ***/
   
  if(OnUse == 1)
  {
      float flat,flon,falti;
      unsigned long age, date, time, chars = 0;
      unsigned short sentences = 0, failed = 0;
    //obtenir les donnes latitude et longtitude
    print_int(gps.satellites(), TinyGPS::GPS_INVALID_SATELLITES, 5);//le nombre des satellites qu'on a utilse
    preflat=flat;
    preflon=flon;
    print_int(gps.hdop(), TinyGPS::GPS_INVALID_HDOP, 5);//
    gps.f_get_position(&flat, &flon, &age);//
    print_float(flat, TinyGPS::GPS_INVALID_F_ANGLE, 10, 6);
    print_float(flon, TinyGPS::GPS_INVALID_F_ANGLE, 11, 6);
//    print_date(gps);
    print_float(gps.f_altitude(), TinyGPS::GPS_INVALID_F_ALTITUDE, 7, 2);//
    
//    lcd.begin(8,2);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(flat,6);
    lcd.setCursor(0,1);
    lcd.print(flon,6);
     
    Serial.print("\n");
    String test="";
    test=test+"latitude:"+flat+"longtitude"+flon;
    Serial.println(test);
    distance=GetDistance(preflat, preflon,flat ,flon)*1000;
    Serial.print(distance,3);
//     char* time_creat = print_date(gps);
   //if(flat <= 90.00 && flat>=-90.00 && flon <= 180.00 && flon>=-180.00)
     //
  if(flat !=1000.00 && flon!=1000.00){     
         // des que le ficher est bon d'ouvrir, ecrit dans celle:
          if (mycsv){
//          date  = print_date(gps);
        
          mycsv.print("");
          mycsv.print(",");
          mycsv.print(flat,6);
          mycsv.print(",");
          mycsv.print(flon,6);   
          mycsv.print(",");
          mycsv.print(gps.f_altitude(),6);   
          mycsv.print(",");     
          mycsv.println(distance,3);  
          Serial.println("done.");
       //   lcd.setCursor(0,1);
       //   lcd.print("OK      ");
        } else {
          //affiche un error quand on a echoue d'ouvrir
              Serial.println("error of openning");
        }
    }
   else{

   Serial.println("Error coordonne ");
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Patientez");
          lcd.setCursor(0,1);
          lcd.print("SVP");
  }
       
  }
   smartdelay(1000);
}
///GETDISTANCE
static double change_degre(double d){
   return d * PI / 180.0;
}
static double GetDistance(double lat1, double lng1, double lat2, double lng2)
{
   double changeLat1 = change_degre(lat1);
   double changeLat2 = change_degre(lat2);
   double a = changeLat1 - changeLat2;
   double b = change_degre(lng1) - change_degre(lng2);
   double s = 2 * asin(sqrt(pow(sin(a/2),2)+cos(changeLat1)*cos(changeLat2)*pow(sin(b/2),2)));
   s = s * EARTH_RADIUS;
   s = round(s * 10000) / 10000;
   return s;
}
//TINYGPS_GETPOSITION
static void smartdelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}


static void print_float(float val, float invalid, int len, int prec)
{
  if (val == invalid)
  {
    while (len-- > 1)
      Serial.print('*');
    Serial.print(' ');
  }
  else
  {
    Serial.print(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i)
      Serial.print(' ');
  }
  smartdelay(0);
}

static void print_int(unsigned long val, unsigned long invalid, int len)
{
  char sz[32];
  if (val == invalid)
    strcpy(sz, "*******");
  else
    sprintf(sz, "%ld", val);
  sz[len] = 0;
  for (int i=strlen(sz); i<len; ++i)
    sz[i] = ' ';
  if (len > 0) 
    sz[len-1] = ' ';
  Serial.print(sz);
  smartdelay(0);
}

static void printdate(TinyGPS &gps)
{
  int year;
  byte month, day, hour, minute, second, hundredths;
  unsigned long age;
  gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);
  if (age == TinyGPS::GPS_INVALID_AGE)
    Serial.print("********** ******** ");
  else
  {
    char sz[32];
    sprintf(sz, "%02d/%02d/%02d %02d:%02d:%02d ",
        month, day, year, hour, minute, second);
   
  }
  smartdelay(0);
 
}
static void print_str(const char *str, int len)
{
  int slen = strlen(str);
  for (int i=0; i<len; ++i)
    Serial.print(i<slen ? str[i] : ' ');
  smartdelay(0);
}

