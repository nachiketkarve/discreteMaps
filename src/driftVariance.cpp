#include "1dMaps.hpp"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

// Define the observable function
double X(double x)
{
    return x;
}

int main(int argc, char *argv[])
{
    // Default parameters
    int iterations = 10;
    double nonLin = 1.0;
    int dataPoints = 10;
    int averages = 1;

    if (argc != 2)
    {
        std::cout << argc << "\n";
        return -1;
    }

    // Read the non-linearity from command line argument
    nonLin = std::atof(argv[1]);

    // Read parameters from the json file
    std::ifstream dataFile("_params.json");
    json params = json::parse(dataFile);

    std::string saveFolder = params["saveFolder"];
    std::string model = params["modelName"];
    iterations = params["iterations"];
    dataPoints = params["dataPoints"];
    averages = params["averages"];

    // Determine the file name based on the model and non-linearity
    std::string FileName;
    if (model == "logistic")
    {
        FileName = saveFolder + "logistic-R" + std::to_string(nonLin) + ".csv";
    } else if (model == "tent")
    {
        FileName = saveFolder + "tent-R" + std::to_string(nonLin) + ".csv";
    } else if (model == "pomMan")
    {
        FileName = saveFolder + "pomMan-R" + std::to_string(nonLin) + ".csv";
    } else if (model == "circRot")
    {
        FileName = saveFolder + "circRot-R" + std::to_string(nonLin) + ".csv";
    }

    // Compute the observable drift variance and store the results in a csv file
    observableDriftVarianceUniform(model, nonLin, X, iterations, averages, dataPoints, FileName);

}