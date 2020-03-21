#include "point.h"

Point::Point(int pin, int straight, int turn, bool bstraight, ros::Publisher pub_pc)
{
    m_pin = pin;
    m_straight_pos = straight;
    m_turn_pos = turn;
    m_bstraight = bstraight;
    m_pub_pc = pub_pc;
}

void Point::switch_pos () {
    m_bstraight = !m_bstraight;
    int pos = m_bstraight ? m_straight_pos : m_turn_pos;
    std_msgs::Int32 pc;
    pc.data = m_pin * 1000 + pos; //encoding into a single int since geometry_msgs doesn't seem to work...
    m_pub_pc.publish(pc);
}
