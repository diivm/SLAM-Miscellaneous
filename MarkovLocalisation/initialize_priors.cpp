#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

//initialize priors assumimg vehicle at landmark +/- 1.0 meters position stdev
std::vector<float> initialize_priors(int map_size, std::vector<float> landmark_positions,
                                     float position_stdev);

int main() {

    //set standard deviation of position:
    float position_stdev = 1.0f;

    //set map horizon distance in meters 
    int map_size = 25;

    //initialize landmarks
    std::vector<float> landmark_positions {5, 10, 20};

    // initialize priors
    std::vector<float> priors = initialize_priors(map_size, landmark_positions,
                                                  position_stdev);
    
    //print values to stdout 
    for (unsigned int p = 0; p < priors.size(); p++) {
        std::cout << p << " ";
        std::cout << priors[p] << endl;
    }
        
    return 0;

};

// considering non circular world
//TODO: Complete the initialize_priors function
std::vector<float> initialize_priors(int map_size, std::vector<float> landmark_positions,
                                     float position_stdev) {

//initialize priors assumimg vehicle at landmark +/- 1.0 meters position stdev

    //set all priors to 0.0
    std::vector<float> priors(map_size, 0.0);
    
    float set_value = 1/( landmark_positions.size()*(2*position_stdev + 1) );
    int position_stdev_int=int(position_stdev);

    //YOUR CODE HERE
    for(int i =0; i<landmark_positions.size(); i++)
    {
        priors[landmark_positions[i]] = set_value;

        for(int j=0;j<=position_stdev_int;j++)
        {    
            // for standard deviation  
            if(landmark_positions[i]==0)
            {
                //priors[landmark_positions[i]+position_stdev_int+j] = set_value;
                priors[landmark_positions[i]+j] = set_value;
            }
            else if(landmark_positions[i]==map_size)
            {
                //priors[landmark_positions[i]-position_stdev_int-j] = set_value;     
                priors[landmark_positions[i]-j] = set_value;     

            }   
            else
            {
                //priors[landmark_positions[i]-position_stdev_int-j] = set_value;
                //priors[landmark_positions[i]+position_stdev_int+j] = set_value;
                priors[landmark_positions[i]-j] = set_value;
                priors[landmark_positions[i]+j] = set_value;     
            }
        }               
    }

    return priors;
}