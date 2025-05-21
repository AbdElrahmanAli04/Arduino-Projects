#include <Arduino.h>

/*
Notes Before implementing this circuit : 
- It was designed for measuring Li-ion batteries , which it's volt can reach 4.3 volt , So using any battery with higher voltage should be considered in power calculations 
- I used 2SC2655 NPN transistor 
*/

#define VOLT A0
#define Gate 3 
#define LoadResistor 4.7

void setup() {
  Serial.begin(9600);
  pinMode(VOLT, INPUT);
  pinMode(Gate , OUTPUT) ;
}

double Voltage(){
  int val = analogRead(VOLT);
  double voltOut = (val * 5.0)/1023 ;  
  double volt = voltOut * 1.99 ;  
  return volt ;
}

double Calculate_r(double VoltOC , double VoltSC){
  double Current = (VoltSC - VoltOC*0.1  )  / LoadResistor ; // The VoltOC*0.1 is due to some saturation region calculations   
  Serial.print(Current);
  Serial.println(" A"); 
  double r = (VoltOC - VoltSC ) / Current ;
  return r ; 
}


double VoltOC = 0 ;
double VoltSC = 0 ;
double internal_r = 0 ;



void loop() {
  
  long double Avg = 0 ;  
  
  digitalWrite(Gate, LOW);
  delay(300);

  for (int i = 0 ; i<100 ; i++) {
    Avg += Voltage(); 
    delay(5) ;
  }

  VoltOC = Avg/100 ; 

  
  digitalWrite(Gate, HIGH);
  delay(300);

  Avg = 0 ;

  for (int i = 0 ; i<100 ; i++) {
    Avg += Voltage(); 
    delay(5) ;
  }

  VoltSC = Avg/100;

  internal_r = Calculate_r(VoltOC, VoltSC);
  
  Serial.print("Internal resistance = ");
  Serial.print(internal_r , 5);
  Serial.println(" OHM"); 
  
  Serial.print(VoltOC);
  Serial.println(" V"); 
   
  Serial.print(VoltSC);
  Serial.println(" V"); 
}