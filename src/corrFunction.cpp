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

    Vector Time(iterations);
    Vector CorrFn(iterations);
    CorrFn.setZero();

    for(int i = 0; i < Time.size(); i++)
    {
        Time(i) = i;
    }

   for(int average = 0; average < averages; average++)
    {
        start = double(average)/double(averages);

        Vector Pos(iterations);

        State s(start, nonLin, model);
        s.UpdateIters(Pos);
        double avg = Pos.mean();
        for(int i = 0; i < iterations; i++)
        {
            Pos(i) = Pos(i) - avg;
        }
        Pos = (start-avg)*(Pos);

        CorrFn = CorrFn + Pos/averages;
    }

    std::string FileName;
    if (model == "logistic")
    {
        FileName = saveFolder + "logisticCorrFn-R" + std::to_string(nonLin) + ".csv";
    }
    std::ofstream file;
    file.open(FileName);
    file << std::setprecision(15);
    file << "Time" << "," << "CorrFn";
    for (int i = 0; i < CorrFn.size(); i++)
    {
        file << "\n" << Time(i) << "," << CorrFn(i);
    }
    file.close();
}