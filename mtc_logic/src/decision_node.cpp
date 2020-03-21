#include "decision_node.h"

#define PRINT_EXEC_TIME 0

decision::decision() {
    //sub_chatter = n.subscribe("chatter", 1, &decision::throttleCallback, this);
    sub_throttle_slider = n.subscribe("throttle_slider", 1, &decision::throttleSliderCallback, this);
    sub_dir = n.subscribe("dir", 1, &decision::dirCallback, this);
    sub_point_command = n.subscribe("point_command", 1, &decision::pointCommandCallback, this);

    pub_ard_throttle = n.advertise<std_msgs::UInt8>("ard_throttle", 0);
    pub_ard_dir = n.advertise<std_msgs::UInt8>("ard_dir", 0);
    pub_ard_point_command = n.advertise<std_msgs::Int32>("ard_point_command", 0);




    new_man_t = false;

    //setup points
    Point *p = new Point(POINT_1_PIN, POINT_1_STRAIGHT, POINT_1_TURN, true, pub_ard_point_command );
    points_map[POINT_1_PIN] = p;
    p = new Point(POINT_2_PIN, POINT_2_STRAIGHT, POINT_2_TURN, true, pub_ard_point_command );
    points_map[POINT_2_PIN] = p;

#if PRINT_DEBUG_DECISION_STEPS
    ROS_INFO("End of Constructor");
#endif

    //INFINTE LOOP TO COLLECT LASER DATA AND PROCESS THEM
    ros::Rate r(DECISION_NODE_FREQUENCY);// this node will work at 10hz
    while (ros::ok()) {
#if PRINT_EXEC_TIME
        start_ = ros::WallTime::now();
#endif

        ros::spinOnce();//each callback is called once
        update();

#if PRINT_EXEC_TIME
        end_ = ros::WallTime::now();
        double execution_time = (end_ - start_).toNSec() * 1e-6;

        if (execution_time > (1000.0 * 1.0/DECISION_NODE_FREQUENCY)) {
            ROS_WARN_STREAM("[TOO SLOW] Exectution time (ms): " << execution_time);
        }
        else {
            ROS_INFO_STREAM("[OK] Exectution time (ms): " << execution_time);
        }
#endif
        r.sleep();//we wait if the processing (ie, callback+update) has taken less than 1.0/DECISION_NODE_FREQUENCY
    }
}


//UPDATE: main processing
/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
void decision::update() {


}// update


void decision::throttleSliderCallback(const std_msgs::Float32ConstPtr &val) {
    ROS_INFO("slider callback %f", val->data);
    std_msgs::UInt8 message;
    message.data = int(val->data * 255.0);
    ROS_INFO("pub man_throttle: %d", message.data);
    pub_ard_throttle.publish(message);
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


int main(int argc, char **argv){
    ros::init(argc, argv, "decision");

    decision bsObject;

    ros::spin();

    return 0;
}
