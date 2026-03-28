//Smart rubish bin
//By Breadboarders

//Same code - forgot to commit it from my account =)

//NOTE//
//defined pins - all caps
//variables - first word with small letters, second - starts with a capital

//Including libraries
#include <LedControl.h> //matrix library
#include <Stepper.h> //stepper motor library
#include <Servo.h> //servo motor library

////////////////////////////////////////////
////////////////////////////////////////////

//defining pins
//matrix pins
#define CS 9 //cs matrix display pin
#define DIN 10 //din matrix display pin
#define CLK 11 //clk matrix display pin

bool has_candy = true;

//button pins
#define BUTTON_PIN 4 //button pin where we read if it was pressed or not
#define POWER_PIN 13 //connect 5v pin to arduino pin 13 so we can decide when to give electricity to the button

//photoelectric sensor pins
#define EMITTER 6
#define PHOTO_RESISTOR A4 //connect to analog pin 5

#define SENSOR_PIN A3

//distance sensor pins
#define DISTANCE_PIN A5 //connect to analog pin 3

//stepper motor pins
#define STEPPER_PIN_1 9 //first stepper pin to digital pin 9 to Arduino
#define STEPPER_PIN_2 10 //second stepper motor pin is connected to digital pin 10 of the Arduino
#define STEPPER_PIN_3 11 //third motor pin --> digital pin 11
#define STEPPER_PIN_4 12 //fourth motor pin --> digital pin 12

/////////////////////////////////////////////////////////////////////////////////

//initializing variables
//stepper motor variables
int steps = 1024; //half rotation
int speed = 10; //speed for the stepper motor --> calculated in revolutions per  minute --> max speed is 15-20 rpm

//button state --> a variable where we store what we have read from the button (HIGH/LOW)
int buttonState;                     //we see if the button is pressed or not
int time_close;

//sensor variables
int sensorValue; //a variable where we store what we have read from the distance sensor (from 0 to 5V as we use the analogRead() function)

long long time;

//counter - displayed on matrix
int counter=0; //starts at zero

int time_open_start;

bool has_new_trash = false; //true or false variable
bool is_opened = false;

//defining objects from specific libraries
//matrix
LedControl matrix = LedControl(DIN, CLK, CS, 1); //din pin/ clk pin/ cs pin/ 1 - number of matrix displays
//LedControl matrix defines and object called matrix as a led control device (matrix display)

//stepper motor
Stepper myStepper(steps, STEPPER_PIN_1, STEPPER_PIN_2, STEPPER_PIN_3, STEPPER_PIN_4); //Stepper myStepper defines an object called myStepper as a Stepper motor

Servo myServo; //da obqsnq

//matrix number functions
void zero() //type - void (won't return anything)
{
  matrix.setLed(0,1,5,true); //setting led with adress 0 (first matrix display if there are more of them)
  matrix.setLed(0,2,5,true); 
  matrix.setLed(0,3,5,true); // row 3 of the matrix display/ column 5/ write true if you want it to light up
  matrix.setLed(0,4,5,true);
  matrix.setLed(0,5,5,true);
  matrix.setLed(0,6,5,true);
  matrix.setLed(0,1,6,true);
  matrix.setLed(0,6,6,true);
  matrix.setLed(0,1,7,true);
  matrix.setLed(0,2,7,true);
  matrix.setLed(0,3,7,true);
  matrix.setLed(0,4,7,true);
  matrix.setLed(0,5,7,true);
  matrix.setLed(0,6,7,true); //displays the number zero
}

void one()
{
  //da se opravi

  matrix.setLed(0, 1, 6, true);
  matrix.setLed(0, 2, 6, true);
  matrix.setLed(0, 3, 6, true);
  matrix.setLed(0, 4, 6, true);
  matrix.setLed(0, 5, 6, true);
  matrix.setLed(0, 6, 6, true); //displays nuber one
}

void two()
{
  matrix.setLed(0, 1, 5, true);
  matrix.setLed(0, 1, 6, true);
  matrix.setLed(0, 1, 7, true);
  matrix.setLed(0, 1, 7, true);
  matrix.setLed(0, 2, 7, true);
  matrix.setLed(0, 3, 7, true);
  matrix.setLed(0, 4, 5, true);
  matrix.setLed(0, 4, 6, true);
  matrix.setLed(0, 4, 7, true);
  matrix.setLed(0, 4, 7, true);
  matrix.setLed(0, 5, 5, true);
  matrix.setLed(0, 6, 5, true);
  matrix.setLed(0, 6, 6, true);
  matrix.setLed(0, 6, 7, true);
  matrix.setLed(0, 6, 7, true); //displays nuber two
}

void three()
{
  matrix.setLed(0, 1, 5, true);
  matrix.setLed(0, 1, 6, true);
  matrix.setLed(0, 1, 7, true);
  matrix.setLed(0, 2, 7, true);
  matrix.setLed(0, 3, 7, true);
  matrix.setLed(0, 4, 5, true);
  matrix.setLed(0, 4, 6, true);
  matrix.setLed(0, 4, 7, true);
  matrix.setLed(0, 5, 7, true);
  matrix.setLed(0, 6, 5, true);
  matrix.setLed(0, 6, 6, true);
  matrix.setLed(0, 6, 7, true); //displays number three

}

void four()
{
  matrix.setLed(0, 1, 5, true);
  matrix.setLed(0, 1, 7, true);
  matrix.setLed(0, 2, 5, true);
  matrix.setLed(0, 2, 7, true);
  matrix.setLed(0, 3, 5, true);
  matrix.setLed(0, 3, 7, true);
  matrix.setLed(0, 4, 5, true);
  matrix.setLed(0, 4, 6, true);
  matrix.setLed(0, 4, 7, true);
  matrix.setLed(0, 5, 7, true);
  matrix.setLed(0, 6, 7, true); //displays number four

}

void five()
{
  matrix.setLed(0, 1, 5, true);
  matrix.setLed(0, 1, 6, true);
  matrix.setLed(0, 1, 7, true);
  matrix.setLed(0, 2, 5, true);
  matrix.setLed(0, 3, 5, true);
  matrix.setLed(0, 4, 5, true);
  matrix.setLed(0, 4, 6, true);
  matrix.setLed(0, 4, 7, true);
  matrix.setLed(0, 5, 7, true);
  matrix.setLed(0, 6, 5, true);
  matrix.setLed(0, 6, 6, true);
  matrix.setLed(0, 6, 7, true); //displays number five
}

void six()
{
  matrix.setLed(0,1,5,true);
  matrix.setLed(0,2,5,true);
  matrix.setLed(0,3,5,true);
  matrix.setLed(0,4,5,true);
  matrix.setLed(0,5,5,true);
  matrix.setLed(0,6,5,true);
  matrix.setLed(0,1,6,true);
  matrix.setLed(0,4,6,true);
  matrix.setLed(0,6,6,true);
  matrix.setLed(0,1,7,true);
  matrix.setLed(0,4,7,true);
  matrix.setLed(0,5,7,true);
  matrix.setLed(0,6,7,true); //displays number six
}

void seven()
{
  matrix.setLed(0,1,5,true);
  matrix.setLed(0,1,6,true);
  matrix.setLed(0,1,7,true);
  matrix.setLed(0,2,7,true);
  matrix.setLed(0,3,7,true);
  matrix.setLed(0,4,7,true);
  matrix.setLed(0,5,7,true);
  matrix.setLed(0,6,7,true); //displays number seven
}

void eight()
{
  matrix.setLed(0,1,5,true);
  matrix.setLed(0,2,5,true);
  matrix.setLed(0,3,5,true);
  matrix.setLed(0,4,5,true);
  matrix.setLed(0,5,5,true);
  matrix.setLed(0,6,5,true);
  matrix.setLed(0,1,6,true);
  matrix.setLed(0,3,6,true);
  matrix.setLed(0,6,6,true);
  matrix.setLed(0,1,7,true);
  matrix.setLed(0,2,7,true);
  matrix.setLed(0,3,7,true);
  matrix.setLed(0,4,7,true);
  matrix.setLed(0,5,7,true);
  matrix.setLed(0,6,7,true); //displays number eight
}

void nine()
{
  matrix.setLed(0, 1, 5, true);
  matrix.setLed(0, 1, 6, true);
  matrix.setLed(0, 1, 7, true);
  matrix.setLed(0, 1, 7, true);
  matrix.setLed(0, 2, 5, true);
  matrix.setLed(0, 2, 7, true);
  matrix.setLed(0, 3, 5, true);
  matrix.setLed(0, 3, 7, true);
  matrix.setLed(0, 4, 5, true);
  matrix.setLed(0, 4, 6, true);
  matrix.setLed(0, 4, 7, true);
  matrix.setLed(0, 4, 7, true);
  matrix.setLed(0, 5, 7, true);
  matrix.setLed(0, 6, 5, true);
  matrix.setLed(0, 6, 6, true);
  matrix.setLed(0, 6, 7, true);
  matrix.setLed(0, 6, 7, true); //displays number nine
}

//tenths on matrix display
//numbers in these functions use the first three columns of the matrix display

void one_t()
{
  matrix.setLed(0, 1, 1, true);
  matrix.setLed(0, 2, 1, true);
  matrix.setLed(0, 3, 1, true);
  matrix.setLed(0, 4, 1, true);
  matrix.setLed(0, 5, 1, true);
  matrix.setLed(0, 6, 1, true); //displays number one as in tenths
}

void two_t()
{
  matrix.setLed(0, 1, 0, true);
  matrix.setLed(0, 1, 1, true);
  matrix.setLed(0, 1, 2, true);
  matrix.setLed(0, 1, 2, true);
  matrix.setLed(0, 2, 2, true);
  matrix.setLed(0, 3, 2, true);
  matrix.setLed(0, 4, 0, true);
  matrix.setLed(0, 4, 1, true);
  matrix.setLed(0, 4, 2, true);
  matrix.setLed(0, 4, 2, true);
  matrix.setLed(0, 5, 0, true);
  matrix.setLed(0, 6, 0, true);
  matrix.setLed(0, 6, 1, true);
  matrix.setLed(0, 6, 2, true);
  matrix.setLed(0, 6, 2, true); //displays number two as in tenths //max is 20
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

void display_number()
{
  switch (counter)
  { //we use the counter variable so we can see how many times a trash was placed in the bin
    case 0:
      zero();
      //delay(3500);
      matrix.clearDisplay(0); //clears display - takes 0 as an argument (the adress of the matrix) 
      break;

    case 1: //if counter == 1 --> displays number 1 with the function
      one(); //calls the function that displays the number
      //goes out of the cycle --> breaks the cycke so only one case is possible at a time
      matrix.clearDisplay(0); //clears display - takes 0 as an argument (the adress of the matrix) 
                                          //because we are using the first display (with adress/index = 0)
      break;
    case 2: //if counter == 2 --> displays number 2 with the function
      two(); //calls the function that displays the number
  //goes out of the cycle (breaks it) so only one case is possible at a time
      matrix.clearDisplay(0); //clears the display
      break;
    case 3: //repeats --> if counter == 3 --> displays number 3 with the function
      three(); //repeats
      //repeats
      delay(3500); //waits 3.5 seconds before clearing screen
      matrix.clearDisplay(0); //clears the display
      break;
    case 4:
      four(); ////repeats --> if counter == 4 --> displays number 4 with the function
      
      matrix.clearDisplay(0); //clears the display
      break;
    case 5:
      five(); //repeats --> if counter == 5 --> displays number 5 with the function
      matrix.clearDisplay(0); //clears the display
      break;
    case 6:
      six();
      
      matrix.clearDisplay(0); //clears the display
      break;
    case 7:
      seven();
      
      matrix.clearDisplay(0); //clears the display
      break;
    case 8:
      eight();
      
      matrix.clearDisplay(0); //clears the display
      break;
    case 9:
      nine();
    
     
      matrix.clearDisplay(0); //clears the display
      break;
    case 10:
      one_t(); //a function that uses only the first three columns of the matrix since the number is part of the tenths
      zero();
      
     
      matrix.clearDisplay(0); //clears the display
      break;
    case 11:
      one_t(); //repeats the same number
      one();
      
      //delay(3500); //waits 3.5 seconds before clearing screen
      matrix.clearDisplay(0); //clears the display
      break;
    case 12:
      one_t();
      two();
      
      //delay(3500); //waits 3.5 seconds before clearing screen
      matrix.clearDisplay(0); //clears the display
      break;
    case 13:
      one_t();
      three();
      
      //delay(3500); //waits 3.5 seconds before clearing screen
      matrix.clearDisplay(0); //clears the display
      break;
    case 14:
      one_t();
      four();
      
      //delay(3500); //waits 3.5 seconds before clearing screen
      matrix.clearDisplay(0); //clears the display
      break;
    case 15:
      one_t();
      five();
      
      delay(3500); //waits 3.5 seconds before clearing screen
      matrix.clearDisplay(0); //clears the display
      break;
    case 16:
      one_t();
      six();
      
      delay(3500); //waits 3.5 seconds before clearing screen
      matrix.clearDisplay(0); //clears the display
      break;
    case 17:
      one_t();
      seven();
      //delay(3500); //waits 3.5 seconds before clearing screen
      matrix.clearDisplay(0); //clears the display
      break;
    case 18:
      one_t();
      eight();
      //delay(3500); //waits 3.5 seconds before clearing screen
      matrix.clearDisplay(0); //clears the display
      break;
    case 19:
      one_t();
      nine();
      //delay(3500); //waits 3.5 seconds before clearing screen
      matrix.clearDisplay(0); //clears the display
      break;
    case 20:
      two_t();
      zero();
      //last case since the max score is 20
      //delay(3500); //waits 3.5 seconds before clearing screen
      matrix.clearDisplay(0); //clears the display
      counter=0;
      break;
  }
}
void setup() //runs only one time
{
  matrix.shutdown(0, false); //turns on the matrix/ if matrix.shutdown() was set to true it would turn off
  matrix.setIntensity(0, 5); //sets the brightness
  matrix.clearDisplay(0); //clears the display
  //the first argument is always zero because it is the first display - since we are using only one matrix display its index is zero

 

  //button
  pinMode(BUTTON_PIN, INPUT); //button --> gets information

  //stepper motor --> all pins display information so all pins are set as outputs
  pinMode(STEPPER_PIN_1, OUTPUT);
  pinMode(STEPPER_PIN_2, OUTPUT);
  pinMode(STEPPER_PIN_3, OUTPUT);
  pinMode(STEPPER_PIN_4, OUTPUT);

  //distance sensor --> gets information
  pinMode(DISTANCE_PIN, INPUT);

  pinMode(SENSOR_PIN, INPUT);

  //sets stepper speed
  myStepper.setSpeed(speed); //calculated in revolutions per minute

  //da opisha
  myServo.attach(5);
  for(int pos=0; pos<90; pos++){
    myServo.write(90);
    delay(15);

  }
 
  //turns on serial monitor so that the microcontroller can send information to the computer
  Serial.begin(9600); //sets 9600 (default) as baud rate
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////


void loop() //runs until no electricity goes through the electric chain
{
  //working with sensor for distance to see if a hand has passed through (so that the servo motor can open the top part of the bin)
  int distanceValue = analogRead(DISTANCE_PIN); //reading the sensor value from 0 to 5V



  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  int sensorValue = analogRead(SENSOR_PIN); //reads the value of the photoelectric sensor from 0 to 5V and stores it in a variable called sensorValue

  //Serial.println(sensorValue); //printing sensor value in serial monitor (ln --> new line every time)
  Serial.println(sensorValue);
  digitalWrite(POWER_PIN, LOW);
  counter=0;
  if (distanceValue >= 250) //if the distance sensor "sees" something that is close to it
  {
    if (is_opened == false)
    {
      is_opened = true;

      myServo.write(-90); //rotate servo motor --> open the top part of the bin
      time_open_start = millis();
      display_number();
      delay(10);

    }
    if (is_opened == true)
    {
      time_open_start = millis();
      display_number();
    }
   
  }
  else
  {
    if (millis() - time_open_start > 7500)
    {
      is_opened = false;
    }
    //else - continue
  }
  if(is_opened == false){
    myServo.write(90);
    delay(15);
  }

  
     //turn off the 5V pin on the button so that it can only be pressed when a specific statement is true
                                        //no electricity goes through the button unless something happens
    
    if (sensorValue>250)
    {
      if (has_new_trash == false)
      {
            has_new_trash = true;
            time = millis(); //start counting time in miliseconds --> devide it by 1000 because we will work with seconds
            counter++; 
            display_number();

      }
      if ((millis() - time>=30000) && counter>=5) //if the sensor value has been low for thirty seconds or more (meaning the trash is full and there are objects that are blocking the sensors)
      {
          digitalWrite(POWER_PIN, HIGH); //we give electricity to the button 
          buttonState = digitalRead(BUTTON_PIN); //reads the button pin and stores it in a variable called buttonState
          has_candy = false;
          if (buttonState == HIGH) //we read the button pin (the variable where the information was stored) and we see if the button has been pressed
          {
            if (has_candy==true)
            {
              myStepper.step(0);
              myStepper.setSpeed(0);
            }
            else
            {
              myStepper.step(steps); //rotate the stepper for the exact amount of steps --> for 28BYJ-48 stepper motor the full rotation is 2048 steps -->
              delay(2500); //waits for 3.5 seconds                                 // --> since we need a half rotation we use steps = 1024;
              myStepper.step(steps); //makes a half rotation again in the same direction so that the stepper motor is in the same direction as we started
              delay(2500);
              has_candy=true;
              has_new_trash = false;
            }
            
          }
          else
          {
             has_new_trash = false;
          }
      }
      else
      {
        has_new_trash = false;
      }
    }
  else
  {
    has_new_trash = false;
  } 
}
