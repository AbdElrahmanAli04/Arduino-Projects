#include <Arduino.h>
#define Pot A0
#define Pushbutton 2

//Pins for Motor 1 
#define INP1 3  
#define INP2 4 
#define EN1 9 // PWM

//Pins for Motor 2
#define INP3 5  
#define INP4 6 
#define EN2 10 // PWM

//Global Variables
  int PotReading = 0 , MOTOR_SPEED = 0;
  volatile bool State = 0;

void Forward (int input1 , int input2 ,int input3 ,int input4 , int Speed ) {
  Change_Speed(EN1,EN2,Speed);

  digitalWrite (input1 , HIGH);
  digitalWrite (input2 , LOW);
  digitalWrite (input3 , HIGH);
  digitalWrite (input4 , LOW);


}

void Backward (int input1 , int input2 ,int input3 ,int input4 , int Speed ) {
  Change_Speed(EN1,EN2,Speed);
  digitalWrite (input1 , LOW);
  digitalWrite (input2 , HIGH);
  digitalWrite (input3 , LOW);
  digitalWrite (input4 , HIGH);



}



void Stop (int input1 , int input2 ,int input3 ,int input4  ) {
  digitalWrite (input1 , LOW);
  digitalWrite (input2 , LOW);
  digitalWrite (input3 , LOW);
  digitalWrite (input4 , LOW);

}

void Change_Speed(int Enable1 , int Enable2 , int PWM_Signal) {
  analogWrite(Enable1 , PWM_Signal);
  analogWrite(Enable2 , PWM_Signal);

}

void ChangeDir(int input1 , int input2 ,int input3 ,int input4  , int speed){
  Stop(input1,input2,input3,input4 ) ;
  delay(100) ;

  if (State == 0  /*Backward*/ ) {
    Forward(input1,input2,input3,input4,speed) ;
    State = 1 ;
  }

  else {
    Backward(input1,input2,input3,input4,speed) ;
    State = 0;
  }

}


void setup() {
  Serial.begin(9600);
  for (int i = 3 ; i<= 6 ; i++) {
    pinMode(i , OUTPUT) ;
  }

  pinMode(EN1 , OUTPUT) ;
  pinMode(EN2 , OUTPUT) ;
  pinMode(Pushbutton , INPUT ) ;

  Serial.begin(9600);


}


void loop() {


  PotReading = analogRead(Pot) ;
  MOTOR_SPEED = map(PotReading , 0 , 1024 , 0 , 255) ;

  if  (digitalRead(Pushbutton) == 1) {
    ChangeDir(INP1 , INP2,INP3,INP4 , MOTOR_SPEED) ;
  }
  
  Change_Speed(EN1,EN2,MOTOR_SPEED);

  

  delay(100);

}



