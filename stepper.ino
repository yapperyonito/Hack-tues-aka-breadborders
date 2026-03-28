#include<Stepper.h>
Stepper myStepper(1024, 11, 10, 9, 8);
int steps=1024;
void setup() {
  // put your setup code here, to run once:
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  
  pinMode(7, OUTPUT);
  myStepper.setSpeed(20);
}

void loop() {
          myStepper.step(steps); //rotate the stepper for the exact amount of steps --> for 28BYJ-48 stepper motor the full rotation is 2048 steps -->
          delay(3500); //waits for 3.5 seconds                                 // --> since we need a half rotation we use steps = 1024;
          myStepper.step(steps); //makes a half rotation again in the same direction so that the stepper motor is in the same direction as we started
}