#include "1dMaps.hpp"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

int main(int argc, char *argv[])
{
    int points = 100;
    double nonLin = 2.5;
    std::string modelName = "logistic";
    int maxIters = 10;
    int dataPoints = 5;
    int nbins = 20;

    if (argc != 2)
    {
        std::cout << argc << "\n";
        return -1;
    }
    nonLin = std::atof(argv[1]);

    std::ifstream dataFile("_params.json");
    json params = json::parse(dataFile);

    std::string saveFolder = params["saveFolder"];
    modelName = params["modelName"];
    maxIters = params["iterations"];
    dataPoints = params["dataPoints"];
    points = params["averages"];
    nbins = params["bins"];

    Vector bins(nbins);
    bins.setZero();
    int step = std::max(int(maxIters/dataPoints),1);
    int maxStep = int(maxIters/step);

    State xs[points];
    for(int i = 0; i < points; i++)
    {
        xs[i].x = float(i)/float(points);
        xs[i].nonLin = nonLin;
        xs[i].model = modelName;
    }

    std::string FileName;
    if (modelName == "logistic")
    {
        FileName = saveFolder + "logisticDensity-R" + std::to_string(nonLin) + ".csv";
    } else if (modelName == "tent")
    {
        FileName = saveFolder + "tentDensity-R" + std::to_string(nonLin) + ".csv";
    }
    std::ofstream file;
    file.open(FileName);
    file << std::setprecision(15);

    for(int iters = 0; iters < maxIters; iters++)
    {
        for(int i = 0; i < points; i++)
        {
            int npos = std::min(int(xs[i].x * nbins),nbins-1);
            bins(npos) = bins(npos) + 1.0;
            xs[i].Update();
        }

        if (iters%step == 0){
            double binSum = bins.sum();
            file << iters;
            for(int i = 0; i < nbins; i++)
            {
                file << "," << bins(i)/binSum;
            }
            if(int(iters/step) < maxStep-1){
                file << "\n";
            }
            else
            {
                break;
            }
        }
    }

    file.close();
}