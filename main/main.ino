#include "MeOrion.h"

int leftSensor;
int rightSensor;

int[][] board = new int[4][7];

int curr_x = 0;
int curr_y = 0;
String curr_d = "N";

MeDCMotor motor1(PORT_1);
MeDCMotor motor3(M1);

MeDCMotor motor2(PORT_2);
MeDCMotor motor4(M2);

uint8_t motorSpeed = 100;

MeUltrasonicSensor ultraSensor(PORT_7);

void setup() {
  
  Serial.begin(9600);

  pinMode(12, INPUT);
  pinMode(9, INPUT);
  
}

void loop() {

  leftSensor = digitalRead(12);
  rightSensor = digitalRead(9);
  
  Serial.print(leftSensor);
  Serial.println(rightSensor);

  Serial.print(ultraSensor.distanceCm() );
  Serial.println(" cm");
  
  drive();

  if (leftSensor == 0 && rightSensor == 0) {
    brake();
    checkNode();
  }
  
}

void drive() {

  motor1.run(motorSpeed);
  motor2.run(-motorSpeed);
  motor3.run(motorSpeed);
  motor4.run(-motorSpeed);
  
}

void brake() {
  
  motor1.stop();
  motor2.stop();
  motor3.stop();
  motor4.stop();
  
}


void checkNode() {

  switch(curr_d) {

    case "N": curr_y++; break;
    case "E": curr_x++; break;
    case "S": curr_y--; break;
    case "W": curr_x--; break;
  }

  
  if(ultraSensor.distanceCm() < 36) {
    //call BFS and drive accordingly

     
  }


}
