#include <stdio.h>
#include <limits.h>

int n, cost[10][10], visited[10];
int minCost = INT_MAX;

void tsp(int city, int count, int totalCost, int start) {
    if (count == n) {
        if (cost[city][start] != -1) {
            int finalCost = totalCost + cost[city][start];
            if (finalCost < minCost)
                minCost = finalCost;
        }
        return;
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i] && cost[city][i] != -1) {
            visited[i] = 1;
            tsp(i, count + 1, totalCost + cost[city][i], start);
            visited[i] = 0;
        }
    }
}

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
        }
    }

    visited[0] = 1;
    tsp(0, 1, 0, 0);

    printf("%d\n", minCost);

    return 0;
}
