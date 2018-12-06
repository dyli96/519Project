/*
 * rosserial Subscriber Example
 * Blinks an LED on callback
 */
#include "mbed.h"
#include <ros.h>
#include <std_msgs/Empty.h>
#include <geometry_msgs/Twist.h>

ros::NodeHandle nh;
//DigitalOut myled(LED1);
PwmOut myled(LED1);

float pwmValue=0.0f;
float pwmValue1=0.0f;

void messageCb(const geometry_msgs::Twist& twist){
   // myled = 0xff;   // blink the led
  // myled = twist.linear.x;
    pwmValue = (float)((twist.linear.x+2.0f)/(4.0f));       //values will come in between -2 to +2
    
    pwmValue1 = (float)((twist.linear.y+2.0f)/(4.0f));       //values will come in between -2 to +2
}

ros::Subscriber<geometry_msgs::Twist> sub("turtle1/cmd_vel", &messageCb);

int main() {
    myled.period(0.01f);                                      //10 mSec period
    nh.initNode();
    nh.subscribe(sub);
    
    while (1) 
   {
        nh.spinOnce();
        if(pwmValue1==1.0f){myled.write(0.0f);}
        else if(pwmValue1==0.0f){myled.write(1.0f);}
        else {myled.write(pwmValue);}
        
        wait_ms(1);
    }
}

