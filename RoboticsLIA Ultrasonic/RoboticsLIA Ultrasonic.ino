/*
Smart Car kit Elegoo V4
Object avoider 
The goal of this program is to use an ultrasonic sensor attached to a servo motor to indicate the direction of the car. If the ultrasonicsensor detects an object, 
the servo motor will move the sensor to the left and will read the distance again. If there's no object detected, the car will turn left and continue forward.
If there's an object, the car will check on the right, and continue if there's no object. If in both directions there's an object, the car will turn back and continue
until detecting an object. 
*/

#define MA 7 //pin for direction of motor A
#define MB 8 //pin for direction of motor B
#define SA 5 //pin for speed of motor A
#define SB 6 //pin for speed of motor B

#define trigPin  13 //Pin that is connected to the Trigger pin
#define echoPin  12 //Pin that is connected to the Echo pin

#include <Servo.h> //Includes library to control servo motor

Servo myservo;  // create servo object to control a servo

float duration; // Stores pulse duration value
float distance; // Stores calculated distance in cm

void setup() {
  // define pins for moving the car as outputs
  pinMode(MA,OUTPUT);
  pinMode(MB,OUTPUT);
  pinMode(SA,OUTPUT);
  pinMode(SB,OUTPUT);
  pinMode(3,OUTPUT); //this pin enables the movement of the motors

  pinMode(trigPin, OUTPUT); //define trigger pin as an output
  pinMode(echoPin, INPUT); //define echo pin as an input

  myservo.attach(10);  // attaches the servo on pin 10 to the servo object

  Serial.begin(9600); //intialize serial monitor

}

void move (bool a, int s1, bool b, int s2){ //general function for the car movement
	digitalWrite(MA,a); //digitalWrite in motor A the direction in accordance to the movement
	analogWrite(SA,s1); //analogWrithe the velocity for motor A
	
	digitalWrite(MB,b); //digitalWrite in motor B the direction in accordance to the movement
	analogWrite(SB,s2); //analogWrithe the velocity for motor B
}

void forward (int x){ //function for moving forward with x speed
  move(1,x,1,x); //use the move function and pass the values to the function 
}

void backward (int x){ //function for moving backwards with x speed
  move(0,x,0,x); //use the move function and pass the values to the function 
}

void stop (){ //function for stopping
  move(1,0,1,0); //any movement with 0 speed will stop the car
}

void left (int x){ //function for moving left with x speed
  move(1,x,0,x); //use the move function and pass the values to the function 
}

void right (int x){ //function for moving rigth with x speed
  move(0,x,1,x); //use the move function and pass the values to the function 
}

void leftforward (int x){ //function for moving leftforward with x speed
  move(1,x,1,x/2); //use the move function and pass the values to the function 
}

void rightforward (int x){ //function for moving rightforward with x speed
  move(1,x/2,1,x); //use the move function and pass the values to the function 
}

void loop() {
  digitalWrite(3,1); //enables pin for moving the car
  
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); //sends a pulse with the trigger pin 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH); //times the duration of the pulse 
  distance = (duration/2)*0.0343;  //calculates the distance with the duration read

   Serial.print("Distance: "); //Serial print to debug

   
if (distance>=400) {  //If the distance is greater than 400cm
  Serial.println("Out of range"); //print to debug
  Serial.println("Forward"); //print to debug
  forward(100); //move forward because it means there's no obstacle 
}
else {
Serial.print(distance); //print to debug

if (distance>=15){ //if the distance is greater than 15cm 
  Serial.println("Forward"); //print to debug
  forward(100); //move forward
}
if (distance<15){
  Serial.println("Stop"); //print to debug
  stop(); //stop if the distance is less than 15cm
  delay(1000); //Stop during a second
  Serial.println("Left"); //print to debug
  myservo.write(180); //move sensor to the left
  
  //Read again the distance------------------------
  digitalWrite(trigPin, LOW);               
  delayMicroseconds(2);                     
  digitalWrite(trigPin, HIGH);              
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2)*0.0343;
  //-----------------------------------------------

  stop(); //This stop is just to remark the movement of the car to see if it is working well 
  delay(1000); //Stop during a second
  
  if (distance<15){ //if an object is detected on the left
  myservo.write(0); //move sensor to the right

  //Read again the distance------------------------
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2)*0.0343; 
  //-----------------------------------------------

  stop(); //This stop is just to remark the movement of the car to see if it is working well 
  delay(1000); //stop during a second
  
  if (distance<15){ //if there's an object also on the right
    left(100);            //turn back
    delay(1350);          //turn to the left enough time to turn back
    stop();               //Stops
    delay(1000);          //Stop during a second
    myservo.write(90);    //Position the sensor to the front again
  }
  else{
    right(100); //If there's no object on the right move the car to the right 
    delay(1000); //move enough time to turn 90°
    myservo.write(90);   //Position the sensor to the front again
  }
  
  }
  else{
  left(100); //If there's no object on the left, move the car to the left 
  delay(1000); //move enough time to turn -90°
  myservo.write(90);  //Position the sensor to the front again
  }  
  }
}
}
