#include <iostream>
#include <algorithm>
#include <vector>

#include "help_functions.h"
using namespace std;

std::vector<float> initialize_priors(int map_size, std::vector<float> landmark_positions,
                                     float position_stdev);

float motion_model(float pseudo_position, float movement, std::vector<float> priors,
                   int map_size, int control_stdev);

int main() {

    //set standard deviation of control:
    float control_stdev = 1.0f;

    //set standard deviation of position:
    float position_stdev = 1.0f;

    //meters vehicle moves per time step
    float movement_per_timestep = 1.0f;

    //number of x positions on map
    int map_size = 25;

    //initialize landmarks
    std::vector<float> landmark_positions {5, 10, 20};

    // initialize priors
    std::vector<float> priors = initialize_priors(map_size, landmark_positions,
                                                  position_stdev);

    //step through each pseudo position x (i)
    for (unsigned int i = 0; i < map_size; ++i) {
        float pseudo_position = float(i);

        //get the motion model probability for each x position
        float motion_prob = motion_model(pseudo_position, movement_per_timestep,
                            priors, map_size, control_stdev);

        //print to stdout
        std::cout << pseudo_position << "\t" << motion_prob << endl;
    }

    return 0;
};

/*
For each x_{t}:
Calculate the transition probability for each potential value x_{t-1}
Calculate the discrete motion model probability by multiplying the transition model probability by the \
belief state (prior) for x_{t-1}
Return total probability (sum) of each discrete probability


*/


//TODO, implement the motion model: calculates prob of being at an estimated position at time t
float motion_model(float pseudo_position, float movement, std::vector<float> priors,
                   int map_size, int control_stdev) {

    //initialize probability
    float position_prob = 0.0f;

    //YOUR CODE HERE

    /*
    Calculating transition for each point
    Use helper norm_pdf function
    static float normpdf(float x, float mu, float std)

    mu is the movement

    priors is the belief

    add to position_prob (summation step)
    */
    float diff_by_movement, ith_motion_prob, next_pseudo_position;

    //step through each next pseudo position x (i)
    for(int i = 0; i<map_size; i++)
    {
        //
        next_pseudo_position = float(i);
        diff_by_movement = pseudo_position - next_pseudo_position;

        //trans_prob * belief
        ith_motion_prob = Helpers::normpdf(diff_by_movement ,movement, control_stdev) * priors[i]; 
        position_prob += ith_motion_prob;

    }

    return position_prob;
}

//initialize priors assumimg vehicle at landmark +/- 1.0 meters position stdev
std::vector<float> initialize_priors(int map_size, std::vector<float> landmark_positions,
                                     float position_stdev) {
//initialize priors assumimg vehicle at landmark +/- 1.0 meters position stdev

    //set all priors to 0.0
    std::vector<float> priors(map_size, 0.0);

    //set each landmark positon +/1 to 1.0/9.0 (9 possible postions)
    float normalization_term = landmark_positions.size() * (position_stdev * 2 + 1);
    for (unsigned int i = 0; i < landmark_positions.size(); i++){
        int landmark_center = landmark_positions[i];
        priors[landmark_center] = 1.0f/normalization_term;
        priors[landmark_center - 1] = 1.0f/normalization_term;
        priors[landmark_center + 1] = 1.0f/normalization_term;
    }
    return priors;
}
