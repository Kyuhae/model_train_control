#ifndef DECISION_NODE_H
#define DECISION_NODE_H

#include "ros/ros.h"
#include"globals.h"
#include "std_msgs/String.h"
#include "std_msgs/Float32.h"
#include "std_msgs/Int32.h"
#include "std_msgs/Bool.h"
#include "std_msgs/UInt8.h"

#include "point.h"

class decision {
public:
    decision();
    void update();
    void throttleCallback(const std_msgs::Float32ConstPtr& m_t);
    void throttleSliderCallback(const std_msgs::Float32ConstPtr& val); //get throttle slider value [0.0, 255.0] from ui
    void dirCallback(const std_msgs::Int32ConstPtr& dir); //get train direction from ui (enum dir in globals.h)
    void pointCommandCallback(const std_msgs::Int32ConstPtr& pc); //get point to be switched

private:
    ros::NodeHandle n;

    ros::Subscriber sub_chatter;
    ros::Subscriber sub_throttle_slider;
    ros::Subscriber sub_dir;
    ros::Subscriber sub_point_command;

    ros::Publisher pub_ard_throttle;
    ros::Publisher pub_ard_dir;
    ros::Publisher pub_ard_point_command;

    float man_t_val;

    bool new_man_t;
    bool new_dir;

    dirEnum dir_val;

    std::map<int, Point*> points_map;

};

#endif //DECISION_NODE_H
