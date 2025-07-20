#include "1dMaps.hpp"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

int main(int argc, char *argv[])
{
    double start = 0.5;
    int iterations = 10;
    double nonLin = 1.0;
    int dataPoints = 10;
    int averages = 1;

    double p = 0.3;
    double w = 0.01;

    if (argc != 4)
    {
        std::cout << argc << "\n";
        return -1;
    }

    nonLin = std::atof(argv[1]);
    p = std::atof(argv[2]);
    w = std::atof(argv[3]);

    double xmin = p-w/2.0;
    double xmax = p+w/2.0;
    if (xmin < 0.0)
    {
        xmin = 0.0;
    }
    if (xmax > 1.0)
    {
        xmax = 1.0;
    }

    std::ifstream dataFile("_params.json");
    json params = json::parse(dataFile);

    std::string saveFolder = params["saveFolder"];
    std::string model = params["modelName"];
    iterations = params["iterations"];
    dataPoints = params["dataPoints"];
    averages = params["averages"];

    if (dataPoints > iterations)
    {
        dataPoints = iterations;
    }

    int iStep = int(iterations/dataPoints);

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
    
        start = xmin + (xmax-xmin)*double(average)/double(averages);

        Vector PosSum(iterations);
        Vector Slopes(iterations);
        Vector Time(iterations);

        for(int i = 0; i < Time.size(); i++)
        {
            Time(i) = i;
        }

        State s(start, nonLin, model);
        s.xSum(PosSum, Slopes);

        Vector variances(dataPoints);

        variances.setZero();

        for(int i = 1; i < dataPoints; i++)
        {
            Vector fluctuation(i*iStep);
            double meanX = 0;
            double meanX2 = 0;
            for(int j = 0; j < fluctuation.size(); j++)
            {
                fluctuation(j) = PosSum(j) - Slopes(i*iStep)*Time(j);
                meanX = meanX + fluctuation(j)/(i*iStep);
                meanX2 = meanX2 + fluctuation(j)*fluctuation(j)/(i*iStep);
            }

            variances(i) = meanX2 - meanX*meanX;
        }

        variancesAvg = variancesAvg + variances/averages;
    }

    std::string FileName;
    if (model == "logistic")
    {
        FileName = saveFolder + "logistic-R" + std::to_string(nonLin) + "-P" + std::to_string(p) + "-W" + std::to_string(w) + ".csv";
    } else if (model == "tent")
    {
        FileName = saveFolder + "tent-R" + std::to_string(nonLin) + "-P" + std::to_string(p) + "-W" + std::to_string(w) + ".csv";
    }
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