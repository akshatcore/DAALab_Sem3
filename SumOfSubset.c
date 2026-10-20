#include <stdio.h>

#define MAX_N 20
#define MAX_SUBSETS 1048576

int nums[MAX_N];
int currentSubset[MAX_N];

// Store discovered subsets
int subsets[MAX_SUBSETS][MAX_N];
int subsetSizes[MAX_SUBSETS];
int totalSubsets = 0;

void findSubsets(int index, int n, int currentSum, int targetSum, int currentSize) {
    if (currentSum == targetSum) {
        for (int i = 0; i < currentSize; i++) {
            subsets[totalSubsets][i] = currentSubset[i];
        }
        subsetSizes[totalSubsets] = currentSize;
        totalSubsets++;
        return;
    }

    if (index >= n || currentSum > targetSum) {
        return;
    }

    // Include current element
    currentSubset[currentSize] = nums[index];
    findSubsets(index + 1, n, currentSum + nums[index], targetSum, currentSize + 1);

    // Exclude current element
    findSubsets(index + 1, n, currentSum, targetSum, currentSize);
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
    }

    int targetSum;
    scanf("%d", &targetSum);

    findSubsets(0, n, 0, targetSum, 0);

    if (totalSubsets == 0) {
        printf("-1\n");
        return 0;
    }

    // Print subsets in reverse order of discovery with trailing spaces
    for (int i = totalSubsets - 1; i >= 0; i--) {
        for (int j = 0; j < subsetSizes[i]; j++) {
            printf("%d ", subsets[i][j]);
        }
        printf("\n");
    }

    return 0;
}
