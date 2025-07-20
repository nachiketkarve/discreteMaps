#include "1dMaps.hpp"

State::State(double position, double nonLinearity, std::string modelName) : x(position), nonLin(nonLinearity), model(modelName)
{
    if (modelName != "logistic" && modelName != "tent")
    {
        throw std::invalid_argument("Invalid Model Name");
    }
}

State::State(const State &s)
{
    x = s.x;
    nonLin = s.nonLin;
    model = s.model;
}

State::State()
{
    x = 0;
    nonLin = 0;
    model = "logistic";
}

void State::Update()
{
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
    }
}

void State::UpdateIters(Vector &Pos)
{
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

void State::xSum(Vector &PosSum, Vector &Slopes)
{
    if(PosSum.size() == 0)
    {
        return;
    }

    PosSum.setZero();
    Slopes.setZero();
    double slope = 0;

    double sumX = 0;
    double sumY = 0;
    double sumXY = 0;
    double sumX2 = 0;
    int n = PosSum.size();

    for(int i = 1; i < n; i++)
    {
        Update();
        PosSum(i) = PosSum(i-1) + x;
        sumX = sumX + i;
        sumX2 = sumX2 + i*i;
        sumY = sumY + PosSum(i);
        sumXY = sumXY + PosSum(i)*i;
        //slope = sumY/sumX;
        slope = ((i+1.0)*sumXY - sumX*sumY)/((i+1.0)*sumX2 - sumX*sumX);
        //slope = sumXY/sumX2;
        Slopes(i) = slope;
    }

    return;
}

void State::x2Sum(Vector &Pos2Sum, Vector &Slopes)
{
    if(Pos2Sum.size() == 0)
    {
        return;
    }

    Pos2Sum.setZero();
    Slopes.setZero();
    double slope = 0;

    double sumX = 0;
    double sumY = 0;
    double sumXY = 0;
    double sumX2 = 0;
    int n = Pos2Sum.size();

    for(int i = 1; i < n; i++)
    {
        Update();
        Pos2Sum(i) = Pos2Sum(i-1) + x*x;
        sumX = sumX + i;
        sumX2 = sumX2 + i*i;
        sumY = sumY + Pos2Sum(i);
        sumXY = sumXY + Pos2Sum(i)*i;
        //slope = sumY/sumX;
        slope = ((i+1.0)*sumXY - sumX*sumY)/((i+1.0)*sumX2 - sumX*sumX);
        //slope = sumXY/sumX2;
        Slopes(i) = slope;
    }

    return;
}