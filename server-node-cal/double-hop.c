#include <stdio.h>

void printTable(int n, int m, int a[][m])
{
    printf("\n\n");
    for (int i = 0; i < n; i++)
    {
        printf("Node %d: ", i);
        for (int j = 0; j < m; j++)
        {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

void calculateTableforOne(int node)
{
    printf("Cost for node %d is: %d\n", node, a[0][node]);
}

void generateCombinations(int m)
{
    int total_combinations = (1 << m) - 1;
    for (int i = 1; i <= total_combinations; i++)
    {
        int elements[4];
        int count = 0;
        for (int j = 0; j < m; j++)
        {
            if (i & (1 << j))
            {
                elements[count++] = j + 1;
            }
        }
        if (count == 1)
        {
            calculateTableforOne(elements[0]);
        }
        else if (count == 2)
        {
            calculateTableforTwo(elements[0], elements[1]);
        }
        else if (count == 3)
        {
            calculateTableforThree(elements[0], elements[1], elements[2]);
        }
        else if (count == 4)
        {
            calculateTableforFour(elements[0], elements[1], elements[2], elements[3]);
        }
    }
}

int main()
{
    int n;
    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    int a[n][n];

    printf("How many Middle Nodes do you want to add? ");
    int m;
    scanf("%d", &m);

    if (m > n - 1)
    {
        printf("Invalid Input\n");
        return 0;
    }

    // Initializing Table with 0
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            a[i][j] = 0;
        }
    }

    // Taking Cost from Source to Middle Nodes
    for (int i = 1; i <= m; i++)
    {
        printf("\nEnter the cost from Node 0 to Node %d: ", i);
        int val;
        scanf("%d", &val);
        a[0][i] = val;
    }
    // Taking Cost from Middle Nodes to Destination
    printf("\n");
    for (int i = 1; i <= m; i++)
    {

        for (int j = m + 1; j < n; j++)
        {
            printf("\nEnter the cost from Node %d to Node %d: ", i, j);
            int val;
            scanf("%d", &val);
            a[i][j] = val;
        }
    }

    generateCombinations(m);

    printTable(n, n, a);
    return 0;
}
