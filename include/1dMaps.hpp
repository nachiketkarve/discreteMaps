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

        // Perform multiple iterations of the logistic map and store cumulative sums of x in the vector PosSum
        // Return the slopes of PosSum vs iterations
        void xSum(Vector &PosSum, Vector &Slopes);

        // Perform multiple iterations of the logistic map and store cumulative sums of x^2 in the vector PosSum
        // Return the slopes of PosSum vs iterations
        void x2Sum(Vector &Pos2Sum, Vector &Slopes);
};  

#endif