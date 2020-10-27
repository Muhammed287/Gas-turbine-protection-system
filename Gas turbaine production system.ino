#include <Wire.h>
#include <FlowMeter.h> 
#include <SFE_BMP180.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
SFE_BMP180 pressure;
FlowMeter Meter = FlowMeter(13);
const unsigned long period = 1000;
int cr=1;
void MeterISR() {  Meter.count();  }

int motors=8;
int motorn=9;
int motore=10;
int fn=11;
int fe=4;
int tn=6;
int te=7;
int pn=2;
int pe=12;
int bp=3;
int motor=5;

int ctr=0;
void setup() {
  Serial.begin(9600); 

  Serial.println("Program started");
  attachInterrupt(INT0, MeterISR, RISING);
   
    Meter.reset();
  if (pressure.begin())
    Serial.println("BMP180 init success");
  else //Else, stop code forever
  { Serial.println("BMP180 init fail");   while (1); }

  lcd.begin();
  lcd.backlight();

  pinMode(motors,OUTPUT);
  pinMode(motorn,OUTPUT);
  pinMode(motore,OUTPUT);
  pinMode(pn,OUTPUT);
  pinMode(pe,OUTPUT);
  pinMode(tn,OUTPUT);
  pinMode(te,OUTPUT);
  pinMode(fn,OUTPUT);
  pinMode(fe,OUTPUT);
  pinMode(bp,OUTPUT);
  pinMode(0,INPUT_PULLUP);
  pinMode(1,INPUT_PULLUP);
  pinMode(motor,OUTPUT);

  // start state 
      lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("Working : 50% ");
      analogWrite(motor,128);
      digitalWrite(motorn,0);
      digitalWrite(motore,0);
      digitalWrite(motors,1);
      digitalWrite(fn,0);
      digitalWrite(fe,0);
      digitalWrite(tn,0);
      digitalWrite(te,0);
      digitalWrite(pn,0);
      digitalWrite(pe,0);
      digitalWrite(bp,0);
      delay(4000);
  
}

void loop()
{ 
     char status;
    double T, P, p0;
    status = pressure.startTemperature();
    if (status != 0) {
      delay(status);
  
      status = pressure.getTemperature(T);
      if (status != 0) {
        Serial.print("Temp: ");
        Serial.print(T, 1);
        Serial.println(" deg C");
  
        status = pressure.startPressure(3);
  
        if (status != 0) {
          delay(status);
  
          status = pressure.getPressure(P, T);
          if (status != 0) {
            Serial.print("Pressure measurement: ");
            Serial.print(P);
            Serial.println(" Pa ");
          }
        }
      }
    }
     delay(period);
     Meter.tick(period);
float    m=Meter.getCurrentFlowrate();
     Serial.println("Currently " + String(m) + " l/min");

      if ( 990<P & P<1021 & 20 <T & T<= 34 & -1<=m & m<=15)
      {
          lcd.clear();
          lcd.setCursor(0,0); 
          lcd.print("Working : 90% ");
          analogWrite(motor,230);
          digitalWrite(motorn,1);
          digitalWrite(motore,0);
          digitalWrite(motors,0);
          digitalWrite(fn,1);
          digitalWrite(fe,0);
          digitalWrite(tn,1);
          digitalWrite(te,0);
          digitalWrite(pn,1);
          digitalWrite(pe,0);
          digitalWrite(bp,0);

          lcd.setCursor(0,1); 
          lcd.print("Error:");
       }
      
       if ( 990>=P | P>=1021)
    { lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("Working : 50% ");
      lcd.setCursor(0,1); 
      lcd.print("Error:");
      lcd.setCursor(8,1); 
      lcd.print("P");
      analogWrite(motor,125);
      digitalWrite(motorn,0);
      digitalWrite(motore,1);
      digitalWrite(motors,0);
      digitalWrite(fn,1);
      digitalWrite(fe,0);
      digitalWrite(tn,1);
      digitalWrite(te,0);
      digitalWrite(pn,0);
      digitalWrite(pe,1); 
      digitalWrite(bp,1);

}
        if (-1>=m | m>=20)
      {
          lcd.clear();
          lcd.setCursor(0,0); 
          lcd.print("Working : 50% ");
          lcd.setCursor(0,1); 
          lcd.print("Error:");
          lcd.setCursor(13,1); 
          lcd.print("F");
          analogWrite(motor,125);
          digitalWrite(motorn,0);
          digitalWrite(motore,1);
          digitalWrite(motors,0);
          digitalWrite(fn,0);
          digitalWrite(fe,1);
          digitalWrite(tn,1);
          digitalWrite(te,0);
          digitalWrite(pn,1);
          digitalWrite(pe,0);
          digitalWrite(bp,0);
      }
        if (20 >= T | T >= 34)
      {
        lcd.clear();
        lcd.setCursor(0,0); 
        lcd.print("Working : 50% ");
        lcd.setCursor(0,1); 
        lcd.print("Error:");
        lcd.setCursor(10,1); 
        lcd.print("T");
        analogWrite(motor,125);
        digitalWrite(motorn,0);
        digitalWrite(motore,1);
        digitalWrite(motors,0);
        digitalWrite(fn,1);
        digitalWrite(fe,0);
        digitalWrite(tn,0);
        digitalWrite(te,1);
        digitalWrite(pn,1);
        digitalWrite(pe,0); 
        digitalWrite(bp,0);
       } 
}
