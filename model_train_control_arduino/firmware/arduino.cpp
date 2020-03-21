#include <ros.h>
#include <std_msgs/String.h>
//#include <std_msgs/Float32.h>
#include <std_msgs/Int32.h>
#include <std_msgs/UInt8.h>
//#include <geometry_msgs/Point.h>
//#include <model_train_control_arduino/point_command.h>
#include <stdio.h>
#include <stdlib.h>

#include <Arduino.h>

#define BAUD 9600
#define MAX_THROTTLE 255 //255 for normal voltage

#define POINT_1_PIN 4
#define POINT_2_PIN 2
#define POINT_1_STRAIGHT 100 //in range 0-255
#define POINT_2_STRAIGHT 177 //in range 0-255
#define POINT_1_TURN 140 //in range 0-255
#define POINT_2_TURN 110//in range 0-255
#define SWITCH_DURATION 1.0 //s

#define SERVO_DELAY 20 //ms

ros::NodeHandle nh;

std_msgs::String str_msg;

int throttle_val = 0;
uint8_t direction = 0;
bool new_throttle = false;
bool new_dir = false;

bool new_point_command = false;
bool straight = true;
int new_pc_pin;
uint8_t new_pc_pos;

ros::Publisher chatter("chatter", &str_msg);

bool state = true;


//(servo_pin, POINT_x_TURN || POINT_x_STRAIGHT)
//position range 0,255 will be converted to pulse range
void switch_point(int servo_pin, int position) {
    int start_time = millis();
    int current_time = millis();
    int servo_pulse=map(position, 0, 255, 600, 2400);

    while (abs(start_time - current_time)/1000 < SWITCH_DURATION) {
        digitalWrite(servo_pin, HIGH);
        delayMicroseconds(servo_pulse);
        digitalWrite(servo_pin, LOW);
        delay(SERVO_DELAY);
        current_time = millis();
    }
}

void ard_throttle_cb(const std_msgs::UInt8& msg)
{
    throttle_val = msg.data;
    new_throttle = true;
}

void ard_dir_cb(const std_msgs::UInt8& dir) {
    direction = dir.data;
    new_dir = true;
}

void ard_point_command_cb(const std_msgs::Int32& pc) {
    new_point_command = true;
    new_pc_pin = pc.data/1000;
    int tmp = new_pc_pin*1000;
    new_pc_pos = pc.data - tmp;

}

ros::Subscriber<std_msgs::UInt8> man_throttle("ard_throttle", ard_throttle_cb);
ros::Subscriber<std_msgs::UInt8> sub_arduino_dir("ard_dir", ard_dir_cb);
ros::Subscriber<std_msgs::Int32> sub_point_command("ard_point_command", ard_point_command_cb);



void initialization()
{
    //for each point motor: set it to turn, then set to straight
    //switch_point(POINT_1_PIN, POINT_1_TURN);
    switch_point(POINT_1_PIN, POINT_1_STRAIGHT);
    //switch_point(POINT_2_PIN, POINT_2_TURN);
    switch_point(POINT_2_PIN, POINT_2_STRAIGHT);

}


void setup()
{
    nh.getHardware()->setBaud(BAUD);
    nh.initNode();
    nh.advertise(chatter);
    nh.subscribe(man_throttle);
    nh.subscribe(sub_arduino_dir);
    nh.subscribe(sub_point_command);

    //motor pin setup
    pinMode(12,OUTPUT); //Initiates DC power on Motor A
    pinMode(9,OUTPUT); //Intitiates Brake on Motor A

    //servo pin setup
    pinMode(POINT_1_PIN, OUTPUT);
    pinMode(POINT_2_PIN, OUTPUT);

    //PWM frequency adjustment for track power.
    //WARNING: use ONLY 31372Hz setting (higher than 20k) for coreless motors
    TCCR2B = TCCR2B & B11111000 | B00000001;    // set timer 2 divisor to     1 for PWM frequency of 31372.55 Hz
    //TCCR2B = TCCR2B & B11111000 | B00000010;    // set timer 2 divisor to     8 for PWM frequency of  3921.16 Hz
    //TCCR2B = TCCR2B & B11111000 | B00000011;    // set timer 2 divisor to    32 for PWM frequency of   980.39 Hz
    //TCCR2B = TCCR2B & B11111000 | B00000100;    // set timer 2 divisor to    64 for PWM frequency of   490.20 Hz (The DEFAULT)
    //TCCR2B = TCCR2B & B11111000 | B00000101;    // set timer 2 divisor to   128 for PWM frequency of   245.10 Hz
    //TCCR2B = TCCR2B & B11111000 | B00000110;    // set timer 2 divisor to   256 for PWM frequency of   122.55 Hz
    //TCCR2B = TCCR2B & B11111000 | B00000111;    // set timer 2 divisor to  1024 for PWM frequency of    30.64 Hz

    initialization();

}



void update(){
    // motor
    if (new_dir) {
        new_dir = false;

        if (direction == 2) {
            //2 is DIR_BACKWARD
            digitalWrite(12,LOW); //Establish Backward Direction
            digitalWrite(9,LOW); //Release the Brake
        }
        else if (direction == 1) {
            //1 is DIR_FORWARD
            digitalWrite(12,HIGH); //Establish Forward Direction
            digitalWrite(9,LOW); //Release the Brake
        }
        else {
            //should be 0 DIR_STOP
            analogWrite(3, 0);
        }
    }

    if (new_throttle && direction != 0) {
        new_throttle = false;
        if ((throttle_val >= 0) && (throttle_val <= MAX_THROTTLE)){
            analogWrite(3, throttle_val);
        }
    }

    //points
    if (new_point_command) {
        new_point_command = false;
        switch_point(new_pc_pin, new_pc_pos);
    }
}

void loop()
{
    update();
    nh.spinOnce();
}
