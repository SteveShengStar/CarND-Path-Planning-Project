#include <vector>

using std::vector;

enum LongitudinalState
{
    ACCELERATE = 0,
    DECELERATE = 1,
    MAINTAIN_COURSE = 2,
    STOP = 3
};
enum LateralState
{
    STAY_IN_LANE = 0,
    PREPARE_CHANGE_LANE_LEFT = 1,
    PREPARE_CHANGE_LANE_RIGHT = 2,
    CHANGE_LANE_LEFT = 3,
    CHANGE_LANE_RIGHT = 4
};

class State {   
    public:
        LongitudinalState long_state;       
        LateralState lat_state;  
        int current_lane;
        int future_lane;

        State(LongitudinalState long_state, LateralState lat_state, int current_lane, int future_lane) {
            this->long_state = long_state;
            this->lat_state = lat_state;
            this->current_lane = current_lane;
            this->future_lane = future_lane;
        }
};


class StateMachine {
    public:
        State* current_state;

        StateMachine() {
            current_state = new State(LongitudinalState::MAINTAIN_COURSE, LateralState::STAY_IN_LANE, 1, 1);
        }

        StateMachine(LongitudinalState long_state, LateralState lat_state, int current_lane, int future_lane) {
            current_state = new State(long_state, lat_state, current_lane, future_lane);
        }

        vector<State> nextPossibleStates() {
            vector<State> future_states;
            LateralState anticipLateralState;
            LongitudinalState anticipLongState;
            
            switch (this->current_state->lat_state)
            {
            case LateralState::STAY_IN_LANE:
                future_states.push_back(State(LongitudinalState::MAINTAIN_COURSE,
                                            LateralState::STAY_IN_LANE,
                                            this->current_state->current_lane,
                                            this->current_state->current_lane));
                future_states.push_back(State(LongitudinalState::ACCELERATE,
                                            LateralState::STAY_IN_LANE,
                                            this->current_state->current_lane,
                                            this->current_state->current_lane));
                future_states.push_back(State(LongitudinalState::DECELERATE,
                                            LateralState::STAY_IN_LANE,
                                            this->current_state->current_lane,
                                            this->current_state->current_lane));        

                future_states.push_back(State(LongitudinalState::MAINTAIN_COURSE,
                                            LateralState::PREPARE_CHANGE_LANE_LEFT,
                                            this->current_state->current_lane,
                                            this->current_state->current_lane - 1));
                future_states.push_back(State(LongitudinalState::ACCELERATE,
                                            LateralState::PREPARE_CHANGE_LANE_LEFT,
                                            this->current_state->current_lane,
                                            this->current_state->current_lane - 1));
                future_states.push_back(State(LongitudinalState::DECELERATE,
                                            LateralState::PREPARE_CHANGE_LANE_LEFT,
                                            this->current_state->current_lane,
                                            this->current_state->current_lane - 1));

                future_states.push_back(State(LongitudinalState::MAINTAIN_COURSE,
                                            LateralState::PREPARE_CHANGE_LANE_RIGHT,
                                            this->current_state->current_lane,
                                            this->current_state->current_lane + 1));
                future_states.push_back(State(LongitudinalState::ACCELERATE,
                                            LateralState::PREPARE_CHANGE_LANE_RIGHT,
                                            this->current_state->current_lane,
                                            this->current_state->current_lane + 1));
                future_states.push_back(State(LongitudinalState::DECELERATE,
                                            LateralState::PREPARE_CHANGE_LANE_RIGHT,
                                            this->current_state->current_lane,
                                            this->current_state->current_lane + 1));

                break;
            case LateralState::PREPARE_CHANGE_LANE_LEFT:

                if (anticipLateralState == LateralState::CHANGE_LANE_LEFT) {
                    future_states.push_back(State(LongitudinalState::MAINTAIN_COURSE,
                                                LateralState::CHANGE_LANE_LEFT,
                                                this->current_state->future_lane,
                                                this->current_state->future_lane));
                }
                 else if (anticipLateralState == LateralState::STAY_IN_LANE) {
                    if (anticipLongState == LongitudinalState::MAINTAIN_COURSE) {

                        future_states.push_back(State(LongitudinalState::MAINTAIN_COURSE,
                                                LateralState::STAY_IN_LANE,
                                                this->current_state->current_lane,
                                                this->current_state->current_lane));
                    } 
                    else if (anticipLongState == LongitudinalState::DECELERATE) {
                        
                        future_states.push_back(State(LongitudinalState::DECELERATE,
                                                LateralState::STAY_IN_LANE,
                                                this->current_state->current_lane,
                                                this->current_state->current_lane));
                    }
                }
                break;

            case LateralState::PREPARE_CHANGE_LANE_RIGHT:
                if (anticipLateralState == LateralState::CHANGE_LANE_RIGHT) {
                    future_states.push_back(State(LongitudinalState::MAINTAIN_COURSE,
                                                LateralState::CHANGE_LANE_RIGHT,
                                                this->current_state->future_lane,
                                                this->current_state->future_lane));
                }
                future_states.push_back(State(LongitudinalState::MAINTAIN_COURSE,
                                            LateralState::STAY_IN_LANE,
                                            this->current_state->current_lane,
                                            this->current_state->current_lane));
                future_states.push_back(State(LongitudinalState::DECELERATE,
                                            LateralState::STAY_IN_LANE,
                                            this->current_state->current_lane,
                                            this->current_state->current_lane));
                break;

            default:       
                future_states.push_back(State(LongitudinalState::MAINTAIN_COURSE,
                                            LateralState::STAY_IN_LANE,
                                            this->current_state->current_lane,
                                            this->current_state->current_lane));       
            }
            return future_states;
        }
};