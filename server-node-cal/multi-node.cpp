#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

#define ROUND_TO_ONE_DECIMAL(value) (std::round((value) * 10) / 10.0)

void justPrintTable(const vector<vector<int>> &a)
{
    for (int i = 0; i < a.size(); i++)
    {
        cout << "Path " << i + 1 << ": ";
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
    int NodeVal;
    vector<int> destinations;
};

vector<vector<Table>> generateTableForMiddleNodes(int m, int n, vector<vector<int>> &a)
{
    // Create an ofstream object to write to a file
    std::ofstream outFile("output.txt");

    if (!outFile)
    {
        std::cerr << "Error opening the file!" << std::endl;
        cout << "Error opening the file!" << endl;
        return std::vector<vector<Table>>();
    }

    vector<vector<Table>> t;
    int destNodes = n - m - 1;
    vector<vector<int>> combinations = generateBinaryCombinations(destNodes);

    for (int k = 1; k <= m; k++)
    {
        std::string header = "***    FOR NODE " + std::to_string(k) + "   ***\n\n";
        std::cout << header;
        outFile << header; // Write to file as well
        vector<Table> tables;
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
            entry.NodeVal = k;
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

            tables.push_back(entry);
            if (zeroes != destNodes)
            {
                // Printing to console
                for (int val : combinations[i])
                {
                    std::cout << val << " ";
                }
                std::cout << " -> Cost: " << entry.cost << std::endl;

                std::cout << "To Nodes: ";
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

                outFile << "To Nodes: ";
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
        outFile << std::endl;
        t.push_back(tables);
    }
    outFile.close();
    std::cout << "Data written to output.txt" << std::endl;
    return t;
}

vector<vector<int>> generateCombinations(int m, int n, vector<vector<int>> &a, int flag)
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
    if (flag == 1)
    {
        return result;
    }
    for (int i = 0; i < result.size(); i++)
    {
        int flag = 0;
        int count = 0;
        vector<int> temp((n - (m + 1)), 0);
        for (int j = 0; j < result[i].size(); j++)
        {
            int val = result[i][j];

            for (int k = m + 1; k < n; k++)
            {
                if (a[val][k] == 0 && temp[k - m - 1] == 0)
                {
                    temp[k - m - 1] = 0;
                }
                else
                {
                    temp[k - m - 1] = 1;
                }
            }
        }
        for (int j = 0; j < temp.size(); j++)
        {
            if (temp[j] == 0)
            {
                flag = 1;
            }
        }
        cout << endl;

        if (flag)
        {
            result.erase(result.begin() + i);
        }
    }
    return result;
}

float truncateToOneDecimal(float value)
{
    return std::floor(value * 10) / 10.0;
}

void findMinimumCost(int m, int n, vector<vector<int>> &a, vector<vector<int>> &combinations, vector<vector<Table>> tables)
{
    float minCost = 1000.00;
    vector<int> minPath;
    cout << "\n\n";
    std::ofstream outFile("cost.txt");
    if (!outFile)
    {
        std::cerr << "Error opening the file!" << std::endl;
        cout << "Error opening the file!" << endl;
    }

    for (int i = 0; i < combinations.size(); i++)
    {
        float cost = 1000.0;
        vector<int> path;
        if (combinations[i].size() == 1)
        {
            float c1 = 0;
            int node = combinations[i][0];
            for (int j = 0; j < tables[combinations[i][0]].size(); j++)
            {
                if (tables[node - 1][j].destinations.size() == (n - (m + 1)))
                {
                    c1 += tables[node - 1][j].cost;
                    path.push_back(tables[node - 1][j].NodeVal);
                    for (int k = 0; k < tables[node - 1][j].destinations.size(); k++)
                    {
                        path.push_back(tables[node - 1][j].destinations[k]);
                    }
                }
            }
            c1 += a[0][node];
            cout << "Cost via " << node << " is " << c1 << endl;
            cost = c1;

            outFile << "Cost via " << node << " is " << c1 << std::endl;
        }
        if (combinations[i].size() == 2)
        {
            int node1 = combinations[i][0];
            int node2 = combinations[i][1];

            // Check if one node can send to both destinations
            bool canSendToBoth1 = false;
            for (int j = 0; j < tables[node1 - 1].size(); j++)
            {
                if (tables[node1 - 1][j].destinations.size() == (n - (m + 1)) && tables[node1 - 1][j].cost != -1)
                {
                    canSendToBoth1 = true;
                }
            }
            // Check if node2 can send to both destinations
            bool canSendToBoth2 = false;
            for (int j = 0; j < tables[node2 - 1].size(); j++)
            {
                if (tables[node2 - 1][j].destinations.size() == (n - (m + 1)) && tables[node2 - 1][j].cost != -1)
                {
                    canSendToBoth2 = true;
                }
                else
                {
                    canSendToBoth2 = false;
                }
            }

            // function if one can send to both the nodes
            if (canSendToBoth1 || canSendToBoth2)
            {
                int cannotSend;
                int canSend;
                if (canSendToBoth1)
                {
                    canSend = node1;
                    cannotSend = node2;
                }
                else
                {
                    canSend = node2;
                    cannotSend = node1;
                }
                int dest1 = 0;
                for (int j = 0; j < tables[cannotSend - 1].size(); j++)
                {
                    if (tables[cannotSend - 1][j].destinations.size() == 1 && tables[cannotSend - 1][j].cost != -1)
                    {
                        dest1 = tables[cannotSend - 1][j].destinations[0];
                    }
                }

                int val1 = a[0][cannotSend];
                int val2 = a[cannotSend][dest1];

                int val3 = a[0][canSend];
                int val4 = a[canSend][dest1];
                int dest2 = 0;
                for (int j = 0; j < tables[canSend - 1].size(); j++)
                {
                    if (tables[canSend - 1][j].destinations.size() == 2 && tables[canSend - 1][j].cost != -1)
                    {
                        if (tables[canSend - 1][j].destinations[0] == dest1)
                        {

                            dest2 = tables[canSend - 1][j].destinations[1];
                        }
                        else if (tables[canSend - 1][j].destinations[1] == dest1 && tables[canSend - 1][j].destinations.size() == 2)
                        {
                            dest2 = tables[canSend - 1][j].destinations[0];
                        }
                    }
                }
                int val5 = a[canSend][dest2];

                float costOfTwoNode = costOfTwoNodes(static_cast<float>(val4), static_cast<float>(val5));

                float c1 = ((
                                (1 - (1.0f / val1)) * (1 - (1.0f / val3)) +
                                (1 - (1.0f / val1)) * (1.0f / val3) * (1 + costOfTwoNode) +
                                (1.0f / val1) * (1 - (1.0f / val3)) * (1 + std::min(static_cast<float>(val2), val3 + costOfTwoNode)) +
                                (1.0f / val1) * (1.0f / val3) * (1 + std::min(static_cast<float>(val3 + val5), costOfTwoNode))) /
                            (1 - ((1 - (1.0f / val1)) * (1 - (1.0f / val3)))));

                cout << "Cost via " << node1 << " & " << node2 << " is " << c1 << endl;
                cost = c1;
                path.push_back(canSend);
                path.push_back(cannotSend);

                outFile << "Cost via " << node1 << " & " << node2 << " is " << c1 << std::endl;
            }
            if (!canSendToBoth1 && !canSendToBoth2)
            {

                int dest1 = 0;
                int dest2 = 0;
                for (int j = 0; j < tables[node1 - 1].size(); j++)
                {
                    if (tables[node1 - 1][j].destinations.size() == 1 && tables[node1 - 1][j].cost != -1)
                    {
                        dest1 = tables[node1 - 1][j].destinations[0];
                    }
                }
                for (int j = 0; j < tables[node2 - 1].size(); j++)
                {
                    if (tables[node2 - 1][j].destinations.size() == 1 && tables[node2 - 1][j].cost != -1)
                    {
                        dest2 = tables[node2 - 1][j].destinations[0];
                    }
                }

                int val1 = a[0][node1];
                int val2 = a[0][node2];
                int val3 = a[node1][dest1];
                int val4 = a[node2][dest2];

                float c1 = ((((1 - truncateToOneDecimal(1.0 / val1)) * (1 - truncateToOneDecimal(1.0 / val2))) +
                             (truncateToOneDecimal(1.0 / val1) * (1 - truncateToOneDecimal(1.0 / val2)) * (1 + val3 + val2 + val4)) +
                             (truncateToOneDecimal(1.0 / val2) * (1 - truncateToOneDecimal(1.0 / val1)) * (1 + val4 + val1 + val3)) +
                             (truncateToOneDecimal(1.0 / val1) * truncateToOneDecimal(1.0 / val2) * (1 + val3 + val4))) /
                            (1 - truncateToOneDecimal((1 - truncateToOneDecimal(1.0 / val1)) * (1 - truncateToOneDecimal(1.0 / val2)))));
                cout
                    << "Cost via " << node1 << " & " << node2 << " is  " << c1 << endl;
                cost = c1;
                path.push_back(node1);
                path.push_back(node2);

                outFile << "Cost via " << node1 << " & " << node2 << " is " << c1 << std::endl;
            }
        }
        if (combinations[i].size() == 3)
        {
            int node1 = combinations[i][0];
            int node2 = combinations[i][1];
            int node3 = combinations[i][2];

            cout << "Cost via 3 Nodes:  " << cost << endl;
        }
        if (cost < minCost)
        {
            minCost = cost;
            minPath = path;
        }
    }
    cout << "Minimum Cost: " << minCost << endl;
    cout << "Path: ";
    for (int i = 0; i < minPath.size(); i++)
    {
        cout << minPath[i] << " ";
    }
    cout << endl;
    outFile << "Minimum Cost: " << minCost << std::endl;
    outFile << "Path: ";
    for (int i = 0; i < minPath.size(); i++)
    {
        outFile << minPath[i] << " ";
    }
    outFile << std::endl;

    outFile.close();
    std::cout << "Cost Data written to cost.txt" << std::endl;
}

vector<vector<int>> generateDestinationCombinations(int n, int m)
{
    int totalDestinations = n - (m + 1);
    vector<int> destinations;
    for (int i = m + 1; i <= n - 1; i++)
    {
        destinations.push_back(i);
    }

    int totalCombinations = pow(2, totalDestinations) - 1;
    vector<vector<int>> combinations;

    for (int i = 1; i <= totalCombinations; i++)
    {
        vector<int> combination;
        for (int j = 0; j < totalDestinations; j++)
        {
            if (i & (1 << j))
            {
                combination.push_back(destinations[j]);
            }
        }
        combinations.push_back(combination);
    }
    return combinations;
}

float findCostForTwoElements(int c1, int c2, int c3, int c4)
{
    return ((
                ((1 - (1.0 / c1)) * (1 - (1.0 / c2))) +
                ((1 - (1.0 / c1)) * (1.0 / c2) * (1 + c4)) +
                ((1.0 / c1) * (1 - (1.0 / c2)) * (1 + c3)) +
                ((1.0 / c1) * (1.0 / c2) * (1 + min(c3, c4)))) /
            (1 - ((1 - (1.0 / c1)) * (1 - (1.0 / c2)))));
}

float findCostForThreeElements(int c1, int c2, int c3, int c4, int c5, int c6)
{
    return ((
                ((1 - (1.0 / c1)) * (1 - (1.0 / c2)) * (1 - (1.0 / c3))) +
                ((1 - (1.0 / c1)) * (1 - (1.0 / c2)) * (1.0 / c3) * (1 + c6)) +
                ((1 - (1.0 / c1)) * (1.0 / c2) * (1 - (1.0 / c3)) * (1 + c5)) +
                ((1 - (1.0 / c1)) * (1.0 / c2) * (1.0 / c3) * (1 + min(c5, c6))) +
                ((1.0 / c1) * (1 - (1.0 / c2)) * (1 - (1.0 / c3)) * (1 + c4)) +
                ((1.0 / c1) * (1 - (1.0 / c2)) * (1.0 / c3) * (1 + min(c4, c6))) +
                ((1.0 / c1) * (1.0 / c2) * (1 - (1.0 / c3)) * (1 + min(c4, c5))) +
                ((1.0 / c1) * (1.0 / c2) * (1.0 / c3) * (1 + min(min(c4, c5), c6)))) /
            (1 - ((1 - (1.0 / c1)) * (1 - (1.0 / c2)) * (1 - (1.0 / c3)))));
}

void generateTableForEachDestination(int n, int m, vector<vector<int>> &a, vector<vector<Table>> &tables, vector<vector<int>> &destCombinations, vector<vector<int>> combinations)
{
    vector<Table> t;
    for (int i = 0; i < destCombinations.size(); i++)
    {
        if (destCombinations[i].size() == 1)
        {

            int dest = destCombinations[i][0];
            float minCost = 1000.0;
            vector<int> minNode;
            Table entry;
            for (int i = 0; i < combinations.size(); i++)
            {
                int canSend = 1;
                vector<int> Nodes;
                for (int j = 0; j < combinations[i].size(); j++)
                {
                    int node = combinations[i][j];

                    int flag = 0;
                    if (a[node][dest] == 0)
                    {
                        canSend = 0;
                        break;
                    }
                }

                if (canSend)
                {
                    float cost = 0;

                    if (combinations[i].size() == 1)
                    {
                        int node = combinations[i][0];
                        cost += a[0][node];
                        for (int k = 0; k < tables[node - 1].size(); k++)
                            if (tables[node - 1][k].destinations.size() == 1 && tables[node - 1][k].destinations[0] == dest && tables[node - 1][k].cost != -1)
                            {
                                cost += tables[node - 1][k].cost;
                                Nodes.push_back(node);
                            }
                    }
                    if (combinations[i].size() == 2)
                    {
                        int node1 = combinations[i][0];
                        int node2 = combinations[i][1];
                        cost = findCostForTwoElements(a[0][node1], a[0][node2], a[node1][dest], a[node2][dest]);
                        Nodes.push_back(node1);
                        Nodes.push_back(node2);
                    }
                    if (combinations[i].size() == 3)
                    {
                        int node1 = combinations[i][0];
                        int node2 = combinations[i][1];
                        int node3 = combinations[i][2];
                        cost = findCostForThreeElements(a[0][node1], a[0][node2], a[0][node3], a[node1][dest], a[node2][dest], a[node3][dest]);
                        Nodes.push_back(node1);
                        Nodes.push_back(node2);
                        Nodes.push_back(node3);
                    }

                    if (cost < minCost)
                    {
                        minCost = cost;
                        minNode = Nodes;
                    }
                    entry.cost = cost;
                    entry.NodeVal = -1;
                    entry.destinations.push_back(dest);
                    entry.combinations = Nodes;
                    t.push_back(entry);
                }
            }
        }
    }
    for (int i = 0; i < destCombinations.size(); i++)
    {
        if (destCombinations[i].size() == 2)
        {

            int dest1 = destCombinations[i][0];
            int dest2 = destCombinations[i][1];
            float minCost = 1000.0;
            vector<int> minNode;
            Table entry;
            for (int i = 0; i < combinations.size(); i++)
            {
                int canSend = 1;
                vector<int> Nodes;
                int dest1CanBeSent = 0;
                int dest2CanBeSent = 0;

                for (int j = 0; j < combinations[i].size(); j++)
                {
                    int node = combinations[i][j];

                    int flag = 0;
                    if (a[node][dest1] != 0 && dest1CanBeSent == 0)
                    {
                        dest1CanBeSent = 1;
                    }
                    if (a[node][dest2] != 0 && dest2CanBeSent == 0)
                    {
                        dest2CanBeSent = 1;
                    }
                }

                if (dest1CanBeSent && dest2CanBeSent)
                {
                    float cost = 0;

                    if (combinations[i].size() == 3)
                    {
                        int node1 = combinations[i][0];
                        int node2 = combinations[i][1];
                        int node3 = combinations[i][2];
                        // cost = findCostForThreeElements(a[0][node1], a[0][node2], a[0][node3], a[node1][dest], a[node2][dest], a[node3][dest]);
                        Nodes.push_back(node1);
                        Nodes.push_back(node2);
                        Nodes.push_back(node3);
                    }
                }
            }
        }
    }

    cout << endl;
    for (int i = 0; i < t.size(); i++)
    {
        cout << "Cost from 0 to " << t[i].destinations[0] << " is " << t[i].cost << " via ";
        for (int j = 0; j < t[i].combinations.size(); j++)
        {
            cout << t[i].combinations[j] << " ";
        }
        cout << endl;
    }
    cout << endl;
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
    vector<vector<Table>> tables = generateTableForMiddleNodes(m, n, a);
    cout << "Tables generated" << endl;
    vector<vector<int>> combinations = generateCombinations(m, n, a, 1);
    vector<vector<int>> Possiblecombinations = generateCombinations(m, n, a, 0);
    vector<vector<int>> destCombinations = generateDestinationCombinations(n, m);
    generateTableForEachDestination(n, m, a, tables, destCombinations, combinations);

    cout << "Nodes thorugh which the path can be established: \n";
    justPrintTable(Possiblecombinations);
    findMinimumCost(m, n, a, Possiblecombinations, tables);

    // printTable(n, a);

    return 0;
}
