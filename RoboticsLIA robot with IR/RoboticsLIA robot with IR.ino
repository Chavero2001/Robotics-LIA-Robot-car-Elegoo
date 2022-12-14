/*
Smart Car kit Elegoo V4
IR control
The goal of this program is to control the car by using an infrared control 
*/

#include <IRremote.h> // Include IR Remote Library

#define MA 7 //pin for direction of motor A
#define MB 8 //pin for direction of motor B
#define SA 5 //pin for speed of motor A
#define SB 6 //pin for speed of motor B

IRrecv irrecv(9); // Define IR Receiver and Results Objects
decode_results results; 

unsigned long lastCode; //variable to assign the lastCode 

void setup() {
  
   // define pins for moving the car as outputs
  pinMode(MA,OUTPUT);
  pinMode(MB,OUTPUT);
  pinMode(SA,OUTPUT);
  pinMode(SB,OUTPUT);
  pinMode(3,OUTPUT); //this pin enables the movement of the motors
  Serial.begin(9600); //intialize serial monitor
  
  irrecv.enableIRIn(); //Enable Infrared sensor
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
  
  if (irrecv.decode(&results)){
    // Print Code to debug
        Serial.println(results.value, HEX); //print in HEX 
        
        if(results.value == 0xFFFFFFFF) //FFFFFFFF is used to indicate when a value is repated
        {
          // If Repeat then use last code received
          results.value = lastCode;        
        }
        if(results.value==0xFF629D){ //move forward if the top arrow of the control is pressed
            lastCode = results.value;  //store the value of the code read in lastCode        
            forward(200); //move forward 
            delay(250);  //only during this time, because if the time is not specified, the car will continue forward
        }

        if(results.value==0xFFA857){ //move backward if the bottom arrow of the control is pressed
            lastCode = results.value; //store the value of the code read in lastCode        
           backward(200); //move backward
           delay(250); //move backward only for 1/4 second
       
        }
             
        if(results.value==0xFFC23D){ //move to the right if the right arrow of the control is pressed
            lastCode = results.value; //store the value of the code read in lastCode      
            right(200); //move to the right
            delay(250); //move only for 1/4 second
           
        }
        if(results.value==0xFF22DD){ //move to the left if the left arrow of the control is pressed
            lastCode = results.value;  //store the value of the code read in lastCode
           left(200); //move to the left
           delay(250); //move only for 1/4 second
           
        }
        
        irrecv.resume(); //continue reading the IR 

} else {
stop();  //stop if there's no reading
}
}
