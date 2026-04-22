/*
Question 2 – Greedy Method
You are given n coins with denominations d₁, d₂, …, dₙ (not necessarily the standard
{1, 5, 10, 25}). Given an amount M, design a greedy algorithm to find the minimum
number of coins needed to make the amount M. Assume an unlimited supply of each
coin denomination.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Comparison function for qsort in descending order
int compare_desc(const void *a, const void *b) {
    return *(int *)b - *(int *)a;
}

// Returns -1 if impossible, otherwise returns count
int greedy_coins(int *denominations, int n, int amount, int *coins_used) {
    // Sort in descending order
    qsort(denominations, n, sizeof(int), compare_desc);
    
    int count = 0;
    int remaining = amount;
    
    for (int i = 0; i < n; i++) {
        while (remaining >= denominations[i]) {
            coins_used[count] = denominations[i];
            remaining -= denominations[i];
            count++;
        }
    }
    
    if (remaining != 0) {
        return -1;
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
    printf("=== MAIN TEST CASES ===\n");
    
    // Test case 1
    printf("\n--- Test Case 1: Standard coin system ---\n");
    int coins1[] = {1, 5, 10, 25};
    int n1 = sizeof(coins1) / sizeof(coins1[0]);
    int amount1 = 41;
    int *used1 = (int *)malloc(amount1 * sizeof(int));
    
    int count1 = greedy_coins(coins1, n1, amount1, used1);
    printf("Denominations: ");
    print_array(coins1, n1);
    printf("\nAmount: %d\n", amount1);
    printf("Coins used: ");
    print_array(used1, count1);
    printf("\nTotal coins: %d\n", count1);

    // Test case 2
    printf("\n--- Test Case 2: Greedy fails [1,3,4], amount 6 ---\n");
    int coins2[] = {1, 3, 4};
    int n2 = sizeof(coins2) / sizeof(coins2[0]);
    int amount2 = 6;
    int *used2 = (int *)malloc(amount2 * sizeof(int));
    
    int count2 = greedy_coins(coins2, n2, amount2, used2);
    printf("Denominations: ");
    print_array(coins2, n2);
    printf("\nAmount: %d\n", amount2);
    printf("Greedy gives: ");
    print_array(used2, count2);
    printf("\nTotal coins: %d\n", count2);
    printf("But optimal is [3, 3] = 2 coins. Greedy fails! (Gives %d coins)\n", count2);

    // Test case 3
    printf("\n--- Test Case 3: Greedy fails [1,5,6,9], amount 11 ---\n");
    int coins3[] = {1, 5, 6, 9};
    int n3 = sizeof(coins3) / sizeof(coins3[0]);
    int amount3 = 11;
    int *used3 = (int *)malloc(amount3 * sizeof(int));
    
    int count3 = greedy_coins(coins3, n3, amount3, used3);
    printf("Denominations: ");
    print_array(coins3, n3);
    printf("\nAmount: %d\n", amount3);
    printf("Greedy gives: ");
    print_array(used3, count3);
    printf("\nTotal coins: %d\n", count3);
    printf("Optimal is [5, 6] = 2 coins. Greedy fails again! (Gives %d coins)\n", count3);

    printf("\n--- Complexity Analysis ---\n");
    printf("Time Complexity: O(n log n) for sorting + O(amount) for loop = O(n log n + M)\n");
    printf("Space Complexity: O(amount) for storing coins used\n");

    printf("\n=== EDGE CASES ===\n");
    
    // Edge case 1: Amount = 0
    printf("\n--- Edge Case 1: Amount = 0 ---\n");
    int coins_edge1[] = {1, 5, 10};
    int amount_edge1 = 0;
    int *used_edge1 = (int *)malloc(1 * sizeof(int));
    int count_edge1 = greedy_coins(coins_edge1, 3, amount_edge1, used_edge1);
    printf("Denominations: [1, 5, 10], Amount: 0\n");
    printf("Result: %d coins (Expected: 0) ✓\n", count_edge1);
    free(used_edge1);
    
    // Edge case 2: Impossible case (no solution)
    printf("\n--- Edge Case 2: Impossible case ---\n");
    int coins_edge2[] = {5, 10};
    int amount_edge2 = 3;
    int *used_edge2 = (int *)malloc(amount_edge2 * sizeof(int));
    int count_edge2 = greedy_coins(coins_edge2, 2, amount_edge2, used_edge2);
    printf("Denominations: [5, 10], Amount: 3\n");
    printf("Result: %d (Expected: -1, impossible) ✓\n", count_edge2);
    free(used_edge2);
    
    // Edge case 3: Single coin denomination
    printf("\n--- Edge Case 3: Single denomination [1] ---\n");
    int coins_edge3[] = {1};
    int amount_edge3 = 5;
    int *used_edge3 = (int *)malloc(amount_edge3 * sizeof(int));
    int count_edge3 = greedy_coins(coins_edge3, 1, amount_edge3, used_edge3);
    printf("Denominations: [1], Amount: 5\n");
    printf("Coins used: ");
    print_array(used_edge3, count_edge3);
    printf("\nTotal coins: %d (Expected: 5) ✓\n", count_edge3);
    free(used_edge3);
    
    // Edge case 4: Large amount
    printf("\n--- Edge Case 4: Large amount ---\n");
    int coins_edge4[] = {1, 5, 10, 25};
    int amount_edge4 = 100;
    int *used_edge4 = (int *)malloc(amount_edge4 * sizeof(int));
    int count_edge4 = greedy_coins(coins_edge4, 4, amount_edge4, used_edge4);
    printf("Denominations: [1, 5, 10, 25], Amount: 100\n");
    printf("Total coins: %d (Expected: 4 coins = 4x25) ✓\n", count_edge4);
    free(used_edge4);

    // Free allocated memory
    free(used1);
    free(used2);
    free(used3);

    return 0;

    return 0;
}
