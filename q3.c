/*
Question 3 – Dynamic Programming
You are given a set of n items, each with a weight wᵢ and a value vᵢ, and a knapsack
of capacity W. Design a dynamic programming algorithm to determine the
maximum value that can be obtained by selecting items such that the total weight
does not exceed W. Each item can be selected at most once (0/1 knapsack problem).
*/

#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int knapsack(int *weights, int *values, int n, int W, int **dp, int *selected) {
    *dp = (int *)malloc((n + 1) * (W + 1) * sizeof(int));
    
    // Initialize and fill DP table
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0) {
                (*dp)[i * (W + 1) + w] = 0;
            } else if (weights[i - 1] <= w) {
                int include = (*dp)[(i - 1) * (W + 1) + (w - weights[i - 1])] + values[i - 1];
                int exclude = (*dp)[(i - 1) * (W + 1) + w];
                (*dp)[i * (W + 1) + w] = max(include, exclude);
            } else {
                (*dp)[i * (W + 1) + w] = (*dp)[(i - 1) * (W + 1) + w];
            }
        }
    }
    
    int max_val = (*dp)[n * (W + 1) + W];
    
    // Backtrack to find selected items
    int count = 0;
    int w = W;
    for (int i = n; i > 0; i--) {
        if ((*dp)[i * (W + 1) + w] != (*dp)[(i - 1) * (W + 1) + w]) {
            selected[count] = i - 1;
            w -= weights[i - 1];
            count++;
        }
    }
    
    return count;
}

void print_array(int *arr, int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]");
}

int main() {
    int weights[] = {2, 3, 4, 5};
    int values[] = {3, 4, 5, 6};
    int n = sizeof(weights) / sizeof(weights[0]);
    int W = 8;
    
    int *dp = NULL;
    int *selected = (int *)malloc(n * sizeof(int));
    
    int count = knapsack(weights, values, n, W, &dp, selected);
    int max_val = dp[n * (W + 1) + W];
    
    printf("Weights: ");
    print_array(weights, n);
    printf("\n");
    printf("Values:  ");
    print_array(values, n);
    printf("\n");
    printf("Capacity W = %d\n", W);
    printf("Max Value: %d\n", max_val);
    printf("Items selected (0-indexed): ");
    print_array(selected, count);
    printf("\n");
    
    int total_weight = 0;
    for (int i = 0; i < count; i++) {
        total_weight += weights[selected[i]];
    }
    printf("Total weight: %d\n", total_weight);

    printf("\nDP Table:\n");
    printf("    ");
    for (int j = 0; j <= W; j++) {
        printf("%3d", j);
    }
    printf("\n");
    
    for (int i = 0; i <= n; i++) {
        if (i == 0) {
            printf(" 0 |");
        } else {
            printf(" %d |", i);
        }
        for (int j = 0; j <= W; j++) {
            printf("%3d", dp[i * (W + 1) + j]);
        }
        printf("\n");
    }

    printf("\nExperimental Results:\n");
    printf("%-6s %-6s %-12s\n", "n", "W", "Max Value");
    
    // Test case 1
    int w1[] = {1, 2, 3};
    int v1[] = {6, 10, 12};
    int cap1 = 5;
    int *dp1 = NULL;
    int *sel1 = (int *)malloc(3 * sizeof(int));
    knapsack(w1, v1, 3, cap1, &dp1, sel1);
    printf("%-6d %-6d %-12d\n", 3, cap1, dp1[3 * (cap1 + 1) + cap1]);
    free(dp1);
    free(sel1);
    
    // Test case 2
    int w2[] = {2, 3, 4, 5};
    int v2[] = {3, 4, 5, 6};
    int cap2 = 8;
    int *dp2 = NULL;
    int *sel2 = (int *)malloc(4 * sizeof(int));
    knapsack(w2, v2, 4, cap2, &dp2, sel2);
    printf("%-6d %-6d %-12d\n", 4, cap2, dp2[4 * (cap2 + 1) + cap2]);
    free(dp2);
    free(sel2);
    
    // Test case 3
    int w3[] = {1, 2, 3, 4, 5};
    int v3[] = {1, 6, 10, 16, 15};
    int cap3 = 7;
    int *dp3 = NULL;
    int *sel3 = (int *)malloc(5 * sizeof(int));
    knapsack(w3, v3, 5, cap3, &dp3, sel3);
    printf("%-6d %-6d %-12d\n", 5, cap3, dp3[5 * (cap3 + 1) + cap3]);
    free(dp3);
    free(sel3);
    
    // Test case 4
    int w4[] = {3, 4, 5, 6};
    int v4[] = {4, 5, 6, 7};
    int cap4 = 10;
    int *dp4 = NULL;
    int *sel4 = (int *)malloc(4 * sizeof(int));
    knapsack(w4, v4, 4, cap4, &dp4, sel4);
    printf("%-6d %-6d %-12d\n", 4, cap4, dp4[4 * (cap4 + 1) + cap4]);
    free(dp4);
    free(sel4);

    printf("\nTime Complexity: O(n*W)\n");
    printf("Space Complexity: O(n*W) for the dp table\n");

    // Free main allocations
    free(dp);
    free(selected);

    return 0;
}
