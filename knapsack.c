#include <stdio.h>

int main() {
    int n, capacity;
    scanf("%d", &n);

    int value[n], weight[n];

    for (int i = 0; i < n; i++)
        scanf("%d", &value[i]);

    for (int i = 0; i < n; i++)
        scanf("%d", &weight[i]);

    scanf("%d", &capacity);

    int dp[capacity + 1];

    for (int w = 0; w <= capacity; w++)
        dp[w] = 0;

    for (int i = 0; i < n; i++) {
        for (int w = capacity; w >= weight[i]; w--) {
            int newValue = dp[w - weight[i]] + value[i];
            if (newValue > dp[w])
                dp[w] = newValue;
        }
    }

    printf("%d\n", dp[capacity]);

    return 0;
}
