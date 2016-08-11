/*
 * Antz
 * Antz Framework
 * EcsBot.cpp
 *		ECS 101 student code.
 * Copyright (c) 2015 ELi Goldweber. All rights reserved.
 * License: <#license#>
 */
#include "EcsBot.h"

using namespace Antz;

/* EcsBot -- Contructor */
EcsBot::EcsBot(uint32_t robotId):
AntzRobot(robotId){}

/* setup -- setup routine for EcsBot */
void EcsBot::setup() {
  
    AntzRobot::setup();
    Serial.begin(9600);
}
/* Creating variables for use in the EcsBot loop */
int counter = 0;
int stuck = 0;
boolean leftBlocked = false;
boolean midBlocked = false;
boolean rightBlocked = false;
boolean blocked1 = false;

/* loop -- loop routine for EcsBot */
void EcsBot::loop() {
  do{
    counter = 0;//resetting variables necessary for the do-while loop
    leftBlocked = false;
    midBlocked = false;
    rightBlocked = false;
    blocked1=false;
  
  
    delay(10);//short delay for caution after moving forward
    for (int i = 0; i<=80; i+=4)//checking on the right side
    {
      scanner.scanAt(i);//setting the scanner to the degree of the value of i
      float f = scanner.getDistanceFront();//checking the distance the scanner is measuring.
      Serial.println(f);//pritning that distance to the serial
      delay(27);//delay for the scanner
      if (f <= 18){//if the value recorded by the scanner is less than 18
        turnLeft(18);//turn left 18 degrees
        delay(175);//175 ms delay for the turn
        //counterLeft +=10;
        counter +=10;//add this value for counter, (necessary for if the robot gets stuck.)
        blocked1==true;//switch blocked1 to true, to for the loop to tell that the robot did have to avoid an obstacle. 
      }  //end if-statement
    }//end for loop
  
    
  
    for (int i = 180; i>=100; i-=4)//checking the left side
    {
      scanner.scanAt(i);//setting the scanner to the degree of the value of i
      float f = scanner.getDistanceFront();//checking the distance the scanner is measuring.
      Serial.println(f);//pritning that distance to the serial
      delay(27);//delay for the scanner
      if (f <= 18){//if the value recorded by the scanner is less than 18
        turnRight(18);//turn right 18 degrees
        delay(175);//175 ms delay for the turn
        counter +=10;//add this value for counter, (necessary for if the robot gets stuck.)
        blocked1==true;//switch blocked1 to true, to for the loop to tell that the robot did have to avoid an obstacle.
      } //end if-statement
    
    }//end for-loop
    
    for (int i = 80; i<=100; i+=5)//middle side
      {
        scanner.scanAt(i);//setting the scanner to the degree of the value of i
        float f = scanner.getDistanceFront();//checking the distance the scanner is measuring.
        Serial.println(f);//pritning that distance to the serial
        delay(27);//delay for the scanner
        if (f <= 18){//if the value recorded by the scanner is less than 15
          turnRight(90);//turn right 90 degrees
          delay(600);//delay 600 for the turn to the right
          counter +=90;//add this value for counter, (necessary for if the robot gets stuck.)
          blocked1=true;//switch blocked1 to true, to for the loop to tell that the robot did have to avoid an obstacle.
        } //end if-statement
      }//end for-loop
    
    stuck +=1;//add 1 to stuck
  
    //turnLeft(stuck);//if the robot can't decide where to turn
    if (stuck >3){//if the robot has been stuck for 4 loops
      turnLeft(180);//do a 180
      delay(1500);//delay for the robot to complete the 180
      display.number(true,9);//for debugging
      stuck = 0;//reset stuck
    }//end if-statement
  
      
    //counter = counterLeft + counterMid + counterRight;
    //counter = 90;
    if (stuck <=3)
    {
      display.number(true,8);
    }//end if-statement
    
    }while(blocked1==true);//end do-while loop
    
    goForward(137);//go forward 137
    display.number(true,7);//showing the number 7 for debugging 
    delay(150);//delay for a but longer than the goForward value
    stuck = 0;//set stuck to 0   
}











