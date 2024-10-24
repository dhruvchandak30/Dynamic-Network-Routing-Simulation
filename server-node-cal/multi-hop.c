#include <stdio.h>
#include <stdlib.h>
#include <float.h>

int min(int a, int b)
{
    return (a < b) ? a : b;
}

float findCostForOneElement(int cost[2])
{
    return cost[0] + cost[1];
}

float findCostForTwoElements(int cost1[2], int cost2[2])
{
    int c1 = cost1[0];
    int c2 = cost2[0];
    int c3 = cost1[1];
    int c4 = cost2[1];
    return ((
                ((1 - (1.0 / c1)) * (1.0 / c2) * (1 + c4)) + ((1.0 / c1) * ((1 - (1.0 / c2)) * (1 + c3))) +
                ((1.0 / c1) * (1.0 / c2) * (1 + min(c3, c4)))) /
            ((1 - (1.0 / c1)) * (1 - (1.0 / c2))));
}

void storeCombinations(int arr[][2], int n, int **combinations, int *sizes, int *totalCombinations)
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

void processCombinations(int **combinations, int *sizes, int totalCombinations, int arr[][2])
{
    float minimum = FLT_MAX;
    for (int i = 0; i < totalCombinations; i++)
    {
        if (sizes[i] == 1)
        {
            int node = combinations[i][0];
            float val = findCostForOneElement(arr[node - 1]);
            if (val < minimum)
            {
                minimum = val;
            }
        }
        else if (sizes[i] == 2)
        {
            int node1 = combinations[i][0];
            int node2 = combinations[i][1];
            float val = findCostForTwoElements(arr[node1 - 1], arr[node2 - 1]);
            if (val < minimum)
            {
                minimum = val;
            }
        }
    }
    printf("\n\nMinimum cost is: %f\n", minimum);
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

    int arr[n][2];
    for (int i = 0; i < n; i++)
    {
        printf("Enter cost from server to node %d: ", i + 1);
        scanf("%d", &arr[i][0]);
        printf("Enter cost from node %d to client: ", i + 1);
        scanf("%d", &arr[i][1]);
    }

    storeCombinations(arr, n, combinations, sizes, &totalCombinations);

    processCombinations(combinations, sizes, totalCombinations, arr);

    for (int i = 0; i < (1 << n); i++)
    {
        free(combinations[i]);
    }
    free(combinations);
    free(sizes);

    return 0;
}
