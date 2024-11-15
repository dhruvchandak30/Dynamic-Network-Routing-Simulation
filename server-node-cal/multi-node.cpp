#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <fstream>

using namespace std;

#include <fstream>
#include <iostream>
#include <vector>

void justPrintTable( const vector<vector<int>> &a)
{
    for (int i = 0; i < a.size(); i++)
    {
        cout << "Node " << i << ": ";
        for (int j = 0; j < a[i].size(); j++)
        {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

void printTable(int n, const vector<vector<int>> &a)
{
    // Create an ofstream object to write to a file
    std::ofstream outFile("table_output.txt");

    if (!outFile)
    {
        std::cerr << "Error opening the file!" << std::endl;
        return;
    }

    std::cout << "\n\n";
    outFile << "\n\n"; // Write a newline to the file

    for (int i = 0; i < n; i++)
    {
        std::string nodeHeader = "Node " + std::to_string(i) + ": ";
        std::cout << nodeHeader;
        outFile << nodeHeader; // Write to file as well

        for (int j = 0; j < n; j++)
        {
            std::cout << a[i][j] << " ";
            outFile << a[i][j] << " "; // Write each value to the file
        }

        std::cout << "\n";
        outFile << "\n"; // Write a newline to the file
    }

    outFile.close(); // Don't forget to close the file
    std::cout << "Data written to table_output.txt" << std::endl;
}

float costOfTwoNodes(float cost1, float cost2)
{
    return 1 + (cost2 * ((1.0 / cost1) * (1 - (1.0 / cost2)))) +
           (cost1 * ((1.0 / cost2) * (1 - (1.0 / cost1))));
}

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

struct Table
{
    vector<int> combinations;
    float cost;
    vector<int> destinations;
};

void generateTableForMiddleNodes(int m, int n, vector<vector<int>> &a)
{
    // Create an ofstream object to write to a file
    std::ofstream outFile("output.txt");

    if (!outFile)
    {
        std::cerr << "Error opening the file!" << std::endl;
        return;
    }

    vector<Table> t;
    int destNodes = n - m - 1;
    vector<vector<int>> combinations = generateBinaryCombinations(destNodes);

    for (int k = 1; k <= m; k++)
    {
        std::string header = "***    FOR NODE " + std::to_string(k) + "   ***\n\n";
        std::cout << header;
        outFile << header; // Write to file as well

        for (int i = 0; i < combinations.size(); i++)
        {
            vector<int> destinations;
            bool flag = false;
            int zeroes = 0;

            for (int j = 0; j < combinations[i].size(); j++)
            {
                if (combinations[i][j] == 1)
                {
                    destinations.push_back(m + j + 1);
                }
                if (a[k][m + j + 1] == 0 && combinations[i][j] == 1)
                {
                    flag = true;
                }
                if (combinations[i][j] == 0)
                {
                    zeroes++;
                }
            }

            Table entry;
            entry.combinations = combinations[i];
            entry.destinations = destinations;

            if (flag)
            {
                entry.cost = -1;
            }
            else
            {
                if (destinations.size() == 1)
                {
                    entry.cost = a[k][destinations[0]];
                }
                else if (destinations.size() == 2)
                {
                    entry.cost = costOfTwoNodes(a[k][destinations[0]], a[k][destinations[1]]);
                }
                else
                {
                    entry.cost = 0;
                }
            }

            t.push_back(entry);
            if (zeroes != destNodes)
            {
                // Printing to console
                for (int val : combinations[i])
                {
                    std::cout << val << " ";
                }
                std::cout << " -> Cost: " << entry.cost << std::endl;

                std::cout << "Via Nodes: ";
                for (int i = 0; i < destinations.size(); i++)
                {
                    std::cout << destinations[i];
                    if (i != destinations.size() - 1)
                    {
                        std::cout << ", ";
                    }
                }
                std::cout << std::endl;
                std::cout << std::endl;

                // Writing to file
                for (int val : combinations[i])
                {
                    outFile << val << " ";
                }
                outFile << " -> Cost: " << entry.cost << std::endl;

                outFile << "Via Nodes: ";
                for (int i = 0; i < destinations.size(); i++)
                {
                    outFile << destinations[i];
                    if (i != destinations.size() - 1)
                    {
                        outFile << ", ";
                    }
                }
                outFile << std::endl;
                outFile << std::endl;
            }
        }
        std::cout << std::endl;
        outFile << std::endl; // Newline in the file
    }
    outFile.close(); // Don't forget to close the file
    std::cout << "Data written to output.txt" << std::endl;
}

vector<vector<int>> generateCombinations(int m)
{
    vector<vector<int>> result;
    int totalCombinations = (1 << m);

    for (int mask = 1; mask < totalCombinations; ++mask)
    {
        vector<int> combination;

        for (int i = 0; i < m; ++i)
        {
            if (mask & (1 << i))
            {
                combination.push_back(i + 1);
            }
        }

        result.push_back(combination);
    }

    return result;
}

int main()
{
    int n;
    cout << "Enter the number of nodes: ";
    cin >> n;

    vector<vector<int>> a(n, vector<int>(n, 0));

    cout << "How many Middle Nodes do you want to add? ";
    int m;
    cin >> m;

    if (m > n - 1)
    {
        cout << "Invalid Input\n";
        return 0;
    }

    // Taking Cost from Source to Middle Nodes
    for (int i = 1; i <= m; i++)
    {
        cout << "\nEnter the cost from Node 0 to Node " << i << ": ";
        int val;
        cin >> val;
        a[0][i] = val;
    }

    // Taking Cost from Middle Nodes to Destination
    cout << "\n";
    for (int i = 1; i <= m; i++)
    {
        for (int j = m + 1; j < n; j++)
        {
            cout << "\nEnter the cost from Node " << i << " to Node " << j << ": ";
            int val;
            cin >> val;
            a[i][j] = val;
        }
    }
    cout << endl;
    // generateTableForMiddleNodes(m, n, a);
    vector<vector<int>> combinations = generateCombinations(m);
    justPrintTable(combinations);

    // printTable(n, a);

    return 0;
}
