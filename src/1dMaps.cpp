#include "1dMaps.hpp"

State::State(double position, double nonLinearity, std::string modelName) : x(position), nonLin(nonLinearity), model(modelName)
{
    // Check for valid model names
    if (modelName != "logistic" && modelName != "tent" && modelName != "pomMan" && modelName != "circRot")
    {
        throw std::invalid_argument("Invalid Model Name");
    }
}

State::State(const State &s)
{
    // Copy state variables
    x = s.x;
    nonLin = s.nonLin;
    model = s.model;
}

State::State()
{
    // Default constructor
    x = 0;
    nonLin = 0;
    model = "logistic";
}

void State::Update()
{
    // Update the state of the system under one iteration
    if (model == "logistic")
    {
        x = nonLin*x*(1.0-x);
    }
    else if (model == "tent")
    {
        if (x < 0.5)
            x = nonLin*x;
        else
            x = nonLin*(1.0-x);
    } else if (model == "pomMan")
    {
        x = std::fmod(x + std::pow(x,nonLin),1.0);
    } else if (model == "circRot")
    {
        x = std::fmod(x + nonLin, 2.0*pi);
    }
}

void State::UpdateIters(Vector &Pos)
{
    // Perform multiple iterations and store all iterations in the vector Pos
    Pos.setZero();
    if(Pos.size() == 0)
    {
        return;
    }

    for (int i = 0; i < Pos.size(); i++)
    {
        Pos(i) = x;
        Update();
    }
}

void State::observableSum(Vector &obsSum, Vector &Slopes, double (*obs)(double))
{
    if(obsSum.size() == 0 || obsSum.size() != Slopes.size())
    {
        return;
    }

    // Initialize variables for performing a simple linear regression
    double slope = 0; // stores the slope of the linear regression
    double sumX = 0; // stores the sum of indices
    double sumY = 0; // stores the sum of the cumulative observable sums
    double sumXY = 0; // stores the sum of the product of indices and cumulative observable sums
    double sumX2 = 0; // stores the sum of the squares of indices
    int n = obsSum.size(); // number of iterations

    // Always start with zero
    obsSum(0) = 0;
    Slopes(0) = 0;

    for(int i = 1; i < n; i++)
    {
        
        obsSum(i) = obsSum(i-1) + obs(x);
        sumX = sumX + i;
        sumX2 = sumX2 + i*i;
        sumY = sumY + obsSum(i);
        sumXY = sumXY + obsSum(i)*i;
        slope = ((i+1.0)*sumXY - sumX*sumY)/((i+1.0)*sumX2 - sumX*sumX); // linear regression formula for slope
        Slopes(i) = slope;
        Update();
    }
}

void observableDriftVarianceUniform(std::string modelName, double nonLin, double (*obs)(double), int iterations, int averages, int dataPoints, std::string FileName)
{
    // Make sure the number of data points to be stored is not larger than the number of iterations
    if (dataPoints > iterations)
    {
        dataPoints = iterations;
    }

    // Number of iterations to skip while storing the data
    int iStep = int(iterations/dataPoints);

    // Create vectors to store the iterations and the average drift variances
    Vector iters(dataPoints);
    Vector variancesAvg(dataPoints);

    iters.setZero();
    variancesAvg.setZero();
    for(int i = 1; i < dataPoints; i++)
    {
        iters(i) = i*iStep;
    }

    for(int average = 0; average < averages; average++)
    {
    
        // Choose an initial condition for the state
        // The initial condition is chosen uniformly from the interval [0, 1]
        double start = double(average)/double(averages);

        // Create vectors to store the cumulative observable sums, slopes, and time
        Vector obsSum(iterations);
        Vector Slopes(iterations);
        Vector Time(iterations);

        for(int i = 0; i < Time.size(); i++)
        {
            Time(i) = i;
        }

        // Create a state object with the initial condition and model parameters
        State s(start, nonLin, modelName);
        // Compute the cumulative observable sums and slopes
        s.observableSum(obsSum, Slopes, obs);

        // Create a vector to store the drift variances
        Vector variances(dataPoints);

        variances.setZero();

        for(int i = 1; i < dataPoints; i++)
        {
            // Create a vector to store the drift for the current number of iterations
            Vector drift(i*iStep);
            // Compute the mean drift and mean drift squared
            double meanDrift = 0;
            double meanDrift2 = 0;
            for(int j = 0; j < drift.size(); j++)
            {
                // Compute the drift as the difference between the cumulative observable sum and the linear fit
                drift(j) = obsSum(j) - Slopes(i*iStep)*(Time(j));
                meanDrift = meanDrift + drift(j)/(i*iStep);
                meanDrift2 = meanDrift2 + drift(j)*drift(j)/(i*iStep);
            }
            // Compute the variance of this drift
            variances(i) = meanDrift2 - meanDrift*meanDrift;
        }
        // Add this variance to the average variances
        variancesAvg = variancesAvg + variances/averages;
    }

    // Store the data in a CSV file
    std::ofstream file;
    file.open(FileName);
    file << std::setprecision(15);
    file << "Iters" << "," << "Variance";
    for (int i = 0; i < variancesAvg.size(); i++)
    {
        file << "\n" << iters(i) << "," << variancesAvg(i);
    }
    file.close();
}


void observableDriftVarianceNarrow(std::string modelName, double nonLin, double (*obs)(double), double center, double width, int iterations, int averages, int dataPoints, std::string FileName)
{
    // Make sure the number of data points to be stored is not larger than the number of iterations
    if (dataPoints > iterations)
    {
        dataPoints = iterations;
    }

    // Number of iterations to skip while storing the data
    int iStep = int(iterations/dataPoints);

    // Determine the range of initial conditions to be sampled
    double xmin = center-width/2.0;
    double xmax = center+width/2.0;
    if (xmin < 0.0)
    {
        xmin = 0.0;
    }
    if (xmax > 1.0)
    {
        xmax = 1.0;
    }

    // Create vectors to store the iterations and the average drift variances
    Vector iters(dataPoints);
    Vector variancesAvg(dataPoints);

    iters.setZero();
    variancesAvg.setZero();
    for(int i = 1; i < dataPoints; i++)
    {
        iters(i) = i*iStep;
    }

    for(int average = 0; average < averages; average++)
    {
    
        // Choose an initial condition for the state
        // The initial condition is chosen uniformly from the interval [xmin, xmax]
        double start = xmin + (xmax-xmin)*double(average)/double(averages);

        // Create vectors to store the cumulative observable sums, slopes, and time
        Vector obsSum(iterations);
        Vector Slopes(iterations);
        Vector Time(iterations);

        for(int i = 0; i < Time.size(); i++)
        {
            Time(i) = i;
        }

        // Create a state object with the initial condition and model parameters
        State s(start, nonLin, modelName);
        // Compute the cumulative observable sums and slopes
        s.observableSum(obsSum, Slopes, obs);

        // Create a vector to store the drift variances
        Vector variances(dataPoints);

        variances.setZero();

        for(int i = 1; i < dataPoints; i++)
        {
            // Create a vector to store the drift for the current number of iterations
            Vector drift(i*iStep);
            // Compute the mean drift and mean drift squared
            double meanDrift = 0;
            double meanDrift2 = 0;
            for(int j = 0; j < drift.size(); j++)
            {
                // Compute the drift as the difference between the cumulative observable sum and the linear fit
                drift(j) = obsSum(j) - Slopes(i*iStep)*(Time(j));
                meanDrift = meanDrift + drift(j)/(i*iStep);
                meanDrift2 = meanDrift2 + drift(j)*drift(j)/(i*iStep);
            }
            // Compute the variance of this drift
            variances(i) = meanDrift2 - meanDrift*meanDrift;
        }
        // Add this variance to the average variances
        variancesAvg = variancesAvg + variances/averages;
    }

    // Store the data in a CSV file
    std::ofstream file;
    file.open(FileName);
    file << std::setprecision(15);
    file << "Iters" << "," << "Variance";
    for (int i = 0; i < variancesAvg.size(); i++)
    {
        file << "\n" << iters(i) << "," << variancesAvg(i);
    }
    file.close();
}

