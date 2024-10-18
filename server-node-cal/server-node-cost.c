#include <stdio.h>
#include <math.h>

float costOfTwoNodes(float cost1, float cost2)
{
    return 1 + (cost2 * ((1.0 / cost1) * (1 - (1.0 / cost2)))) + (cost1 * ((1.0 / cost2) * (1 - (1.0 / cost1))));
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

    float ans = costOfTwoNodes(cost[0], cost[1]);
    printf("The total cost of the network is: %f\n", ans);

    return 0;
}