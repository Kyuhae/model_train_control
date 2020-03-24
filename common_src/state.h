#ifndef STATE_H
#define STATE_H



#include "globals.h"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/PoseWithCovariance.h"
#include "geometry_msgs/PoseWithCovarianceStamped.h"
#include "nav_msgs/Path.h"
#include <tf/LinearMath/Matrix3x3.h>
#include <tf/transform_datatypes.h>


class decision;
class StateMachine;

class State {

protected:
    StateMachine *m_state_machine_ptr;
    decision *m_decision_node_ptr;

public:
    State(StateMachine *state_machine_ptr);

    virtual void start(){}
    virtual void end(){}
    virtual void run(){}

    ros::WallTime start_, current_;
    double elapsed;
    double timer;
    Sound snd;
};


class StateIdle : public State {
public:
    using State::State;
    virtual void start();
    virtual void run();
    virtual void end();
    std::string name = "StateIdle";
};

class StateStationDepart : public State {
public:
    using State::State;
    virtual void start();
    virtual void run();
    virtual void end();
    std::string name = "StateStationDepart";
};

class StateStationArrive : public State {
public:
    using State::State;
    virtual void start();
    virtual void run();
    virtual void end();
    std::string name = "StateStationArrive";
};

class StateCruise : public State {
public:
    using State::State;
    virtual void start();
    virtual void run();
    virtual void end();
    std::string name = "StateCruise";
};



#endif // STATE_H
