#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <complex>
#include "eigenClasses.hpp"

const double pi = 3.141592653589793;

double op(double x,double p){
    return x*p;
}

void standard(double &x, double &p, double K)
{
    p = p + K*std::sin(x);
    x = x + p;
    x = x - std::floor(x/(2.0*pi))*2.0*pi;
    p = p - std::floor(p/(2.0*pi))*2.0*pi;
}

double slope(Vector &X, Vector &Y, int start, int end)
{
    double sumX = 0;
    double sumY = 0;
    double sumX2 = 0;
    double sumXY = 0;

    int n = end - start;

    for (int i = start; i < end; i++)
    {
        sumX = sumX + X(i);
        sumY = sumY + Y(i);
        sumX2 = sumX2 + X(i)*X(i);
        sumXY = sumXY + X(i)*Y(i);
    }

    double slp = (n*sumXY - sumX*sumY)/(n*sumX2 - sumX*sumX);
    return slp;
}

int main(int argc, char *argv[])
{
    int gridSize = 10;
    int Iters = 1000;
    double K = 1.0;

    if (argc != 4)
    {
        std::cout << argc << "\n";
        return -1;
    }

    gridSize = std::atof(argv[1]);
    Iters = std::atof(argv[2]);
    K = std::atof(argv[3]);

    Vector x0s = Eigen::VectorXd::LinSpaced(gridSize, 0.01, 2.0*pi-0.01);
    Vector p0s = Eigen::VectorXd::LinSpaced(gridSize, 0.01, 2.0*pi-0.01);

    Matrix gammas(x0s.size(),p0s.size());
    gammas.setZero();

    for(int i1 = 0; i1 < x0s.size(); i1++)
    {
        for(int i2 = 0; i2 < p0s.size(); i2++)
        {
            double x0 = x0s[i1];
            double p0 = p0s[i2];

            Vector xSum(Iters);
            Vector its = Eigen::VectorXd::LinSpaced(Iters, 1, Iters+1);
            xSum.setZero();

            xSum(0) = op(x0,p0);
            double x = x0;
            double p = p0;

            for(int i = 1; i < Iters; i++)
            {
                standard(x,p,K);
                xSum(i) = xSum(i-1) + op(x,p);
            }

            double slp = slope(its,xSum,1,xSum.size());
            Vector drift(Iters);
            drift = xSum - slp*its;

            double drift2Sum = 0;
            double driftSum = 0;
            Vector vars(Iters);
            for(int i = 0; i < Iters; i++)
            {
                drift2Sum = drift2Sum + drift(i)*drift(i);
                driftSum = driftSum + drift(i);
                vars(i) = drift2Sum/(i+1) - (driftSum/(i+1))*(driftSum/(i+1));
            }

            double varSum = 0;
            Vector varsAvg(Iters);
            for(int i = 0; i < Iters; i++)
            {
                varSum = varSum + vars(i);
                varsAvg(i) = varSum/(i+1);
            }

            Vector varsAvgLog(Iters);
            Vector itsLog(Iters);

            for(int i = 0; i < Iters; i++)
            {
                varsAvgLog(i) = std::log(varsAvg(i));
                itsLog(i) = std::log(its(i));
            }

            gammas(i1,i2) = slope(itsLog,varsAvgLog,std::round(0.9*Iters),Iters);
        }
    }

    std::string FileName;
    FileName = "stdPhase-K" + std::to_string(K) + ".csv";
    std::ofstream file;
    file.open(FileName);
    file << std::setprecision(15);

    for(int i1 = 0; i1 < gridSize; i1++)
    {
        for(int i2 = 0; i2 < gridSize; i2++)
        {
            file << gammas(i2,i1);
            if(i2 < gridSize - 1)
            {
                file << ",";
            }
        }
        file << "\n";
    }

    file.close();

    return 0;
}
