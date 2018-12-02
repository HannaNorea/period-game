/*  This is a simulation of period pain
   Copyright Isra Rab and Hanna Thenor Årström, All rights reserved
   It consists of 2 servos, one waterpump, one potentionmeter, one joystick and LED
   Early Autumn version 2018
*/

#include <Servo.h>
Servo servo1;
Servo servo2; // create servo object to control 2 servos

//motor A connected between A01 and A02, no second motor

//Motor A
int STBY = 10; //standby
int PWMA = 7; //Speed control
int AIN1 = 8; //Direction
int AIN2 = 9; //Direction

//Servo 1 & 2 variables
const int SERVO1 = 5;
const int SERVO2 = 6;
//Potentiometer and Joystcik
const int pot = A0;
const int joyY = A1; // analog pin connected to Y output
//LED
const int led = 3;

int potVal, rotate, joyVal, joystick;
int servoCounter1 = 0;
//int servoCounter2 = 0;
int randAngle1 = 0;
//int randAngle2 = 0;
int randTime1 = 10000;
//int randTime2 = randTime1;

int pumpSpeed = 255;

unsigned long lastMillis = 0;
unsigned long currentMillis;
const unsigned long stopGame = 10000;

void servo_pot(int Val) {
  //mapping the potentiometer value to degrees of servo angle
  rotate = map(Val, 0, 1023, 0, 90);

  if (servoCounter1 >= randTime1) {
    // a random angle is added with the random interval randTime1
    randTime1 = random(5000, 10000);
    randAngle1 = random(-25, 25);
    servoCounter1 = 0;
  }
  int angle = rotate + randAngle1;
  servo1.write(angle);
  //servo2.write(angle);

  // rotate2 = map(Val2, 0, 1023, 0, 70);
  /*if (servoCounter2 >= randTime2) {
    randTime2 = random(5000, 10000);
      Serial.println(randTime2);
    randAngle2 = random(-30, 30);
    servoCounter2 = 0;
    }
    servo2.write(rotate2 + randAngle2);*/
}
void servo_joystick(int Val) {
  //mapping the joystick values to degrees of servo rotational angle
  joystick = map(joyVal, 0, 1023, 0, 180);

  servo2.write(joystick);
  //Serial.println(joystick);

}
void pump_move(int speed, int direction) {
  //Move specific motor at speed and direction
  //motor: 0 for B 1 for A
  //speed: 0 is off, and 255 is full speed
  //direction: 0 clockwise, 1 counter-clockwise

  digitalWrite(STBY, HIGH); //disable standby

  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;

  if (direction == 1) {
    inPin1 = HIGH;
    inPin2 = LOW;
  }
  else{
    inPin1 = LOW;
    inPin2 = HIGH;
  }
  digitalWrite(AIN1, inPin1);
  digitalWrite(AIN2, inPin2);
  analogWrite(PWMA, speed);
}

//boolean pump_mode() {
//  //enable standby
//  if(gameover == true){
//  
//  }
//  else{
//    
//  }
//}

void gameover() {
  Serial.println("game over");
  digitalWrite(STBY, LOW);
  // Variables will change:
  int i = 0;
  
  for (i = 0; i < 10; i++) {
    Serial.println("blinking");
    // if the LED is off turn it on and vice-versa:
    digitalWrite(led, HIGH);
    delay(100);
    digitalWrite(led, LOW);
    delay(100);
    // set the LED with the ledState of the variable:
  } 
}

void setup() {
  Serial.begin(9600);// set up Serial library at 9600 bps Serial.println("Motor test!");
  Serial.println("Motor party!");

  servo1.attach(SERVO1);
  servo2.attach(SERVO2);

  pinMode(STBY, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(led, OUTPUT);

  digitalWrite(led, LOW);

  servo1.write(90);
  servo2.write(90);
}

void loop() {
  servoCounter1 ++;
  //servoCounter2 ++;
  // reading the potentiometer and sending to servo
  potVal = analogRead(pot);
  joyVal = analogRead(joyY);
  servo_pot(potVal);
  servo_joystick(joyVal);
  // Serial.println(potVal1);

  pump_move(pumpSpeed, 1); //motor 1, full speed, left
  currentMillis = millis();  //get the current millisecond

  if (currentMillis - lastMillis == stopGame) {
    Serial.println("FINISH!");
    gameover();
    Serial.println(lastMillis);
    Serial.println(currentMillis);
    lastMillis = currentMillis;
  }
}


