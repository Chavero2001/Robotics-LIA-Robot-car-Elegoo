/*
Smart Car kit Elegoo V4
Line tracker
The goal of this program is to use the line tracker module to make the car follow a line on the ground.
If it reaches the end of the line, turn back. 
*/

#include <IRremote.h> // Include IR Remote Library

#define MA 7 //pin for direction of motor A
#define MB 8 //pin for direction of motor B
#define SA 5 //pin for speed of motor A
#define SB 6 //pin for speed of motor B

int dataR; //variable in which will be store the value of the R sensor
int dataM; //variable in which will be store the value of the M sensor
int dataL; //variable in which will be store the value of the L sensor

void setup() {
  
  // define pins for moving the car as outputs
  pinMode(MA,OUTPUT);
  pinMode(MB,OUTPUT);
  pinMode(SA,OUTPUT);
  pinMode(SB,OUTPUT);
  pinMode(3,OUTPUT); //this pin enables the movement of the motors
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
  
  dataR= analogRead(A0); //Read the data of the Right sensor
  dataM= analogRead(A1); //Read the data of the Midle sensor
  dataL= analogRead(A2); //Read the data of the Left sensor
    
Serial.print("DataR: ");   //Serial print the value of DataR to know the values of the sensor before coding, it also can help to debug
Serial.print(dataR);
Serial.print("    DataM: "); //Serial print the value of DataM to know the values of the sensor before coding, it also can help to debug
Serial.print(dataM);
Serial.print("    DataL: "); //Serial print the value of DataL to know the values of the sensor before coding, it also can help to debug
Serial.println(dataL);


if(dataR<360 && dataM>300 && dataL<300) { //If the values are in this thereshold 
Serial.println("Forward"); //print to debug
forward(70); //move forward while the data have those values
} 

if(dataR>200 && dataM<300 && dataL<40){ //If the car start moving to the left the sensor on the right will increase its value
  Serial.println("Right"); //print to debug
  right(50); //move to the right until the values allow to continue forward
  
}

if(dataR<40 && dataM<300 && dataL>500){ //If the car start moving to the right the sensor on the right will increase its value
  Serial.println("Left"); //print to debug
  left(50); //move to the left until the values allow to continue forward
  
}
if(dataR<50 && dataM<50 && dataL<50){ //if the car reach the end of the line
  Serial.println("Turn");    //print to debug
    left(100);      //turn back
  delay(1350);      //move to the left enough time to turn back
  stop();           //stop before continuing 
  delay(1000);      //stop during a second
}

}
