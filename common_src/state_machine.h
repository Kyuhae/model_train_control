#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H
#include <map>
#include "state.h"

class decision;
class State;

class StateMachine {
public:
    StateMachine(decision *d);
    void switchState(const StateEnum& new_state);
    void runCurrentState();

    //GETTERS
    decision *getDecisionNodePtr();
    StateEnum getNewState();

    nav_msgs::Path wp_msg;

private:
    std::map<StateEnum, State*> m_state_mapping;
    StateEnum m_state = STATE_IDLE;
    StateEnum m_new_state = STATE_IDLE;
    decision *m_decision_node_ptr;
    bool m_first_run = true;

};

#endif //STATE_MACHINE_H
