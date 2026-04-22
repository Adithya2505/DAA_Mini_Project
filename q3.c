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

void print_dp_table(int *dp, int n, int W) {
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
}

int main() {
    // Define main example data (FIX: Added missing variable declarations)
    int weights[] = {2, 3, 4, 5};
    int values[] = {3, 4, 5, 6};
    int n = 4;
    int W = 8;
    
    int *dp = NULL;
    int *selected = (int *)malloc(n * sizeof(int));
    
    int count = knapsack(weights, values, n, W, &dp, selected);
    int max_val = dp[n * (W + 1) + W];
    
    printf("=== MAIN EXAMPLE ===\n\n");
    printf("Weights: ");
    print_array(weights, n);
    printf("\nValues:  ");
    print_array(values, n);
    printf("\nCapacity W = %d\n", W);
    printf("Max Value: %d\n", max_val);
    printf("Items selected (0-indexed): ");
    print_array(selected, count);
    printf("\n");
    
    int total_weight = 0;
    for (int i = 0; i < count; i++) {
        total_weight += weights[selected[i]];
    }
    printf("Total weight: %d\n", total_weight);
    print_dp_table(dp, n, W);

    printf("\n\n=== TEST CASES WITH DP TABLES ===\n");
    
    // Test case 1
    printf("\n--- Test Case 1 ---\n");
    int w1[] = {1, 2, 3};
    int v1[] = {6, 10, 12};
    int cap1 = 5;
    int *dp1 = NULL;
    int *sel1 = (int *)malloc(3 * sizeof(int));
    int count1 = knapsack(w1, v1, 3, cap1, &dp1, sel1);
    printf("Weights: ");
    print_array(w1, 3);
    printf("\nValues:  ");
    print_array(v1, 3);
    printf("\nCapacity W = %d\n", cap1);
    printf("Max Value: %d\n", dp1[3 * (cap1 + 1) + cap1]);
    printf("Items selected (0-indexed): ");
    print_array(sel1, count1);
    printf("\n");
    print_dp_table(dp1, 3, cap1);
    free(dp1);
    free(sel1);
    
    // Test case 2
    printf("\n--- Test Case 2 ---\n");
    int w2[] = {2, 3, 4, 5};
    int v2[] = {3, 4, 5, 6};
    int cap2 = 8;
    int *dp2 = NULL;
    int *sel2 = (int *)malloc(4 * sizeof(int));
    int count2 = knapsack(w2, v2, 4, cap2, &dp2, sel2);
    printf("Weights: ");
    print_array(w2, 4);
    printf("\nValues:  ");
    print_array(v2, 4);
    printf("\nCapacity W = %d\n", cap2);
    printf("Max Value: %d\n", dp2[4 * (cap2 + 1) + cap2]);
    printf("Items selected (0-indexed): ");
    print_array(sel2, count2);
    printf("\n");
    print_dp_table(dp2, 4, cap2);
    free(dp2);
    free(sel2);
    
    // Test case 3
    printf("\n--- Test Case 3 ---\n");
    int w3[] = {1, 2, 3, 4, 5};
    int v3[] = {1, 6, 10, 16, 15};
    int cap3 = 7;
    int *dp3 = NULL;
    int *sel3 = (int *)malloc(5 * sizeof(int));
    int count3 = knapsack(w3, v3, 5, cap3, &dp3, sel3);
    printf("Weights: ");
    print_array(w3, 5);
    printf("\nValues:  ");
    print_array(v3, 5);
    printf("\nCapacity W = %d\n", cap3);
    printf("Max Value: %d\n", dp3[5 * (cap3 + 1) + cap3]);
    printf("Items selected (0-indexed): ");
    print_array(sel3, count3);
    printf("\n");
    print_dp_table(dp3, 5, cap3);
    free(dp3);
    free(sel3);
    
    // Test case 4
    printf("\n--- Test Case 4 ---\n");
    int w4[] = {3, 4, 5, 6};
    int v4[] = {4, 5, 6, 7};
    int cap4 = 10;
    int *dp4 = NULL;
    int *sel4 = (int *)malloc(4 * sizeof(int));
    int count4 = knapsack(w4, v4, 4, cap4, &dp4, sel4);
    printf("Weights: ");
    print_array(w4, 4);
    printf("\nValues:  ");
    print_array(v4, 4);
    printf("\nCapacity W = %d\n", cap4);
    printf("Max Value: %d\n", dp4[4 * (cap4 + 1) + cap4]);
    printf("Items selected (0-indexed): ");
    print_array(sel4, count4);
    printf("\n");
    print_dp_table(dp4, 4, cap4);
    free(dp4);
    free(sel4);

    printf("\n--- Complexity Analysis ---\n");
    printf("Time Complexity: O(n*W)\n");
    printf("Space Complexity: O(n*W) for the dp table\n");

    printf("\n=== EDGE CASES ===\n");
    
    // Edge case 1: Capacity W = 0
    printf("\n--- Edge Case 1: Capacity W = 0 ---\n");
    int w_edge1[] = {2, 3, 4};
    int v_edge1[] = {3, 4, 5};
    int cap_edge1 = 0;
    int *dp_edge1 = NULL;
    int *sel_edge1 = (int *)malloc(3 * sizeof(int));
    knapsack(w_edge1, v_edge1, 3, cap_edge1, &dp_edge1, sel_edge1);  // FIX: Removed unused variable
    printf("Max Value: %d (Expected: 0)\n", dp_edge1[3 * (cap_edge1 + 1) + cap_edge1]);
    print_dp_table(dp_edge1, 3, cap_edge1);
    free(dp_edge1);
    free(sel_edge1);
    
    // Edge case 2: All items too heavy
    printf("\n--- Edge Case 2: All items too heavy ---\n");
    int w_edge2[] = {10, 15, 20};
    int v_edge2[] = {100, 150, 200};
    int cap_edge2 = 5;
    int *dp_edge2 = NULL;
    int *sel_edge2 = (int *)malloc(3 * sizeof(int));
    knapsack(w_edge2, v_edge2, 3, cap_edge2, &dp_edge2, sel_edge2);  // FIX: Removed unused variable
    printf("Weights: [10, 15, 20], Values: [100, 150, 200], Capacity: 5\n");
    printf("Max Value: %d (Expected: 0)\n", dp_edge2[3 * (cap_edge2 + 1) + cap_edge2]);
    print_dp_table(dp_edge2, 3, cap_edge2);
    free(dp_edge2);
    free(sel_edge2);
    
    // Edge case 3: Single item fits perfectly
    printf("\n--- Edge Case 3: Single item fits perfectly ---\n");
    int w_edge3[] = {5};
    int v_edge3[] = {50};
    int cap_edge3 = 5;
    int *dp_edge3 = NULL;
    int *sel_edge3 = (int *)malloc(1 * sizeof(int));
    int count_edge3 = knapsack(w_edge3, v_edge3, 1, cap_edge3, &dp_edge3, sel_edge3);
    printf("Max Value: %d (Expected: 50)\n", dp_edge3[1 * (cap_edge3 + 1) + cap_edge3]);
    printf("Items selected: ");
    print_array(sel_edge3, count_edge3);
    printf("\n");
    print_dp_table(dp_edge3, 1, cap_edge3);
    free(dp_edge3);
    free(sel_edge3);

    // Free main allocations
    free(dp);
    free(selected);

    return 0;
}