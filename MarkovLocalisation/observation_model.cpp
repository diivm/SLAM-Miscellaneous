#include <iostream>
#include <algorithm>
#include <vector>

#include "help_functions.h"
using namespace std;

//function to get pseudo ranges
std::vector<float> pseudo_range_estimator(std::vector<float> landmark_positions, 
                                          float pseudo_position);

//observation model: calculates likelihood prob term based on landmark proximity
float observation_model(std::vector<float> landmark_positions, std::vector<float> observations, 
                        std::vector<float> pseudo_ranges, float distance_max, 
                        float observation_stdev);


int main() {  

    //set observation standard deviation:
    float observation_stdev = 1.0f;

    //number of x positions on map
    int map_size = 25;

    //set distance max
    float distance_max = map_size;

    //define landmarks
    std::vector<float> landmark_positions {5, 10, 12, 20};

    //define observations
    std::vector<float> observations {5.5, 13, 15};

    //step through each pseudo position x (i)
    for (unsigned int i = 0; i < map_size; ++i) {
        float pseudo_position = float(i);

        //get pseudo ranges
        std::vector<float> pseudo_ranges = pseudo_range_estimator(landmark_positions, 
                                                                  pseudo_position);

        //get observation probability
        float observation_prob = observation_model(landmark_positions, observations, 
                                                   pseudo_ranges, distance_max, 
                                                   observation_stdev);

        //print to stdout
        std::cout << observation_prob << endl; 
    }      

    return 0;
};

/*
Observation_Model
For each observation:
determine if a pseudo range vector exists for the current pseudo position x
if the vector exists, extract and store the minimum distance, element 0 of the sorted vector, and remove that element (so we don't re-use it). This will be passed to norm_pdf
if the pseudo range vector does not exist, pass the maximum distance to norm_pdf
use norm_pdf to determine the observation model probability
return the total probability Return the product of all probabilities
*/



//TODO Complete the observation model function
//calculates likelihood prob term based on landmark proximity
float observation_model(std::vector<float> landmark_positions, std::vector<float> observations, 
                        std::vector<float> pseudo_ranges, float distance_max,
                        float observation_stdev) {

    float distance_prob=1.0f;
    //YOUR CODE HERE
    for(int i= 0; i< observations.size(); i++)
    {
    	float min_dist;
    	if(!pseudo_ranges.empty()) 
    	{
    		min_dist=pseudo_ranges[0];
    		pseudo_ranges.erase(pseudo_ranges.begin());
    		//	static float normpdf(float x, float mu, float std)
    		distance_prob*=Helpers::normpdf(observations[i], min_dist, observation_stdev);
    	}
    	else
    	{
    		//can use distance_max or infinity 
    		distance_prob*=Helpers::normpdf(observations[i], std::numeric_limits<const float>::infinity(), observation_stdev);
    	}
    }    
    return distance_prob;
}

/*
Pseudo_range_estimator
For each landmark position:
determine the distance between each pseudo position x and each landmark position
if the distance is positive (landmark is forward of the pseudo position) push the distance to the pseudo range vector
sort the pseudo range vector in ascending order
return the pseudo range vector

*/

//TODO: Complete pseudo range estimator function
std::vector<float> pseudo_range_estimator(std::vector<float> landmark_positions, float pseudo_position) {
    
    //define pseudo observation vector:
    std::vector<float> pseudo_ranges;
            
    //loop over number of landmarks and estimate pseudo ranges:
        //YOUR CODE HERE
    for(int i=0; i<landmark_positions.size(); i++)
    {
    	if(landmark_positions[i]-pseudo_position<=0) continue;
    	else
    	{
    		pseudo_ranges.push_back(landmark_positions[i]-pseudo_position);
    	}
    }
    sort(pseudo_ranges.begin(), pseudo_ranges.end());

    //sort pseudo range vector:
        //YOUR CODE HERE
    
    return pseudo_ranges;
}