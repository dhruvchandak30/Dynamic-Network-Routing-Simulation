#include <stdio.h>
#include <stdlib.h>
#include <float.h>

float min(float a, float b)
{
    return (a < b) ? a : b;
}

float findCostForOneElement(float cost[2])
{
    return cost[0] + cost[1];
}

float findCostForTwoElements(float cost1[2], float cost2[2])
{
    float c1 = cost1[0];
    float c2 = cost2[0];
    float c3 = cost1[1];
    float c4 = cost2[1];
    return ((
                ((1 - (1.0 / c1)) * (1 - (1.0 / c2))) +
                ((1 - (1.0 / c1)) * (1.0 / c2) * (1 + c4)) +
                ((1.0 / c1) * (1 - (1.0 / c2)) * (1 + c3)) +
                ((1.0 / c1) * (1.0 / c2) * (1 + min(c3, c4)))) /
            ((1 - (1.0 / c1)) * (1 - (1.0 / c2))));
}

float findCostForThreeElements(float cost1[2], float cost2[2], float cost3[2])
{
    float c1 = cost1[0];
    float c2 = cost2[0];
    float c3 = cost3[0];
    float c4 = cost1[1];
    float c5 = cost2[1];
    float c6 = cost3[1];

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

float findCostForFourElements(float cost1[2], float cost2[2], float cost3[2], float cost4[2])
{
    float c1 = cost1[0];
    float c2 = cost2[0];
    float c3 = cost3[0];
    float c4 = cost4[0];
    float c5 = cost1[1];
    float c6 = cost2[1];
    float c7 = cost3[1];
    float c8 = cost4[1];

    return ((
                ((1 - (1.0 / c1)) * (1 - (1.0 / c2)) * (1 - (1.0 / c3)) * (1 - (1.0 / c4))) +
                ((1 - (1.0 / c1)) * (1 - (1.0 / c2)) * (1 - (1.0 / c3)) * (1.0 / c4) * (1 + c8)) +
                ((1 - (1.0 / c1)) * (1 - (1.0 / c2)) * (1.0 / c3) * (1 - (1.0 / c4)) * (1 + c7)) +
                ((1 - (1.0 / c1)) * (1 - (1.0 / c2)) * (1.0 / c3) * (1.0 / c4) * (1 + min(c7, c8))) +
                ((1 - (1.0 / c1)) * (1.0 / c2) * (1 - (1.0 / c3)) * (1 - (1.0 / c4)) * (1 + c6)) +
                ((1 - (1.0 / c1)) * (1.0 / c2) * (1 - (1.0 / c3)) * (1.0 / c4) * (1 + min(c6, c8))) +
                ((1 - (1.0 / c1)) * (1.0 / c2) * (1.0 / c3) * (1 - (1.0 / c4)) * (1 + min(c6, c7))) +
                ((1 - (1.0 / c1)) * (1.0 / c2) * (1.0 / c3) * (1.0 / c4) * (1 + min(min(c6, c7), c8))) +
                ((1.0 / c1) * (1 - (1.0 / c2)) * (1 - (1.0 / c3)) * (1 - (1.0 / c4)) * (1 + c5)) +
                ((1.0 / c1) * (1 - (1.0 / c2)) * (1 - (1.0 / c3)) * (1.0 / c4) * (1 + min(c5, c8))) +
                ((1.0 / c1) * (1 - (1.0 / c2)) * (1.0 / c3) * (1 - (1.0 / c4)) * (1 + min(c5, c7))) +
                ((1.0 / c1) * (1 - (1.0 / c2)) * (1.0 / c3) * (1.0 / c4) * (1 + min(c5, min(c7, c8)))) +
                ((1.0 / c1) * (1.0 / c2) * (1 - (1.0 / c3)) * (1 - (1.0 / c4)) * (1 + min(c5, c6))) +
                ((1.0 / c1) * (1.0 / c2) * (1 - (1.0 / c3)) * (1.0 / c4) * (1 + min(c5, min(c6, c8))) +
                 ((1.0 / c1) * (1.0 / c2) * (1.0 / c3) * (1 - (1.0 / c4)) * (1 + min(c5, min(c6, c7))) +
                  ((1.0 / c1) * (1.0 / c2) * (1.0 / c3) * (1.0 / c4) * (1 + min(min(c5, c6), min(c7, c8))))))) /
            (1 - ((1 - (1.0 / c1)) * (1 - (1.0 / c2)) * (1 - (1.0 / c3)) * (1 - (1.0 / c4)))));
}

void storeCombinations(float arr[][2], int n, int **combinations, int *sizes, int *totalCombinations)
{
    int count = 0;
    int totalComb = (1 << n);

    for (int i = 1; i < totalComb; i++)
    {
        int size = 0;
        for (int j = 0; j < n; j++)
        {
            if (i & (1 << j))
            {
                combinations[count][size] = j + 1;
                size++;
            }
        }
        sizes[count] = size;
        count++;
    }
    *totalCombinations = count;
}

void processCombinations(int **combinations, int *sizes, int totalCombinations, float arr[][2])
{
    float minimum = FLT_MAX;
    int bestCombinationIndex = -1;

    printf("\n\n");

    for (int i = 0; i < totalCombinations; i++)
    {

        if (sizes[i] == 1)
        {
            int node = combinations[i][0];
            float val = findCostForOneElement(arr[node - 1]);
            printf("Cost for node %d is: %f\n", node, val);
            if (val < minimum)
            {
                minimum = val;
                bestCombinationIndex = i;
            }
        }
        else if (sizes[i] == 2)
        {
            int node1 = combinations[i][0];
            int node2 = combinations[i][1];
            float val = findCostForTwoElements(arr[node1 - 1], arr[node2 - 1]);
            printf("Cost for nodes %d and %d is: %f\n", node1, node2, val);
            if (val < minimum)
            {
                minimum = val;
                bestCombinationIndex = i;
            }
        }
        else if (sizes[i] == 3)
        {
            int node1 = combinations[i][0];
            int node2 = combinations[i][1];
            int node3 = combinations[i][2];
            float val = findCostForThreeElements(arr[node1 - 1], arr[node2 - 1], arr[node3 - 1]);
            printf("Cost for nodes %d, %d and %d is: %f\n", node1, node2, node3, val);
            if (val < minimum)
            {
                minimum = val;
                bestCombinationIndex = i;
            }
        }
        else if (sizes[i] == 4)
        {
            int node1 = combinations[i][0];
            int node2 = combinations[i][1];
            int node3 = combinations[i][2];
            int node4 = combinations[i][3];
            float val = findCostForFourElements(arr[node1 - 1], arr[node2 - 1], arr[node3 - 1], arr[node4 - 1]);
            printf("Cost for nodes %d, %d, %d and %d is: %f\n", node1, node2, node3, node4, val);
            if (val < minimum)
            {
                minimum = val;
                bestCombinationIndex = i;
            }
        }
    }

    printf("\n\nMinimum cost is: %f\n", minimum);
    printf("Best combination is: { ");
    for (int j = 0; j < sizes[bestCombinationIndex]; j++)
    {
        printf("Node %d ", combinations[bestCombinationIndex][j]);
    }
    printf("}\n");
}

int main()
{
    int n;
    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    int **combinations = (int **)malloc((1 << n) * sizeof(int *));
    for (int i = 0; i < (1 << n); i++)
    {
        combinations[i] = (int *)malloc(n * sizeof(int));
    }

    int *sizes = (int *)malloc((1 << n) * sizeof(int));
    int totalCombinations = 0;

    float arr[n][2];
    for (int i = 0; i < n; i++)
    {
        printf("\nEnter cost from server to node %d: ", i + 1);
        scanf("%f", &arr[i][0]);
        printf("\nEnter cost from node %d to client: ", i + 1);
        scanf("%f", &arr[i][1]);
    }
    printf("\n\n");

    for (int i = 0; i < n; i++)
    {
        printf("Cost from server to node %d: %f\n", i + 1, arr[i][0]);
        printf("Cost from node %d to client: %f\n", i + 1, arr[i][1]);
    }

    storeCombinations(arr, n, combinations, sizes, &totalCombinations);

    processCombinations(combinations, sizes, totalCombinations, arr);

    // for (int i = 0; i < (1 << n); i++)
    // {
    //     free(combinations[i]);
    // }
    // free(combinations);
    // free(sizes);

    return 0;
}
