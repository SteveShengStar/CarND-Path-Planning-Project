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

        State(LongitudinalState long_state, LateralState lat_state, int current_lane, int next_lane) {
            this->long_state = long_state;
            this->lat_state = lat_state;
            this->current_lane = current_lane;
        }
};


class StateMachine {
    public:
        State current_state;

        StateMachine() {
            current_state = State(LongitudinalState::MAINTAIN_COURSE, LateralState::STAY_IN_LANE, 1);
        }

        StateMachine(LongitudinalState long_state, LateralState lat_state, int current_lane) {
            current_state = State(long_state, lat_state, current_lane);
        }

        State updateLateralState(LateralState new_lateral_state) {
            // LongitudinalState long_state;       
            // LateralState lat_state;  
            // int current_lane;

            current_state.lat_state = new_lateral_state;

            switch (current_state)
            {
                case LateralState::PREPARE_CHANGE_LANE_LEFT:
                    if (new_lateral_state == LateralState::STAY_IN_LANE) {
                        current_lane = current_lane;
                    } else if (new_lateral_state == LateralState::CHANGE_LANE_LEFT) {
                        current_lane -= 1;
                    }
                    break;
                case LateralState::PREPARE_CHANGE_LANE_RIGHT:
                    if (new_lateral_state == LateralState::STAY_IN_LANE) {
                        current_lane = current_lane;
                    } else if (new_lateral_state == LateralState::CHANGE_LANE_RIGHT) {
                        current_lane += 1;
                    }
                    break;
            }
            return current_state;
        }

        State updateLongState(LateralState new_long_state) {
            // ACCELERATE = 0,
            // DECELERATE = 1,
            // MAINTAIN_COURSE = 2,
            // STOP = 3

            current_state.long_state = new_long_state;
            return current_state;
        }
};