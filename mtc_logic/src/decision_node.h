#ifndef DECISION_NODE_H
#define DECISION_NODE_H

#include "ros/ros.h"
#include"globals.h"
#include "std_msgs/String.h"
#include "std_msgs/Float32.h"
#include "std_msgs/Int32.h"
#include "std_msgs/Bool.h"
#include "std_msgs/UInt8.h"

#include "../common_src/state.h"
#include "../common_src/state_machine.h"
#include "../common_src/loco.h"

#include "point.h"

class decision {
public:
    decision();
    void update();
    void throttleCallback(const std_msgs::Float32ConstPtr& m_t);
    void throttleSliderCallback(const std_msgs::Float32ConstPtr& val); //get throttle slider value [0.0, 255.0] from ui
    void dirCallback(const std_msgs::Int32ConstPtr& dir); //get train direction from ui (enum dir in globals.h)
    void pointCommandCallback(const std_msgs::Int32ConstPtr& pc); //get point to be switched
    void actionCallback(const std_msgs::Int32ConstPtr& action);

private:
    ros::NodeHandle n;

    ros::Subscriber sub_chatter;
    ros::Subscriber sub_throttle_slider;
    ros::Subscriber sub_dir;
    ros::Subscriber sub_point_command;
    ros::Subscriber sub_sound_command;
    ros::Subscriber sub_action;

    ros::Publisher pub_ard_throttle;
    ros::Publisher pub_ard_dir;
    ros::Publisher pub_ard_point_command;

    float man_t_val;
    float throttle1;

    bool new_man_t;
    bool new_dir;
    bool new_action_cmd;

    dirEnum dir_val;
    StateEnum last_action_cmd;

    Loco *current_loco;

    std::map<int, Point*> points_map;

    friend class StateStationDepart;
    friend class StateStationArrive;
    friend class StateCruise;

    friend class LocoCurrent;

    StateMachine *m_sm;

};

#endif //DECISION_NODE_H
