//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Define the State class
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef HEADER_1DMAPS
#define HEADER_1DMAPS

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <complex>
#include "eigenClasses.hpp"


// Define pi
const double pi = 3.14159265358979323846;

// Define a class that stores the state of the system
class State
{
    public:
        // Position of the system
        double x;
        // Non-linearity in the system
        double nonLin;

        // Model name
        std::string model;

        // Class constructor
        State(double position, double nonLinearity, std::string modelName);
        State();

        // Make a copy of a state
        State(const State &s);

        // Update the state of the system under one iteration
        void Update();

        // Perform multiple iterations of the logistic map and store all iterations in the vector Pos
        void UpdateIters(Vector &Pos);

        // Compute cumulative sums of an observable and the slopes of the sums vs iterations
        void observableSum(Vector &obsSum, Vector &Slopes, double (*obs)(double));
};  

// Compute the drift variance of an observable as a function of iterations, averaging over initial conditions uniformly distributed in [0,1]
// Specify the model name, non-linearity, and the observable
// Optionally, specify the number of iterations, number of averages to be taken between the range [0,1], and the number of data points to be stored
// Store the results in a csv file, with the name specified by FileName
void observableDriftVarianceUniform(std::string modelName, double nonLin, double (*obs)(double), int iterations = 100, int averages = 100, int dataPoints = 100, std::string FileName = "./");

// Compute the drift variance of an observable as a function of iterations, averaging over initial conditions in a narrow range [center-width/2, center+width/2]
// Specify the model name, non-linearity, the observable, and the center and width of the range
// Optionally, specify the number of iterations, number of averages to be taken between the range [center-width/2, center+width/2], and the number of data points to be stored
// Store the results in a csv file, with the name specified by FileName
void observableDriftVarianceNarrow(std::string modelName, double nonLin, double (*obs)(double), double center, double width, int iterations = 100, int averages = 100, int dataPoints = 100, std::string FileName = "./");

#endif