const int pingPin = 4;
long duration, inches, cm;

const int MdrSpa = 5;
const int MdrFata =7;
const int pdr=6;

const int MsgSpa = 11;
const int MsgFata =9;
const int psg=5;

long sensors[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
long masuraSenz = 0;
int sw=11;
int sumaSenz = 0;
int p=0,s=0, c=0, pozitie = 0;
int proportional = 0;
long integral = 0;
int derivative = 0;
int propOld = 0;
int control = 0;
double pf=0,ps=0;
int  pw = 230;
float Kp = .1;
float Ki = .000001;
float Kd = 10.105;
int prop,bd=0,bs=0,nrSenz=6;
int limit =(nrSenz-1)*1000/2;

void setup()
{
 pinMode (MdrFata, OUTPUT);
 pinMode (MsgFata,OUTPUT);
 pinMode (MdrSpa, OUTPUT);
 pinMode (MsgSpa, OUTPUT);
 Serial.begin(9600);
 }


void loop()
{
 citeste();
 decide();
 set_motors();
 
}

void citeste()
{
 for (int i = 0; i < nrSenz; i++)
 {
   sensors[i] = analogRead(i);
   
  if (sensors[i] < 100)
   {
     sensors[i] = 0;
   }
 }
masuraSenz = 0;
 
for (int i = 0; i < nrSenz; i ++)
 {
   masuraSenz += sensors[i] * i * 1000;
 }

sumaSenz = 0;
 
 for (int i = 0; i < nrSenz; i++)
 {
   sumaSenz += int(sensors[i]);
 }

pozitie = int(masuraSenz / sumaSenz);

proportional = pozitie - limit;
 prop=proportional;
if (-proportional==limit+1) proportional=propOld;

if (-prop != limit+1) {bd=0;bs=0;ps=0;pf=0;}
 integral = integral + proportional;

 derivative = proportional - propOld;

 
  propOld = proportional;

 control = int(proportional * Kp + integral * Ki + derivative * Kd);
 Serial.println(control);
}

void decide()
{ 
if (proportional>1500 && -prop==limit+1 ) {bs=1;pf=pw;ps=pw/5;baga_linie();}
if (proportional<-1500 && -prop==limit+1 ) {bd=1;pf=pw; ps=pw/5;baga_linie();}
}



void baga_linie()
{
  
while (bs==1)
 {
   citeste();
   ps=ps+.05;
  if (ps>pw) ps=pw;
  analogWrite(MsgSpa,ps);
  analogWrite(MdrSpa,0);
  analogWrite(MsgFata,0);
  analogWrite(MdrFata,pf); 
 }

 while (bd==1)
 {
   citeste();
    ps=ps+.05;
  if (ps>pw) ps=pw;
  analogWrite(MsgSpa,0);
  analogWrite(MdrSpa,ps);
  analogWrite(MsgFata,pf);
  analogWrite(MdrFata,0);
 }

 
}
void set_motors()
{
 analogWrite(MdrSpa,0);
 analogWrite(MsgSpa,0);
  if (control > pw)
 {
   control = pw;
 }
 

 if (control < -pw)
 {
   control = -pw;
 }
 
 if (control < 0)
 {
   analogWrite(MdrSpa,0);
 analogWrite(MsgSpa,0);
 analogWrite(MdrFata,pw + control);
 analogWrite(MsgFata,pw);
 }
else
 {
   analogWrite(MdrSpa,0);
 analogWrite(MsgSpa,0);
 analogWrite(MdrFata,pw);
 analogWrite(MsgFata,pw - control);

 }
}
