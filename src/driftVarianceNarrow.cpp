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
    double start = 0.5;
    int iterations = 10;
    double nonLin = 1.0;
    int dataPoints = 10;
    int averages = 1;

    double center = 0.3;
    double width = 0.01;

    if (argc != 4)
    {
        std::cout << argc << "\n";
        return -1;
    }

    // Read the non-linearity and the center and width of the distribution from command line arguments
    nonLin = std::atof(argv[1]);
    center = std::atof(argv[2]);
    width = std::atof(argv[3]);

    // Read parameters from the json file
    std::ifstream dataFile("_params.json");
    json params = json::parse(dataFile);

    std::string saveFolder = params["saveFolder"];
    std::string model = params["modelName"];
    iterations = params["iterations"];
    dataPoints = params["dataPoints"];
    averages = params["averages"];

    // Determine the file name based on the model, non-linearity, and the center and width of the distribution
    std::string FileName;
    if (model == "logistic")
    {
        FileName = saveFolder + "logistic-R" + std::to_string(nonLin) + "-C" + std::to_string(center) + "-W" + std::to_string(width) + ".csv";
    } else if (model == "tent")
    {
        FileName = saveFolder + "tent-R" + std::to_string(nonLin) + "-C" + std::to_string(center) + "-W" + std::to_string(width) + ".csv";
    }

    // Compute the observable drift variance and store the results in a csv file
    observableDriftVarianceNarrow(model, nonLin, X, center, width, iterations, averages, dataPoints, FileName);

}
