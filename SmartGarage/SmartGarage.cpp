#include <Arduino.h>
#include "LiquidCrystal.h"

#define LDR  A0 

#define RS 2 
#define EN 3
#define D4 4 
#define D5 5
#define D6 6
#define D7 7 
#define LED 8 
#define Trig 9 
#define Echo 10 
#define Buzzer 11 

//Global Variables  

int LDR_Reading ; 
float Distance ;
bool IS_Buzzer_Active = false ;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);


//Functions Decleration

float Ultra_Sonic_Distance(int , int ) ;
void Print_Distance_And_Light_Level( float  , int ) ;
void Buzzer_Activation( int , int , int , bool  );


void setup() {
  Serial.begin(9600);

  pinMode(A0 , INPUT) ;
  pinMode(Echo , INPUT) ;

  pinMode(Buzzer , OUTPUT) ;
  pinMode(Trig , OUTPUT) ;
  pinMode(LED , OUTPUT) ;

  lcd.begin(16, 2);
}

void loop() {
  Distance  = Ultra_Sonic_Distance(Trig , Echo) ;
  LDR_Reading = analogRead(LDR) ;

  Buzzer_Activation(Buzzer , Distance , 10 , false ) ; // Actives the Buzzer depending on Distance Condtion 

  if (IS_Buzzer_Active == false) {                   // the if condtion is solving the conflection if both of the Distance and Light condtions are ture
    Buzzer_Activation(Buzzer , LDR_Reading , 200 , true ) ; // Actives the Buzzer depending on light Condtion 
  }

  //To make this function works please declare an LiquidCrystal  object called lcd 
  Print_Distance_And_Light_Level(Distance , LDR_Reading ) ;
  delay(100);
}


//UltraSonic Function , Returns the Distance infront of it by Cm
float Ultra_Sonic_Distance(int TriggerPin , int EchoPin) {

  float distance = 0.0 , duration = 0.0  ; 

  digitalWrite(TriggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TriggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TriggerPin, LOW);

  duration = pulseIn(EchoPin, HIGH);
  distance = (duration*.0343)/2;

  return distance ;
}


//Printing the Distance and Light level on LCD Fucntion 
void Print_Distance_And_Light_Level( float distance , int LightLevel) { 

//Printing Distance
  lcd.setCursor(0, 0);
  lcd.print("Distance:");
  lcd.print((int)Distance);  // Print integer part
  lcd.print(".");  
  lcd.print((int)((Distance - (int)Distance) * 100));  // Print two decimal places
  
  //PrintLightLevel 
  lcd.setCursor(0, 1);
  lcd.print("Light Level:");
  lcd.print(LightLevel);
}

//Buzzer Controling Function
void Buzzer_Activation( int Buzzer_pin , int Reading , int Threshold , bool Blink_The_LED = false) {


  if (Reading <= Threshold) {
    tone(Buzzer_pin , 200) ; 
    IS_Buzzer_Active = true ;
    if (Blink_The_LED) {
      digitalWrite(LED , HIGH ) ;
    }

  }
  
  else {
    noTone(Buzzer_pin) ;
    IS_Buzzer_Active = false ;
    digitalWrite(LED , LOW ) ;
  }
  }
  