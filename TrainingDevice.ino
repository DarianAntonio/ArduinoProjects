#include <LiquidCrystal.h>
LiquidCrystal lcd(5, 6, 12, 8, 13, 7);

void(*reset) (void) = 0;

char prev[1],tasta[1];
struct securitate{
  char corecta[8];
  char aleasa[8];
} parola,conectare;
int ore=0,minute=0,secunde=0;
int minute_red=0,secunde_red=0;
int minute_blue=0,secunde_blue=0;
int buton_red=10,buton_blue=9;
unsigned long long numarator;
int interval;
int fir[6]={16,18,14,17,15,11};
long long deconectat[6]={-1,-1,-1,-1,-1,-1};
void afisare_control()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Red       ");
  if(minute_red<10)lcd.print("  ");
  else if(minute_red<100)lcd.print(" ");
  lcd.print(minute_red);lcd.print(":");
  if(secunde_red<10)lcd.print("0");
  lcd.print(secunde_red);
  lcd.setCursor(0,1);
  lcd.print("Blue      ");
  if(minute_blue<10)lcd.print("  ");
  else if(minute_blue<100)lcd.print(" ");
  lcd.print(minute_blue);lcd.print(":");
  if(secunde_blue<10)lcd.print("0");
  lcd.print(secunde_blue);
}
void afisare_cronometru(short pozitie,short caz)
{
  if(caz==0){lcd.setCursor(3,pozitie);
  if(ore<10)
  lcd.print("0");lcd.print(ore);lcd.print(":");
  if(minute<10)
  lcd.print("0");lcd.print(minute);lcd.print(":");
  if(secunde<10)
  lcd.print("0");lcd.print(secunde);
      }
  if(caz==1)
    {lcd.setCursor(3,pozitie);
    if(millis()%500>250)
    {if(ore<10)
    lcd.print("0");lcd.print(ore);lcd.print(":");}
    else lcd.print("  :");
    if(minute<10)
    lcd.print("0");lcd.print(minute);lcd.print(":");
    if(secunde<10)
    lcd.print("0");lcd.print(secunde);
      }
  if(caz==2)
    {lcd.setCursor(3,pozitie);
    if(ore<10)
    lcd.print("0");lcd.print(ore);lcd.print(":");
    if(millis()%500>250)
    {if(minute<10)
    lcd.print("0");lcd.print(minute);lcd.print(":");}
    else lcd.print("  :");
    if(secunde<10)
    lcd.print("0");lcd.print(secunde);
      }
  if(caz==3)
    {lcd.setCursor(3,pozitie);
    if(ore<10)
    lcd.print("0");lcd.print(ore);lcd.print(":");
    if(minute<10)
    lcd.print("0");lcd.print(minute);lcd.print(":");
    if(millis()%500>250)
    {if(secunde<10)
    lcd.print("0");lcd.print(secunde);}
    else lcd.print("  ");
      }
  
}
void afisare_text(short pozitie,char *text)
{
  int lungime=strlen(text);
  lcd.setCursor((16-lungime)/2,pozitie);
  lcd.print(text);
}
void afisare_parola(short pozitie,short caz)
{
  if(caz==1){
              lcd.setCursor(3,pozitie);
              for(short i=0;i<8;i++)
                if(parola.corecta[i]!='X')
                  lcd.print(parola.corecta[i]);
           }
   else if(caz==2){
              lcd.setCursor(3,pozitie);
              for(short i=0;i<8;i++)
                if(parola.aleasa[i]!='X')
                  lcd.print(parola.aleasa[i]);
           }
}
void afisare_fire(short pozitie)
{
  lcd.setCursor(3,pozitie);
  for(short i=0;i<6;i++)
    if(conectare.corecta[i]=='0')
      lcd.print(i+1);
    else
      lcd.print(" ");
}

char tastatura()
{
 if(analogRead(A5)<210)
    return '!';
  else 
     if(analogRead(A5)<221)
      return '1';
  else
    if(analogRead(A5)<232)
      return '4';
  else
    if(analogRead(A5)<244)
      return '7';
  else
    if(analogRead(A5)<256)
      return '*';
  else
    if(analogRead(A5)<282)
      return '2';
  else
    if(analogRead(A5)<301)
      return '5';
  else
    if(analogRead(A5)<321)
      return '8';
  else
    if(analogRead(A5)<351)
      return '0';
  else
    if(analogRead(A5)<389)
      return '3';
  else
    if(analogRead(A5)<431)
      return '6';
  else
    if(analogRead(A5)<481)
      return '9';
  else
    if(analogRead(A5)<551)
      return '#';
  else
    if(analogRead(A5)<651)
      return 'A';
  else
    if(analogRead(A5)<751)
      return 'B';
  else
    if(analogRead(A5)<900)
      return 'C';
  else
      return 'D';
}


struct comenzi{
  int tip()
  {
    short conditie=false;
    if(prev[0]!=tasta[0]&&prev[0]=='!')conditie=true;
    if(conditie==true)
    {
      if(tasta[0]>='0'&&tasta[0]<='9')
      return 1;
      else if(tasta[0]>='A'&&tasta[0]<='D')
      return 2;
      else return 3;
    }
    else return 0;
  }
  int simbol()
  {
    return tasta[0];
  }
  
} comanda;

void initializere()
{
  for(int i=0;i<8;i++)
  {
    parola.corecta[i]='X';
    parola.aleasa[i]='X';
    conectare.corecta[i]='X';
    conectare.aleasa[i]='X';
  }
  prev[0]='!';
  lcd.begin(16,2);
  for(int i=0;i<6;i++)
  {pinMode(fir[i],INPUT);
  digitalWrite(fir[i],1);}
  pinMode(buton_red,INPUT);
  pinMode(buton_blue,INPUT);
  pinMode(1,OUTPUT);
  pinMode(0,INPUT);
  digitalWrite(buton_blue,1);
  digitalWrite(buton_red,1);
  digitalWrite(1,1);
  digitalWrite(0,1);
}



void setare_parola()
{
  int setat=false,pozitie=0;
  lcd.clear();
  afisare_text(0,"Setati parola");
  while(setat!=true)
  {
    tasta[0]=tastatura();
    if(comanda.tip()==1&&pozitie!=8)
    {
      parola.corecta[pozitie]=comanda.simbol();
      pozitie++;
      lcd.clear();
      afisare_text(0,"Setati parola");
      afisare_parola(1,1);
    }
    else if(comanda.tip()==2)
    {
    }
    else if(comanda.tip()==3)
    {
      if(comanda.simbol()=='*'&&pozitie>=1)
      {
        pozitie--;
        parola.corecta[pozitie]='X';
        lcd.clear();
        afisare_text(0,"Setati parola");
        afisare_parola(1,1);
      }
      else if(comanda.simbol()=='#')
      {
        setat=true;
      }
    }
    prev[0]=tasta[0];
  }
  while(tasta[0]=='#')tasta[0]=tastatura();
}

void setare_ore()
{
  int setat=false;
  unsigned long long timp=millis();
  lcd.clear();
  afisare_text(0,"Cronometrul");
  afisare_cronometru(1,1);
  while(setat!=true)
  {
    if(millis()-timp>=100)
    {
     timp=millis();
     lcd.clear();
    afisare_text(0,"Cronometrul");
    afisare_cronometru(1,1);
    }
    tasta[0]=tastatura();
    if(comanda.tip()==1)
    {
      ore=ore*10+comanda.simbol()-48;
      if(ore>=100)
        ore=ore/10;
    }
    if(comanda.tip()==2)
    {
    }
    if(comanda.tip()==3)
    {
      if(comanda.simbol()=='*')
      {
        ore=ore/10;
      }
      else if(comanda.simbol()=='#')
        setat=1;
    }
    prev[0]=tasta[0];
  }
  while(tasta[0]=='#')tasta[0]=tastatura();
}

void setare_minute()
{
  int setat=false;
  unsigned long long timp=millis();
  lcd.clear();
  afisare_text(0,"Cronometrul");
  afisare_cronometru(1,2);
  while(setat!=true)
  {
    if(millis()-timp>=100)
    {
     timp=millis();
     lcd.clear();
    afisare_text(0,"Cronometrul");
    afisare_cronometru(1,2);
    }
    tasta[0]=tastatura();
    if(comanda.tip()==1)
    {
      minute=minute*10+comanda.simbol()-48;
      if(minute>=60)
        minute=59;
    }
    if(comanda.tip()==2)
    {
    }
    if(comanda.tip()==3)
    {
      if(comanda.simbol()=='*')
      {
        minute=minute/10;
      }
      else if(comanda.simbol()=='#')
        setat=1;
    }
    prev[0]=tasta[0];
  }
  while(tasta[0]=='#')tasta[0]=tastatura();
}
void setare_secunde()
{
  int setat=false;
  unsigned long long timp=millis();
  lcd.clear();
  afisare_text(0,"Cronometrul");
  afisare_cronometru(1,3);
  while(setat!=true)
  {
    if(millis()-timp>=100)
    {
     timp=millis();
     lcd.clear();
    afisare_text(0,"Cronometrul");
    afisare_cronometru(1,3);
    }
    tasta[0]=tastatura();
    if(comanda.tip()==1)
    {
      secunde=secunde*10+comanda.simbol()-48;
      if(secunde>=60)
        secunde=59;;
    }
    if(comanda.tip()==2)
    {
    }
    if(comanda.tip()==3)
    {
      if(comanda.simbol()=='*')
      {
        secunde=secunde/10;
      }
      else if(comanda.simbol()=='#')
        setat=1;
    }
    prev[0]=tasta[0];
  }
  while(tasta[0]=='#')tasta[0]=tastatura();
}

void setare_cronometru()
{
  setare_ore();
  setare_minute();
  setare_secunde();
}

void setare_fire()
{
  int setat=false;
  lcd.clear();
        afisare_text(0,"Alegeti firele");
        afisare_fire(1);
  while(setat!=true)
  {
   tasta[0]=tastatura();
   if(comanda.tip()==1)
   {
      if(comanda.simbol()<'7'&&comanda.simbol()>'0')
      {
        if(conectare.corecta[comanda.simbol()-49]=='X')
          conectare.corecta[comanda.simbol()-49]='0';
        else
          conectare.corecta[comanda.simbol()-49]='X';
        lcd.clear();
        afisare_text(0,"Alegeti firele");
        afisare_fire(1);
      }
   }
   else if(comanda.tip()==2)
   {
    
   }
   else if(comanda.tip()==3)
   {
      if(comanda.simbol()=='#')
      {
       setat=1;
      }
   }
   prev[0]=tasta[0];
  }
  while(tasta[0]=='#')tasta[0]=tastatura();
}
void joc1()
{
  while(tasta[0]=='1')tasta[0]=tastatura();
  setare_parola();
  setare_cronometru();
  setare_fire();
  numarator=millis();
  interval=1000;
  lcd.clear();
  afisare_cronometru(0,0);
  afisare_parola(1,2);
}
void joc2()
{
  afisare_control();
  int control_red=1;
  unsigned long long timp;
  while(digitalRead(buton_blue)==1&&digitalRead(buton_red)==1)
    if(digitalRead(buton_blue)==0)
        control_red=0;
  while(1){
    timp=millis();
    while(control_red==1){
      while(digitalRead(0)==0);
      if(millis()-timp>=1000)
        {secunde_red++,timp=millis();
      if(secunde_red==60)secunde_red=0,minute_red++;afisare_control();}
      if(digitalRead(buton_blue)==0)
        control_red=0;
    }
    timp=millis();
    while(control_red==0){
      while(digitalRead(0)==0);s
      if(millis()-timp>=1000)
        {secunde_blue++,timp=millis();
      if(secunde_blue==60)secunde_blue=0,minute_blue++;afisare_control();}
      if(digitalRead(buton_red)==0)
        control_red=1;
    }
  }
}
void setup()
{
  initializere();
  lcd.clear();
  int setat=0;
  afisare_text(0,"Alegeti jocul");
  afisare_text(1,"1 sau 2");
  while(setat==0){
    tasta[0]=tastatura();
    if(comanda.simbol()=='1')setat=1;
    else if(comanda.simbol()=='2')setat=2;
  }
  if(setat==1)joc1();
  else joc2();
}
void castig()
{
  lcd.clear();
  afisare_text(0,"Felicitari");
  afisare_text(1,"Ai castigat");
  while(1){}
}

void pierd()
{
  lcd.clear();
  {
    char text[]="Bomba a";
    afisare_text(0,text);
  }
  {
    char text[]="explodat";
    afisare_text(1,text);
  }
  digitalWrite(1,0);
  while(1){}
}

void numaratoare()
{
  
  if(millis()-numarator>=interval)
  {
    lcd.clear();
    afisare_cronometru(0,0);
    afisare_parola(1,2);
    numarator=millis();
    secunde--;
    if(secunde==-1)
    {
      secunde=59;
      minute--;
    }
    if(minute==-1)
    {
      minute=59;
      ore--;
    }
  }
}
int pozitie1=0,ales=false,incercari=3;
void alegere_parola()
{
    tasta[0]=tastatura();
    if(comanda.tip()==1&&pozitie1!=8)
    {
      parola.aleasa[pozitie1]=comanda.simbol();
      pozitie1++;
      lcd.clear();
        afisare_cronometru(0,0);
        afisare_parola(1,2);
    }
    else if(comanda.tip()==2)
    {
    }
    else if(comanda.tip()==3)
    {
      if(comanda.simbol()=='*'&&pozitie1>=1)
      {
        pozitie1--;
        parola.aleasa[pozitie1]='X';
        lcd.clear();
        afisare_cronometru(0,0);
        afisare_parola(1,2);
      }
      else if(comanda.simbol()=='#')
      {
        ales=true;
      }
    }
    prev[0]=tasta[0];
}


void alegere_fire()
{
  for(short i=0;i<6;i++)
  {
    if(digitalRead(fir[i])==0)
      conectare.aleasa[i]='X',deconectat[i]=-1;
    else if(digitalRead(fir[i])==1&&deconectat[i]==-1)
      deconectat[i]=millis();
    else if(digitalRead(fir[i])==1&&millis()-deconectat[i]>1000)
      conectare.aleasa[i]='0';
  }
}
void verificare()
{
  int gresit=false,corect=0;
  if(digitalRead(0)==0)
    castig();
  if(ore==-1)
      pierd();
  if(ales==true)
  {
    for(short i=0;i<8&&gresit==false;i++)
    {
      if(parola.corecta[i]!=parola.aleasa[i])
        gresit=true;
    }
    if(gresit==false)
      castig();
    else if(gresit==true)
    {
      ales=false;
      for(short i=0;i<6;i++)
      parola.aleasa[i]='X';
      pozitie1=0;
      if(incercari!= 1)
        {
          incercari--;
          interval=interval*2/3;
        }
      else pierd();
    }
  }
  gresit=false;
  for(short i=0;i<6&&gresit==false;i++)
  {
    if(conectare.corecta[i]==conectare.aleasa[i])
      corect++;
    else if(conectare.corecta[i]=='X'&&conectare.aleasa[i]=='0')
      pierd();
  }
  if(corect==6)
    castig();
}

void loop()
{
  numaratoare();
  alegere_parola();
  alegere_fire();
  verificare();
}
