#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>

using namespace std;

vector<vector<int>> generateBinaryCombinations(int destNodes)
{
    int total_combinations = pow(2, destNodes);
    vector<vector<int>> combinations;

    for (int i = 0; i < total_combinations; i++)
    {
        vector<int> combination;
        for (int j = destNodes - 1; j >= 0; j--)
        {
            combination.push_back((i >> j) & 1);
        }
        combinations.push_back(combination);
    }

    return combinations;
}
float costOfTwoNodes(float cost1, float cost2)
{
    return 1 + (cost2 * ((1.0 / cost1) * (1 - (1.0 / cost2)))) +
           (cost1 * ((1.0 / cost2) * (1 - (1.0 / cost1))));
}

std::mt19937 gen(std::random_device{}());

double generateRandomNumber()
{
    std::uniform_real_distribution<> dis(0.0, 1.0);
    return std::round(dis(gen) * 100) / 100;
}

int approxCostCalculationSingleHop(vector<vector<float>> a, vector<int> destinations, int totalTrials)
{
    int totalDestinations = destinations.size();
    vector<int> destCountValue(totalDestinations + 1, totalTrials);
    vector<vector<int>> binaryCombinations = generateBinaryCombinations(totalDestinations);
    // generating Multiplication of Each Possible probabilities of reaching destination
    vector<float> numberLine;
    for (int i = 0; i < binaryCombinations.size(); i++)
    {
        float val = 1;
        for (int j = 0; j < destinations.size(); j++)
        {
            if (binaryCombinations[i][j] == 1 && a[0][destinations[j]] != -1)
            {
                val = val * a[0][destinations[j]];
            }
            else if (binaryCombinations[i][j] == 0 && a[0][destinations[j]] != -1)
            {
                val = val * (1 - a[0][destinations[j]]);
            }
        }
        if (i == 0)
            numberLine.push_back(val);
        else
        {
            numberLine.push_back(val + numberLine[i - 1]);
        }
    }
    for (int i = 0; i < numberLine.size(); i++)
    {
        cout << numberLine[i] << " ";
    }
    cout << endl;
    int totalCountofTransmissions = 0;
    while (any_of(destCountValue.begin() + 1, destCountValue.end(), [](int val)
                  { return val > 0; }))
    {
        double randomNum = generateRandomNumber();
        // check in which section the random number lies in the number line
        for (int i = 0; i < numberLine.size(); i++)
        {
            if (randomNum < numberLine[i])
            {
                for (int j = 0; j < destinations.size(); j++)
                {
                    if (binaryCombinations[i][j] == 1 && destCountValue[j + 1] > 0)
                    {
                        destCountValue[j + 1]--;
                    }
                }
                break;
            }
        }
        totalCountofTransmissions++;
    }

    return totalCountofTransmissions;
}

int main()
{
    vector<vector<float>> a = {
        {-1, 0.6, 0.4},
        {-1, -1, -1},
        {-1, -1, -1},
    };
    int totalTrials = 10000;
    int totalTransmissions = approxCostCalculationSingleHop(a, {1, 2}, totalTrials);
    float costofNodes = costOfTwoNodes(1.0 / a[0][1], 1.0 / a[0][2]);
    cout << "Cost of nodes is " << costofNodes << endl;
    cout << "Total Transmissions " << totalTransmissions << endl;
    float actualCost = totalTransmissions / (totalTrials * 1.0);
    cout << "Actual Cost " << actualCost << endl;
    return 0;
}
