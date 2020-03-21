#ifndef POINT_H
#define POINT_H

#include "ros/ros.h"
#include "geometry_msgs/Point.h"
#include "std_msgs/Int32.h"


class Point
{
  public:
    Point(int pin, int straight, int turn, bool bstraight, ros::Publisher pub_pc);

    void switch_pos();

  private:
    int m_pin;
    int m_straight_pos;
    int m_turn_pos;
    bool m_bstraight;
    ros::Publisher m_pub_pc;

};

#endif // POINT_H
