#include <Wire.h> //librairie pour communiquer
#include <SoftwareSerial.h>
SoftwareSerial BlueT(3,4);
int moove=0;
const int INT = 2;
const int MPU_addr = 0x68; 
float Acc_X,Acc_Y,Acc_Z; 
float AccCalibre_X,AccCalibre_Y,AccCalibre_Z; 
long GyX,GyY,GyZ;
float Tmp;
float angle_x;
float angle_y;
float angle_z;
float coeffgamme = 16384.0;
float coeffGyro = 100;
//const float rad_deg =57.2958;
float mytime, oldtime;
int Movem;
///////////////////////////////////////////////
//Define calibration coefficient
float xmin, xmax, ymin, ymax, zmin, zmax;
float goffsetx, goffsety, goffsetz,gainx,gainy,gainz;
//Define thresholds for acceleration
float thresholdRot;
float thresholdMouv;
//Define thresholds for speed
float Ggain;
float Gthreshold;
float Gmax;
//Define Accelero measurement
float xc, yc, zc;
//Define Gyro measurement
float gxc,ganglex;
float gyc,gangley;
float gzc,ganglez;
//Define the 3 angles of the Euler rotation matrix
float apsi, ateta, aphi;
//Define data for sliding average acceleration
const int SlidN = 9;
int SlidIn;
float SMX, SMY, SMZ;
float SlidX[SlidN], SlidY[SlidN], SlidZ[SlidN];
//Define data for sliding average speed
float SMGX, SMGY, SMGZ;
float SlidGX[SlidN], SlidGY[SlidN], SlidGZ[SlidN];
//Define old values for movement filtering
int SMXNow, SMYNow, SMZNow;
int SMXOld, SMYOld, SMZOld;
//Define the data for Volume, Rythme and Last
int Volume, Rythme, Last;////CHANGEMENT float
float shock;
float LastShockTime;
const int index1 = 5;
const int index2 = 6;
const int index3 = 7;
const int majeur1 = 8;
const int majeur2 = 9;
//const int majeur3 = 10;
const int annu1 = 10;
const int annu2 = 11;
const int auri1 = 12;
const int auri2 = 13;

void setup() {
    Serial.begin(9600);
    BlueT.begin(9600);
    pinMode(index1,INPUT); // on declare chaque doigt sauf le pouce comme des entrées donc des voltmetre
    pinMode(index2,INPUT);
    pinMode(index3,INPUT);
    pinMode(majeur1,INPUT);
    pinMode(majeur2,INPUT);
    //pinMode(majeur3,INPUT);
    pinMode(annu1,INPUT);
    pinMode(annu2,INPUT);
    pinMode(auri1,INPUT);
    pinMode(auri2,INPUT);
    Wire.begin();
    reglageMPU();
    InitMovement();
}

void loop() {
     lireAccgyro();
      mytime = millis();
     Movem = calculMovement();
   // songchoice();
       Serial.println("");
       Serial.print("%");
       Serial.print(songchoice()); //ajout debut
       Serial.print(";"); 
       Serial.print(Volume);
       Serial.print(";");
       Serial.print(Rythme);//fin
       Serial.print(";");
       Serial.print(shock);
       Serial.print(")"); 
       //bluetooth();
}

//////////////////////////////////////////////////////////////////
void reglageMPU(){
      Wire.beginTransmission(MPU_addr);
      Wire.write(0x6B);
      Wire.write(0);
      Wire.endTransmission();
      Wire.beginTransmission(MPU_addr);
      Wire.write(0x1c);
      Wire.write(B00000000);
      Wire.endTransmission();
}

void lireAccgyro(){
      Wire.beginTransmission(0x68);
      Wire.write(0x3B);
      Wire.endTransmission(false);
      Wire.requestFrom(MPU_addr,14,true); 
      Acc_X=(Wire.read()<<8|Wire.read())/coeffgamme;
      Acc_Y=(Wire.read()<<8|Wire.read())/coeffgamme;
      Acc_Z=(Wire.read()<<8|Wire.read())/coeffgamme;
      Tmp=Wire.read()<<8|Wire.read(); 
      GyX=(Wire.read()<<8|Wire.read()); 
      GyY=(Wire.read()<<8|Wire.read()); 
      GyZ=(Wire.read()<<8|Wire.read()); 
          //DETERMINATION DES ANGLES
      angle_x=(atan((Acc_X)/sqrt(pow((Acc_Y),2)+pow((Acc_Z),2)))*57.2958);
      angle_y=(atan((Acc_Y)/sqrt(pow((Acc_X),2)+pow((Acc_Z),2)))*57.2958);
      angle_z=(atan((Acc_Z)/sqrt(pow((Acc_X),2)+pow((Acc_Y),2)))*57.2958);

      }

int songchoice() {
  if (digitalRead(index1)==1){moove=1;}
  if (digitalRead(index2)==1){moove=2;}
  if (digitalRead(index3)==1){moove=3;}
  if (digitalRead(majeur1)==1){moove=4;}
  if (digitalRead(majeur2)==1){moove=5;}
  if (digitalRead(annu1)==1){moove=6;}
  if (digitalRead(annu2)==1){moove=7;}
  if (digitalRead(auri1)==1){moove=8;}
  if (digitalRead(auri2)==1){moove=9;}
  return moove;
}

void bluetooth() {
  // put your main code here, to run repeatedly:
//  String aenvoyer ="";
//  aenvoyer=aenvoyer+Movem;
 //if (Serial.available()){
    BlueT.write("%");
    EnvoieBtDecomposer(songchoice());
    BlueT.write(";");
    EnvoieBtDecomposer(Volume);
    BlueT.write(";");
    EnvoieBtDecomposer(Rythme);
    BlueT.write(";");
    EnvoieBtDecomposer(shock);
    BlueT.write(")");
    //BlueT.write(char(Movem)); ///PROBLEME ENVOYER MOVEM AUSSI ??????????????
}
void EnvoieBtDecomposer(int nb){
  String str= String(nb);
  for (int i=0;i<str.length();i++){
    BlueT.write(str[i]);}
  
}

///////////////////////////////////////////////
//Algorithm for movement detection
//
//call InitMovement() to initialize
//call  calculMovement(float time, float x, float y, float z) to get Movement with returned value Movement
// 0 = None, 1 = Vertical UP, 2 = Vertical Down, 3 = Horiz X+, 4 = Horiz X- ,5 = Horiz Y+, 6 = HorizY- 
//
///////////////////////////////////////////////////////
//Initialize all data for movement algo
void InitMovement(){
  //Calibration data for our accelerometer
  xmin = -0.875f;
  xmax = 1.09f;
  ymin = -1.03f;
  ymax = 0.96f;
  zmin = -1.02f;
  zmax = 1.04f;
  goffsetx = -3.818022599f;
  goffsety = -4.064293785f;
  goffsetz = -1.218135593f;
  gainx = -0.756303f;
  gainy = 0.725807f;
  gainz = 0.77586f;
  thresholdRot = 0.05f;
  thresholdMouv = 7.0f;
  Ggain = 0.04f;
  Gthreshold = 7.0f;
  Gmax = 10.0f;
  //Define the 3 angles of the Euler rotation matrix
  apsi = 0.0f;
  ateta=0.0f;
  aphi=0.0f;
  //initialize the sliding average
  SlidIn = 0;
  SMX = 0.0f;
  SMY = 0.0F;
  SMZ = -1.0f*SlidN;
  for(int i=0; i<SlidN; i++)
  {
    SlidX[i] = 0.0f;
    SlidY[i] = 0.0f;
    SlidZ[i] = -1.0f;
  }
  SMXOld = 0;
  SMYOld = 0;
  SMZOld = 0;
  ganglex = 0.0f;
  gangley = 0.0f;
  ganglez = 0.0f;
  oldtime = (float)millis()/1000.0f;
  Volume = 0.0f;
  Rythme = 0.0f;
  Last = 0.0f;
  shock = 0.0f;
  LastShockTime = 0.0f;
}

int calculMovement()
{
  //Initilize the Movement: 0 = None, 1 = Vertical UP, 2 = Vertical Down, 3 = Horiz X+, 4 = Horiz X- ,5 = Horiz Y+, 6 = HorizY- 
  int Movement = 0;

  //Calibrate the accelero measurement
  xc = (-2.0f*Acc_X+xmax+xmin)/(xmin-xmax);
  yc = (-2.0f*Acc_Y+ymax+ymin)/(ymin-ymax);
  zc = (-2.0f*Acc_Z+zmax+zmin)/(zmin-zmax);

  //Calibrate the gyro measurement
  gxc = (GyX - goffsetx) * gainx;
  gyc = (GyY - goffsety) * gainy;
  gzc = (GyZ - goffsetz) * gainz;

  //Compute the norm and normalized vector
  float norm = sqrt(xc*xc+yc*yc+zc*zc);
  float xn = xc / norm;
  float yn = yc / norm;
  float zn = zc / norm;

  //get if shock depending on Norm higher than 1;
  float myshock = abs(norm-1.0f);
  //Ignore all shocks that are within 0.5s
  if (((mytime-LastShockTime)>0.5f)&&(myshock>1.0f))
  {
    //Shock switches between 0 and 11
    shock = 11.0f - shock;
    LastShockTime = mytime;
  }
  
  //DETERMINATION DES ANGLES
  angle_x=(atan((xn)/sqrt(pow((yn),2)+pow((zn),2)))*57.2958);
  angle_y=(atan((yn)/sqrt(pow((xn),2)+pow((zn),2)))*57.2958);
  angle_z=(atan((zn)/sqrt(pow((xn),2)+pow((yn),2)))*57.2958);

  //Check if we are other acceleration than Gravity of -1G
  bool IsComputeRotation = (fabsf(norm-1.0f) < thresholdRot);

  //Compute Rotation Matrix only if norm lower than threshold, else we keep the old ones
  if (IsComputeRotation) 
  {
    if ((xn==0.0f)&&(yn==0.0f))
      apsi = 0;
    else
      apsi = atan2f(-xn, yn);
    ateta = -atan2f(sqrt(xn*xn+yn*yn), -zn);
    aphi = 0.0f;
  }

  //Get the all cos and sin of the 3 angles of Matrix
  float cs = cosf(apsi); //f pour flottant
  float ss = sinf(apsi);
  float ct = cosf(ateta);
  float st = sinf(ateta);
  float cp = cosf(aphi);
  float sp = sinf(aphi);
  
  //and reverse the matrix to get the real acceleration measurement
  float xr=(cs*cp-ss*sp*ct)*xc+(cp*ss+sp*ct*cs)*yc+(sp*st)*zc;
  float yr=(-sp*cs-cp*ct*ss)*xc+(-ss*sp+cp*ct*cs)*yc+(cp*st)*zc;
  float zr=(st*ss)*xc+(-st*cs)*yc+(ct)*zc;

  //and reverse the matrix to get the real speed measurement
  float gxr=(cs*cp-ss*sp*ct)*gxc+(cp*ss+sp*ct*cs)*gyc+(sp*st)*gzc;
  float gyr=(-sp*cs-cp*ct*ss)*gxc+(-ss*sp+cp*ct*cs)*gyc+(cp*st)*gzc;
  float gzr=(st*ss)*gxc+(-st*cs)*gyc+(ct)*gzc;

  //And integrate the Gyro to get Angles
  float deltatime = mytime-oldtime;
  ganglex += deltatime * gxr;
  gangley += deltatime * gyr;
  ganglez += deltatime * gzr;

  //And filter with sliding average for acceleration
  SMX += xr - SlidX[SlidIn];
  SMY += yr - SlidY[SlidIn];
  SMZ += zr - SlidZ[SlidIn];
  SlidX[SlidIn] = xr;
  SlidY[SlidIn] = yr;
  SlidZ[SlidIn] = zr;
 //And filter with sliding average for speed
  SMGX += ganglex - SlidGX[SlidIn];
  SMGY += gangley - SlidGY[SlidIn];
  SMGZ += ganglez - SlidGZ[SlidIn];
  SlidGX[SlidIn] = ganglex;
  SlidGY[SlidIn] = gangley;
  SlidGZ[SlidIn] = ganglez;
  //And finalized sliding algo
  SlidIn++;
  if (SlidIn>=SlidN)
    SlidIn = 0;

  //Now compute if movement
  float SMXthresh = SMX / SlidN * 10.0f;
  float SMYthresh = SMY / SlidN * 10.0f;
  float SMZthresh = (SMZ/ SlidN + 1.0f) * 10.0f;
  SMXNow = SMXthresh>thresholdMouv?1:(SMXthresh<-thresholdMouv?-1:0);
  SMYNow = SMYthresh>thresholdMouv?1:(SMYthresh<-thresholdMouv?-1:0);
  SMZNow = SMZthresh>thresholdMouv?1:(SMZthresh<-thresholdMouv?-1:0);

  //Compute the Movement if any
  if ((SMXOld!=SMXNow)&&(SMXOld==1))
    Movement = 3; // Horiz X+
  if ((SMXOld!=SMXNow)&&(SMXOld==-1))
    Movement = 4; // Horiz X-
  if ((SMYOld!=SMYNow)&&(SMYOld==1))
    Movement = 5; // Horiz Y+
  if ((SMYOld!=SMYNow)&&(SMYOld==-1))
    Movement = 6; // Horiz Y-
  if ((SMZOld!=SMZNow)&&(SMZOld==1))
    Movement = 1; // Vertical UP
  if ((SMZOld!=SMZNow)&&(SMZOld==-1))
    Movement = 2; // Vertical Down

  //And Reinit Old SM values
  SMXOld = SMXNow;
  SMYOld = SMYNow;
  SMZOld = SMZNow;  
  
  //Now compute if Volume, Rythme and Last
  float speedZ = ganglez - SMGZ/SlidN;
  if (abs(speedZ)> Gthreshold) {
    Volume+=speedZ*Ggain;
  //  Volume = Volume<0 ? 0 : (Volume>Gmax ? Gmax : Volume);
  }
  float speedX = ganglex - SMGX/SlidN;
  if (abs(speedX)> Gthreshold) {
    Rythme+=speedX*Ggain;
  //  Rythme = Rythme<0 ? 0 : (Rythme>Gmax ? Gmax : Rythme);
  }
  float speedY = gangley - SMGY/SlidN;
  if (abs(speedY)> Gthreshold) {
    Rythme-=speedY*Ggain;
  //  Rythme = Rythme<0 ? 0 : (Rythme>Gmax ? Gmax : Rythme);
  }

  //Now finish
  return Movement;
}
