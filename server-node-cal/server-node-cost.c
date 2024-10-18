#include <stdio.h>
#include <math.h>

float costOfTwoNodes(float cost1, float cost2)
{
    return 1 + (cost2 * ((1.0 / cost1) * (1 - (1.0 / cost2)))) + (cost1 * ((1.0 / cost2) * (1 - (1.0 / cost1))));
}

float costofThreeNodes(float c1, float c2, float c3)
{
    return (c1 + c2 + c3 + (c1 * c2 * c3) - (2 * c1 * c2) - (2 * c2 * c3) - (2 * c3 * c1) + (c3 * costOfTwoNodes(c1, c2)) + (c1 * costOfTwoNodes(c2, c3)) + (c2 * costOfTwoNodes(c3, c1))) / ((1 - c1) * (1 - c2) * (1 - c3));
}

float costofFourNodes(float c1, float c2, float c3, float c4)
{
    return (
        (((((1 - (1.0 / c1)) * (1 - (1.0 / c2)) * (1 - (1.0 / c3)) * (1.0 / c4)) * (1 + costofThreeNodes(c1, c2, c3)))) +
         (((1 - (1.0 / c1)) * (1 - (1.0 / c2)) * (1.0 / c3) * (1 - (1.0 / c4))) * (1 + costofThreeNodes(c1, c2, c4))) +
         (((1 - (1.0 / c1)) * (1.0 / c2) * (1 - (1.0 / c3)) * (1 - (1.0 / c4))) * (1 + costofThreeNodes(c1, c3, c4))) + (((1.0 / c1) * (1 - (1.0 / c2)) * (1 - (1.0 / c3)) * (1 - (1.0 / c4))) * (1 + costofThreeNodes(c2, c3, c4))) +
         (((1 - (1.0 / c1)) * (1 - (1.0 / c2)) * (1.0 / c3) * (1.0 / c4)) * (1 + costOfTwoNodes(c1, c2))) +
         (((1 - (1.0 / c1)) * (1.0 / c2) * (1 - (1.0 / c3)) * (1.0 / c4)) * (1 + costOfTwoNodes(c1, c3))) +
         (((1.0 / c1) * (1 - (1.0 / c2)) * (1 - (1.0 / c3)) * (1.0 / c4)) * (1 + costOfTwoNodes(c2, c3))) +
         (((1 - (1.0 / c1)) * (1.0 / c2) * (1.0 / c3) * (1 - (1.0 / c4))) * (1 + costOfTwoNodes(c1, c4))) +
         (((1.0 / c1) * (1 - (1.0 / c2)) * (1.0 / c3) * (1 - (1.0 / c4))) * (1 + costOfTwoNodes(c2, c4))) +
         (((1.0 / c1) * (1.0 / c2) * (1 - (1.0 / c3)) * (1 - (1.0 / c4))) * (1 + costOfTwoNodes(c3, c4))) +
         (((1 - (1.0 / c1)) * (1.0 / c2) * (1.0 / c3) * (1.0 / c4)) * (1 + c1)) +
         (((1.0 / c1) * (1 - (1.0 / c2)) * (1.0 / c3) * (1.0 / c4)) * (1 + c2)) +
         (((1.0 / c1) * (1.0 / c2) * (1 - (1.0 / c3)) * (1.0 / c4)) * (1 + c3)) +
         (((1.0 / c1) * (1.0 / c2) * (1.0 / c3) * (1 - (1.0 / c4))) * (1 + c4)) + ((1.0 / c1) * (1.0 / c2) * (1.0 / c3) * (1.0 / c4))) /
        ((1 - (1.0 / c1)) * (1 - (1.0 / c2)) * (1 - (1.0 / c3)) * (1 - (1.0 / c4))));
}

int main()
{
    printf("How many nodes are there in the network? ");
    int n;
    scanf("%d", &n);
    float cost[n - 1];
    printf("Enter the cost matrix of the network: \n");

    for (int j = 0; j < n - 1; j++)
    {
        printf("Enter the cost of connection between node %d and node %d: ", 0, j + 1);
        float val;
        scanf("%f", &val);
        cost[j] = val;
    }
    float ans = 0;
    if (n == 2)
    {

        ans = costOfTwoNodes(cost[0], cost[1]);
    }
    else if (n == 3)
    {
        ans = costofThreeNodes(cost[0], cost[1], cost[2]);
    }
    else if (n == 4)
    {
        ans = costofFourNodes(cost[0], cost[1], cost[2], cost[3]);
    }
    else
    {
        printf("The number of nodes is not supported by the program\n");
        return 0;
    }
    printf("The total cost of the network is: %f\n", ans);

    return 0;
}