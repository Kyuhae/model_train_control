#include "decision_node.h"

#define PRINT_EXEC_TIME 0

decision::decision() {
    //sub_chatter = n.subscribe("chatter", 1, &decision::throttleCallback, this);
    sub_throttle_slider = n.subscribe("throttle_slider", 1, &decision::throttleSliderCallback, this);
    sub_dir = n.subscribe("dir", 1, &decision::dirCallback, this);
    sub_point_command = n.subscribe("point_command", 1, &decision::pointCommandCallback, this);
    sub_action = n.subscribe("action", 1, &decision::actionCallback, this);

    pub_ard_throttle = n.advertise<std_msgs::UInt8>("ard_throttle", 0);
    pub_ard_dir = n.advertise<std_msgs::UInt8>("ard_dir", 0);
    pub_ard_point_command = n.advertise<std_msgs::Int32>("ard_point_command", 0);




    new_man_t = false;
    new_action_cmd = false;

    //setup points
    Point *p = new Point(POINT_1_PIN, POINT_1_STRAIGHT, POINT_1_TURN, true, pub_ard_point_command );
    points_map[POINT_1_PIN] = p;
    p = new Point(POINT_2_PIN, POINT_2_STRAIGHT, POINT_2_TURN, true, pub_ard_point_command );
    points_map[POINT_2_PIN] = p;


    current_loco = new Loco(this);

    m_sm = new StateMachine(this);


    ROS_INFO(" --- DECISION NODE ---");
    //INFINTE LOOP TO COLLECT LASER DATA AND PROCESS THEM
    ros::Rate r(DECISION_NODE_FREQUENCY);// this node will work at 10hz
    while (ros::ok()) {
        ros::spinOnce();//each callback is called once
        update();
        r.sleep();//we wait if the processing (ie, callback+update) has taken less than 1.0/DECISION_NODE_FREQUENCY
    }
}


//UPDATE: main processing
/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
void decision::update() {
    ROS_INFO("update!");
    //switch state if new action
    if (new_action_cmd) {
        new_action_cmd = false;
        m_sm->switchState(last_action_cmd);
    }


    //run current state
    m_sm->runCurrentState();

    //update throttle values
    std_msgs::UInt8 msg;
    msg.data = int(throttle1);
    pub_ard_throttle.publish(msg);
    ROS_INFO("pub ard_throttle: %d", msg.data);

}// update


void decision::throttleSliderCallback(const std_msgs::Float32ConstPtr &val) {
    ROS_INFO("slider callback %f", val->data);
    m_sm->switchState(STATE_IDLE);
    throttle1 = 255.0*val->data;

}

void decision::dirCallback(const std_msgs::Int32ConstPtr& dir) {
    new_dir = true;
    dir_val = static_cast<dirEnum>(dir->data);
    std_msgs::UInt8 message;
    message.data = dir_val;
    ROS_INFO("pub dir_val %d", dir_val);
    pub_ard_dir.publish(message);
}

void decision::pointCommandCallback(const std_msgs::Int32ConstPtr& point_pin) {
    Point *p = points_map[point_pin->data];
    p->switch_pos();
    ROS_INFO("pub point %d switch", point_pin->data);
}

void decision::actionCallback(const std_msgs::Int32ConstPtr& action) {
    ROS_INFO("received action");
    new_action_cmd = true;
    last_action_cmd = static_cast<StateEnum>(action->data);
}


int main(int argc, char **argv){
    ros::init(argc, argv, "decision");

    decision bsObject;

    ros::spin();

    return 0;
}
