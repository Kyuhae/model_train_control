#include "communicator.h"
#include "std_msgs/Int32.h"

#include <QEventLoop>

#include <geometry_msgs/Twist.h>
#include "globals.h"

extern bool buffer;

Communicator::Communicator(QObject *_parent):
    QObject(_parent)
{
    
}


void Communicator::reportDirStopClicked() {
    ROS_INFO("REPORT dirStop Clicked");
    std_msgs::Int32 message;
    message.data = static_cast<int>(DIR_STOP);
    m_action_publisher.publish(message);
}

void Communicator::reportDirForwardClicked() {
    ROS_INFO("REPORT dirForward Clicked");
    std_msgs::Int32 message;
    message.data = static_cast<int>(DIR_FORWARD);
    m_action_publisher.publish(message);
}

void Communicator::reportDirBackwardClicked() {
    ROS_INFO("REPORT dirBackward Clicked");
    std_msgs::Int32 message;
    message.data = static_cast<int>(DIR_BACKWARD);
    m_action_publisher.publish(message);
}

void Communicator::reportPoint1ButtonClicked() {
    ROS_INFO("REPORT Point1ButtonClicked");
    std_msgs::Int32 point_pin;
    point_pin.data = static_cast<int>(POINT_1_PIN);
    m_pub_point_command.publish(point_pin);
}

void Communicator::reportPoint2ButtonClicked() {
    ROS_INFO("REPORT Point2ButtonClicked");
    std_msgs::Int32 point_pin;
    point_pin.data = static_cast<int>(POINT_2_PIN);
    m_pub_point_command.publish(point_pin);
}

void Communicator::reportShortWhistleClicked() {
    ROS_INFO("reportShortWhistleClicked");
    std_msgs::Int32 sound_clip_id;
    sound_clip_id.data = static_cast<int>(SND_SHORT_WHISTLE);
    m_pub_sound_id.publish(sound_clip_id);
}

void Communicator::reportStationDepartClicked() {
    std_msgs::Int32 state;
    state.data = static_cast<int>(STATE_STATION_DEPART);
    m_pub_action.publish(state);
}

void Communicator::reportStationArriveClicked() {
    std_msgs::Int32 state;
    state.data = static_cast<int>(STATE_STATION_ARRIVE);
    m_pub_action.publish(state);
}

void Communicator::run() {
    m_ros_node_handle = new ros::NodeHandle();
    m_action_publisher = m_ros_node_handle->advertise<std_msgs::Int32>("dir", 1);
    m_pub_throttle_slider = m_ros_node_handle->advertise<std_msgs::Float32>("throttle_slider", 1);
    m_pub_point_command = m_ros_node_handle->advertise<std_msgs::Int32>("point_command", 1);
    m_pub_sound_id = m_ros_node_handle->advertise<std_msgs::Int32>("sound_id", 1);
    m_pub_action = m_ros_node_handle->advertise<std_msgs::Int32>("action", 1);

    m_emergency_stop_timer = new QTimer();
    m_emergency_stop_timer->setInterval(20);
    connect(m_emergency_stop_timer, &QTimer::timeout, this, &Communicator::onTimeout);
    ROS_INFO("- - MTC UI RUNNING - -");

    QEventLoop wait;
    wait.exec();
    
}

void Communicator::handleSpeedChange(double _new_speed)
{
    ROS_INFO("REPORT handleSpeedChange");
    std_msgs::Float32 message;
    message.data = static_cast<float>(_new_speed);
    m_pub_throttle_slider.publish(message);
}

void Communicator::onTimeout() {
    geometry_msgs::Twist mvt;
    mvt.linear.x = 0;
    mvt.linear.y = 0;
    mvt.linear.z = 0;
    mvt.angular.x = 0;
    mvt.angular.y = 0;
    mvt.angular.z = 0;

    m_twist_publisher.publish(mvt); // spam motors with 0
}
