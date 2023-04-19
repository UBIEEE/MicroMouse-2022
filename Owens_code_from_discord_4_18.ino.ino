//EXAMPLE CODE TO MAKE THE MICROMOUSE OF 2022/23 GO FORWARD, TURN RIGHT AND LEFT
//OPTIMIZATIONS CAN BE DONE, BUT THIS IS THE MOST BASIC FORM OF TURNING
//WRITTEN BY OWEN FARRELL

// Include the AFMotor library
#include <AFMotor.h>

// Number of steps per output rotation
const int stepsPerRevolution = 60;

// Create two instances 
AF_Stepper MotorL(stepsPerRevolution, 2);
AF_Stepper motorR(stepsPerRevolution, 1);

const int trigPin_frontleft = 13;
const int echoPin_frontleft = 12;
const int trigPin_frontright = 11;
const int echoPin_frontright = 10;
const int trigPin_left = 9;
const int echoPin_left = 8;
const int trigPin_right = 6;
const int echoPin_right = 7;
const int trigPin_front = 5;
const int echoPin_front = 4;
// defines variables
float duration_frontleft;
int distance_frontleft;
float duration_frontright;
int distance_frontright;
float duration_front;
int distance_front;
float duration_left;
int distance_left;
float duration_right;
int distance_right;
//Define forward variables
uint8_t L_on = 75;
uint8_t R_on = 75;
float diff;
float adjust;
float totalErrors;
float Kp = 1500;
float Ki = 900;
// ------------- //
// Predetermined values
// Motor shield pin left: A4
// Motor shield pin right: A5


void setup()
{
  pinMode(trigPin_frontleft, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin_frontleft, INPUT); // Sets the echoPin as an Input
  pinMode(trigPin_left, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin_left, INPUT); // Sets the echoPin as an Input  
  pinMode(trigPin_front, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin_front, INPUT); // Sets the echoPin as an Input  
  pinMode(trigPin_frontright, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin_frontright, INPUT); // Sets the echoPin as an Input   
  pinMode(trigPin_right, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin_right, INPUT); // Sets the echoPin as an Input 
  // set the speed at 60 rpm:
  motorL.setSpeed(500);
  motorR.setSpeed(500);
  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {
  // FORWARD
  // both motors on  
  for(int i; i < stepsPerRevolution; ++i)
  motorR.step(1,FORWARD,SINGLE);// < left motor on
  motorL.step(1,FORWARD,SINGLE);// < right motor on

  frontRead();
  frontLeftRead();
  frontRightRead();
  if(distance_front <= 10){
    if(distance_frontleft <= 10){
        // LEFT
      // left motor off
      motorL.step(1,BACKWARD,SINGLE);
      motorR.step(1,FORWARD,SINGLE);      
    }else if(distance_frontright <= 10){
        // Right
      // left motor off
      motorR.step(1,BACKWARD,SINGLE);
      motorL.step(1,FORWARD,SINGLE);   
    }else{
      motorL.step(1,BACKWARD,SINGLE);
      motorR.step(1,BACKWARD,SINGLE);
    }
  }
}
int leftRead(){
  // Clears the trigPin
  digitalWrite(trigPin_left, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin_left, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_left, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration_left = pulseIn(echoPin_left, HIGH);
  // Calculating the distance
  distance_left = duration_left * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance_left);
}

int rightRead(){
  // Clears the trigPin
  digitalWrite(trigPin_right, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin_right, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_right, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration_right = pulseIn(echoPin_right, HIGH);
  // Calculating the distance
  distance_right = duration_right * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance_right);
}

int frontRightRead(){
  // Clears the trigPin
  digitalWrite(trigPin_frontright, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin_frontright, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_frontright, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration_frontright = pulseIn(echoPin_frontright, HIGH);
  // Calculating the distance
  distance_frontright = duration_frontright * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance_frontright);
}

int frontLeftRead(){
  // Clears the trigPin
  digitalWrite(trigPin_frontleft, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin_frontleft, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_frontleft, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration_frontleft = pulseIn(echoPin_frontleft, HIGH);
  // Calculating the distance
  distance_frontleft = duration_frontleft * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance_frontleft);
}

int frontRead(){
  // Clears the trigPin
  digitalWrite(trigPin_front, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin_front, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_front, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration_front = pulseIn(echoPin_front, HIGH);
  // Calculating the distance
  distance_front = duration_front * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance_front);
}

int forward(){
  diff = (distance_left - distance_right);
  totalErrors += diff;
  adjust = (Kp*diff)/1000 + (Ki*totalErrors)/1000;
  //Correct drifting
  if(abs(diff) < 1.3){
    if((L_on - (adjust+1)/2)) < 50){
      L_on = 50;
    }else{
      L_on -=(adjust+1)/2;
    }
    if((L_on + (adjust)/2)) < 50){
      L_on = 50;
    }else{
      L_on +=(adjust)/2;
    }    
  }else{
    motorL.step(1,FORWARD,SINGLE);
    motorR.step(1,FORWARD,SINGLE);
    myStepper.step(10);  
  }
}

int turnRight(){

}

int turnLeft(){

}

int backward(){

}