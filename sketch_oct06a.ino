#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

int tx=2, rx=3, led=8, rs=12, en=11, d4=4,d5=5,d6=6,d7=7;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
char CFStatus = 'C';
int th=0;
int Vo;
float R1=10000;
float logR2, R2, T, Tr;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

SoftwareSerial bluetooth(tx,rx);
int receiveData;

void setup(){
  pinMode(led,OUTPUT);
  digitalWrite(led,LOW);
  Serial.begin(9600);
  bluetooth.begin(9600);
  lcd.begin(16,2);
}

void loop()
{
  Vo=analogRead(th);
  R2=R1*(1023.0f/(float)Vo-1.0f);
  logR2=log(R2);
  T=(1.0/(c1+c2*logR2+c3*logR2*logR2*logR2));
  if(bluetooth.available()>0)
  {
    char ch = bluetooth.read();
    if(ch>='A' && ch<='Z') CFStatus=ch;
  }
  if(CFStatus == 'C')
  {
    Tr = T-273.15;
    digitalWrite(led,LOW);
  }
  else if(CFStatus == 'F')
  {
    Tr = T - 273.15;
    Tr = (Tr * 9.0)/ 5.0 + 32.0;
    digitalWrite(led,HIGH);
  }
  
  bluetooth.println(String(Tr));
  lcd.setCursor(0,0);
  lcd.print("Current Temp");
  lcd.setCursor(0,1);
  lcd.print(String(Tr)+" "+CFStatus);
  delay(100);
}
