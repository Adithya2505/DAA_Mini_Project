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
    // Test case 1
    int coins1[] = {1, 5, 10, 25};
    int n1 = sizeof(coins1) / sizeof(coins1[0]);
    int amount1 = 41;
    int *used1 = (int *)malloc(amount1 * sizeof(int));
    
    int count1 = greedy_coins(coins1, n1, amount1, used1);
    printf("Coins: ");
    print_array(coins1, n1);
    printf(", Amount: %d\n", amount1);
    printf("Coins used: ");
    print_array(used1, count1);
    printf(", Total: %d\n", count1);

    // Test case 2
    int coins2[] = {1, 3, 4};
    int n2 = sizeof(coins2) / sizeof(coins2[0]);
    int amount2 = 6;
    int *used2 = (int *)malloc(amount2 * sizeof(int));
    
    int count2 = greedy_coins(coins2, n2, amount2, used2);
    printf("\nCoins: ");
    print_array(coins2, n2);
    printf(", Amount: %d\n", amount2);
    printf("Greedy gives: ");
    print_array(used2, count2);
    printf(", Total: %d\n", count2);
    printf("But optimal is [3, 3] = 2 coins. Greedy fails here\n");

    // Test case 3
    int coins3[] = {1, 5, 6, 9};
    int n3 = sizeof(coins3) / sizeof(coins3[0]);
    int amount3 = 11;
    int *used3 = (int *)malloc(amount3 * sizeof(int));
    
    int count3 = greedy_coins(coins3, n3, amount3, used3);
    printf("\nCoins: ");
    print_array(coins3, n3);
    printf(", Amount: %d\n", amount3);
    printf("Greedy gives: ");
    print_array(used3, count3);
    printf(", Total: %d\n", count3);
    printf("Optimal is [5, 6] = 2 coins. Greedy fails again\n");

    printf("\nTime Complexity: O(n log n) for sorting + O(amount) for loop = O(n log n + M)\n");

    // Free allocated memory
    free(used1);
    free(used2);
    free(used3);

    return 0;
}
