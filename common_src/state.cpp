#include "state.h"
#include "state_machine.h"
#include "decision_node.h"

State::State(StateMachine *state_machine_ptr) {
    m_state_machine_ptr = state_machine_ptr;
    m_decision_node_ptr = state_machine_ptr->getDecisionNodePtr();
}

void StateIdle::start() {

}

void StateIdle::run() {
    //
}

void StateIdle::end(){

}

void StateStationDepart::start() {
    //system("paplay /home/phil/catkin_ws/src/model_train_control/resources/sound/d51/d51_short_whistle_brake_hiss.flac");
    //play coaling / station announcement sound
    //play long whistle

    snd = m_decision_node_ptr->current_loco->getSound(SND_LONG_WHISTLE);
    std::string s = "paplay " + snd.path;
    system(s.c_str());

    m_decision_node_ptr->throttle1 = m_decision_node_ptr->current_loco->m_start_throttle;
    snd = m_decision_node_ptr->current_loco->getSound(SND_ACCELERATE);
    s = "paplay " + snd.path + " &";
    start_ = ros::WallTime::now();
    system(s.c_str());
}


void StateStationDepart::run() {
    elapsed = (ros::WallTime::now() - start_).toNSec() * 1e-9;

    ROS_INFO("elapsed = %f", elapsed);
    //idea: produce linear mapping between time and throttle?
    int sound_clip_start = 0;
    int sound_clip_end = snd.duration;
    double slope = 1.0 * (m_decision_node_ptr->current_loco->m_cruise_throttle - m_decision_node_ptr->current_loco->m_start_throttle) / (sound_clip_end - sound_clip_start);
    m_decision_node_ptr->throttle1 = m_decision_node_ptr->current_loco->m_start_throttle + round(slope * (elapsed - sound_clip_start));


    if (elapsed > snd.duration) {
        m_state_machine_ptr->switchState(STATE_CRUISE);
    }
}

void StateStationDepart::end(){
    //play alternate whistle
}

// -  -  -   -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -

void StateStationArrive::start() {
    //play station announcement sound
    //play long whistle

    snd = m_decision_node_ptr->current_loco->getSound(SND_LONG_WHISTLE);
    std::string s = "paplay " + snd.path  + " &";
    system(s.c_str());


    snd = m_decision_node_ptr->current_loco->getSound(SND_DECELERATE);
    s = "paplay " + snd.path + " &";
    start_ = ros::WallTime::now();
    system(s.c_str());
}


void StateStationArrive::run() {
    elapsed = (ros::WallTime::now() - start_).toNSec() * 1e-9;
    double remaining = snd.duration - elapsed;
    if (remaining < 0.0) {
        remaining = 0.0;
    }

    ROS_INFO("elapsed = %f", elapsed);

    int sound_clip_start = 0;
    int sound_clip_end = snd.duration;
    double slope = 1.0 * (m_decision_node_ptr->current_loco->m_cruise_throttle - m_decision_node_ptr->current_loco->m_stop_throttle) / (sound_clip_end - sound_clip_start);
    m_decision_node_ptr->throttle1 = m_decision_node_ptr->current_loco->m_stop_throttle + round(slope * (remaining - sound_clip_start));


    if (elapsed > snd.duration) {
        m_state_machine_ptr->switchState(STATE_IDLE);
    }
}

void StateStationArrive::end(){
    //play alternate whistle
}

// -  -  -   -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -

void StateCruise::start() {
    start_ = ros::WallTime::now();
    snd = m_decision_node_ptr->current_loco->getSound(SND_PASS_MED);
    timer = rand()%30+snd.duration;
}


void StateCruise::run() {
    elapsed = (ros::WallTime::now() - start_).toNSec() * 1e-9;

    ROS_INFO("elapsed = %f", elapsed);
    if (elapsed > timer) {
        timer = rand()%30+snd.duration;
        std::string s = "paplay " + snd.path + " &";
        start_ = ros::WallTime::now();
        system(s.c_str());
    }
}

void StateCruise::end(){
    //play alternate whistle
}


// -  -  -   -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
