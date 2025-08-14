#include "1dMaps.hpp"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

double X2(double x)
{
    return x*x;
}

int main(int argc, char *argv[])
{
    double start = 0.5;
    int iterations = 10;
    double nonLin = 1.0;
    int dataPoints = 10;
    int averages = 1;

    if (argc != 2)
    {
        std::cout << argc << "\n";
        return -1;
    }

    nonLin = std::atof(argv[1]);

    std::ifstream dataFile("_params.json");
    json params = json::parse(dataFile);

    std::string saveFolder = params["saveFolder"];
    std::string model = params["modelName"];
    iterations = params["iterations"];
    dataPoints = params["dataPoints"];
    averages = params["averages"];

    std::string FileName;
    if (model == "logistic")
    {
        FileName = saveFolder + "x2logistic-R" + std::to_string(nonLin) + ".csv";
    } else if (model == "tent")
    {
        FileName = saveFolder + "x2tent-R" + std::to_string(nonLin) + ".csv";
    } else if (model == "pomMan")
    {
        FileName = saveFolder + "x2pomMan-R" + std::to_string(nonLin) + ".csv";
    } else if (model == "circRot")
    {
        FileName = saveFolder + "x2circRot-R" + std::to_string(nonLin) + ".csv";
    }

    observableDriftVarianceUniform(model, nonLin, X2, iterations, averages, dataPoints, FileName);

}