#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <QObject>
#include <QTimer>
#include <std_msgs/Bool.h>
#include <std_msgs/Float32.h>

#include "ros/ros.h"

class Communicator : public QObject {
    Q_OBJECT

public:
    Communicator(QObject *_parent = nullptr);

public slots:
    void reportDirStopClicked();
    void reportDirForwardClicked();
    void reportDirBackwardClicked();
    void reportPoint1ButtonClicked();
    void reportPoint2ButtonClicked();
    void reportShortWhistleClicked();

    void run();

    void handleSpeedChange(double _new_speed);

private:
    ros::NodeHandle *m_ros_node_handle;
    ros::Publisher m_action_publisher;
    ros::Publisher m_twist_publisher;
    ros::Publisher m_translation_emergency_stop_publisher;
    ros::Publisher m_pub_throttle_slider;
    ros::Publisher m_pub_point_command;
    ros::Publisher m_pub_sound_id;

    QTimer *m_emergency_stop_timer = nullptr;

private slots:
    void onTimeout();


};

#endif //COMMUNICATOR_H
