#include <LiquidCrystal.h>
#define echo 7 
#define trig 8
LiquidCrystallcd(A5,A0,A1,A2,A3,A4);
#include "SD.h"
#define SD_ChipSelectPin 10
#include "TMRpcm.h"
#include "SPI.h"
#define Shop1 digitalRead(2)
#define Shop2 digitalRead(3)
#define Shop3 digitalRead(4)
#define IR_LeftdigitalRead(5)
#define IR_RightdigitalRead(6)
#define in1 digitalRead(0)
#define in2 digitalRead(1)
TMRpcmtmrpcm;
int current_position=0;
char path_1_2[13]="LRLRBD";
char path_1_3[13]="RLBD";
char path_2_3[13]="RLLBD";
char path_2_1[13]="LRLBD";
char path_3_1[13]="RBD";
char path_3_2[13]="RRLBD";
void setup()
{ 
lcd.begin(16,2);
lcd.clear();
lcd.print("initialization");
delay(1000);
tmrpcm.speakerPin = 9;
    if (SD.begin(SD_ChipSelectPin))
    {
lcd.setCursor(0,1);
lcd.print("SD Card Found");
    }
     else if (!SD.begin(SD_ChipSelectPin)) 
     {
lcd.setCursor(0,1);
lcd.print("SD card FAIL");
     }
      pinMode(0,INPUT_PULLUP);
      pinMode(1,INPUT_PULLUP);
      pinMode(2,INPUT_PULLUP);
      pinMode(3,INPUT_PULLUP);
      pinMode(4,INPUT_PULLUP);
      pinMode(5,INPUT);
      pinMode(6,INPUT);
      pinMode(echo,INPUT);
      pinMode(trig,OUTPUT);
      Voice('l'); Voice('r'); Voice('b');
}
long cm;
long duration;
void loop()
{
if(in1==1 && in2==0)
  {
lcd.clear();
lcd.print("STORE 1");
tmrpcm.setVolume(6);
tmrpcm.play("WC.wav");
delay(1200);
tmrpcm.play("1.wav");
delay(800);
        if(Shop2==0){lcd.clear(); lcd.print("STORE 1-2"); lcd.setCursor(0,1); lcd.print(path_1_2); path_info(1,2); destination(1,2);}
        if(Shop3==0){ lcd.clear(); lcd.print("STORE 1-3"); lcd.setCursor(0,1); lcd.print(path_1_3); path_info(1,3); destination(1,3);}
  }
if(in1==0 && in2==1)
  {
lcd.clear();
lcd.print("STORE 2");
tmrpcm.setVolume(6);
tmrpcm.play("WC.wav");
delay(1200);
tmrpcm.play("2.wav");
delay(800);
        if(Shop1==0){ lcd.clear(); lcd.print("STORE 2-1"); lcd.setCursor(0,1); lcd.print(path_2_1); path_info(2,1); destination(2,1); }
        if(Shop3==0){ lcd.clear(); lcd.print("STORE 2-3"); lcd.setCursor(0,1); lcd.print(path_2_3); path_info(2,3); destination(2,3); }
  }
if(in1==1 && in2==1)
  {
lcd.clear();
lcd.print("STORE 3");
tmrpcm.setVolume(6);
tmrpcm.play("WC.wav");
delay(1200);
tmrpcm.play("3.wav");
delay(800);
        if(Shop1==0){ lcd.clear(); lcd.print("STORE 3-1"); lcd.setCursor(0,1); lcd.print(path_3_1); path_info(3,1); destination(3,1); }
        if(Shop2==0){ lcd.clear(); lcd.print("STORE 3-2"); lcd.setCursor(0,1); lcd.print(path_3_2); path_info(3,2); destination(3,2);}
  }
}
void path_info(int p1, int p2)
{
  int i;
  Voice('P');
if(p1==1 && p2==2)
  {
    while(path_1_2[i-1]!='D') { Voice(path_1_2[i]); delay(500);i++;}
  }
if(p1==1 && p2==3)
  {
    while(path_1_3[i-1]!='D') { Voice(path_1_3[i]); delay(500); i++;}
  }
if(p1==2 && p2==3)
  {
    while(path_2_3[i-1]!='D') { Voice(path_2_3[i]); delay(500); i++;}
  }
if(p1==2 && p2==1)
  {
    while(path_2_1[i-1]!='D') { Voice(path_2_1[i]); delay(500); i++;}
  }
if(p1==2 && p2==3)
  {
    while(path_2_3[i-1]!='D') { Voice(path_2_3[i]); delay(500); i++;}
  }
if(p1==3 && p2==1)
  {
    while(path_3_1[i-1]!='D') { Voice(path_3_1[i]); delay(500); i++;}
  }
}
long ultraSonic_sensor() 
{
  long duration;
for(int i1=0; i1<10; i1++)
  {
    digitalWrite(trig,0);
delay(10);
    digitalWrite(trig,1);
delayMicroseconds(10);
    digitalWrite(trig,0);
    duration = pulseIn(echo, HIGH);
delay(10);
  }
  return duration/29/2;
}
void Voice(char c)
{
  switch(c)
  {
  case 's': tmrpcm.setVolume(6);
tmrpcm.play("SP.wav");
delay(1000);
            break;
  case 'F': tmrpcm.setVolume(6);
tmrpcm.play("GS.wav");
delay(1000);
            break;
  case 'L': tmrpcm.setVolume(6);
tmrpcm.play("TL.wav");
delay(1000);
            break;
  case 'R': tmrpcm.setVolume(6);
tmrpcm.play("TR.wav");
delay(1000);
            break;
  case 'M': tmrpcm.setVolume(6);
tmrpcm.play("M.wav");
delay(1000);
            break;
  case 'W': tmrpcm.setVolume(6);
tmrpcm.play("WS.wav");
delay(1000);
            break;
  case 'D': tmrpcm.setVolume(6);
tmrpcm.play("RD.wav");
delay(1000);
            break;
  case 'C': tmrpcm.setVolume(6);
tmrpcm.play("WC.wav");
delay(1000);
            break;
  case 'B': tmrpcm.setVolume(6);
tmrpcm.play("stop.wav");
delay(1000);
            break;
  case 'P': tmrpcm.setVolume(6);
tmrpcm.play("yourPath.wav");
delay(1500);
            break;
  case 'l': tmrpcm.setVolume(6);
tmrpcm.play("O_Left.wav");
delay(1500);
            break;
  case 'r': tmrpcm.setVolume(6);
tmrpcm.play("O_Right.wav");
delay(1500);
            break;
  case 'b': tmrpcm.setVolume(6);
tmrpcm.play("O_Both.wav");
delay(1500);
            break;
  }
}
void destination(int path1, int path2)
{
  int j=0,TimeCount=0;
  int path_change=0;
  Voice('s');
while(1)
   { 
    cm=ultraSonic_sensor();
lcd.clear();
lcd.print(cm);
    if(cm<=100)
    {
TimeCount++;
     Voice('W');
     if(TimeCount>2) path_change=1;
    }
    if(cm>100)
    {
lcd.setCursor(0,1);
lcd.print('F');
     Voice('F');
TimeCount=0;
    }
if(IR_Left==1 &&IR_Right==1)
{
     Voice('b'); 
    }
    else if(IR_Left==1)
    {
     Voice('l'); 
    }
    else if(IR_Right==1)
    {
     Voice('r'); 
    }

    if(path_change==1)
    {
if(path1==1 && path2==2)
      {
lcd.setCursor(0,1);
lcd.print(path_1_2[j]);
        Voice(path_1_2[j]);
TimeCount=0;
path_change=0;
       if(path_1_2[j]=='B')
       { 
        j=0; 
        Voice('D');
lcd.println("break");
        break;
        }
j++;
     }
if(path1==1 && path2==3)
      {
lcd.print(path_1_3[j]);
        Voice(path_1_3[j]);
TimeCount=0;
path_change=0;
       if(path_1_3[j]=='B')
       { 
        j=0; 
        Voice('D');
lcd.println("break");
        break;
        }
j++;
     }
if(path1==2 && path2==3)
      {
lcd.print(path_2_3[j]);
        Voice(path_2_3[j]);
TimeCount=0;
path_change=0;
       if(path_2_3[j]=='B')
       { 
        j=0; 
        Voice('D');
lcd.println("break");
        break;
        }
j++;
     }
if(path1==2 && path2==1)
      {
lcd.print(path_2_1[j]);
        Voice(path_2_1[j]);
TimeCount=0;
path_change=0;
       if(path_2_1[j]=='B')
       { 
        j=0; 
        Voice('D');
lcd.println("break");
        break;
        }
j++;
     }
if(path1==3 && path2==1)
      {
lcd.print(path_3_1[j]);
        Voice(path_3_1[j]);
TimeCount=0;
path_change=0;
       if(path_3_1[j]=='B')
       { 
        j=0; 
        Voice('D');
lcd.println("break");
        break;
        }
j++;
     }
if(path1==3 && path2==2)
      {
lcd.print(path_3_2[j]);
        Voice(path_3_2[j]);
TimeCount=0;
path_change=0;
       if(path_3_2[j]=='B')
       { 
        j=0; 
        Voice('D');
lcd.println("break");
        break;
        }
j++;
     }
delay(500);
    }
   }
}

