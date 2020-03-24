#include "state_machine.h"
#include "state.h"
#include "decision_node.h"

StateMachine::StateMachine(decision* d)
{
    m_decision_node_ptr = d;
    m_state_mapping[STATE_STATION_DEPART] = new StateStationDepart(this);
    m_state_mapping[STATE_IDLE] = new StateIdle(this);
    m_state_mapping[STATE_STATION_ARRIVE] = new StateStationArrive(this);
    m_state_mapping[STATE_CRUISE] = new StateCruise(this);
}

void StateMachine::switchState(const StateEnum &new_state)
{
    m_new_state = new_state;
    m_state_mapping[m_state]->end();
    m_state = m_new_state;
    m_state_mapping[m_state]->start();
}

decision *StateMachine::getDecisionNodePtr()
{
    return m_decision_node_ptr;
}

StateEnum StateMachine::getNewState()
{
    return m_new_state;
}

void StateMachine::runCurrentState()
{
    if (m_state_mapping.find(m_state) == m_state_mapping.end()) {
        std::cout << "[STATE_MACHINE] NO CORRESPONDING STATE FOUND for " << (int)m_state << std::endl;
        exit(0);
    }
    if (m_first_run) {
        m_state_mapping[m_state]->start();
        m_first_run = false;
    }
    ROS_INFO("[STATE_MACHINE] running  %d", m_state);
    m_state_mapping[m_state]->run();
}
