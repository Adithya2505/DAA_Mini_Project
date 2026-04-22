/*
Question 1 – Divide and Conquer
You are given an unsorted array A[0…n−1] of n distinct integers. A rotation point is
an index i where A[i] > A[i+1]. The array may have zero, one, or more rotation
points. Design a divide-and-conquer algorithm to find the number of rotation points
in the array.
*/

#include <stdio.h>
#include <stdlib.h>

int count_rotation_points(int *A, int left, int right) {
    if (right - left == 1) {  // only one adjacent pair to check
        return A[left] > A[right] ? 1 : 0;
    }
    if (left >= right) {  // single element, nothing to compare
        return 0;
    }
    
    int mid = (left + right) / 2;
    return count_rotation_points(A, left, mid) + count_rotation_points(A, mid, right);
}

int find_rotation_points(int *A, int n) {
    if (n <= 1) {
        return 0;
    }
    return count_rotation_points(A, 0, n - 1);
}

// linear scan for comparison
int linear_rotation_points(int *A, int n) {
    int count = 0;
    for (int i = 0; i < n - 1; i++) {
        if (A[i] > A[i + 1]) {
            count++;
        }
    }
    return count;
}

void print_array(int *A, int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", A[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]");
}

void print_rotation_details(int *A, int n, int dc_result, int linear_result) {
    printf("Array: ");
    print_array(A, n);
    printf("\n");
    printf("Rotation points (D&C): %d\n", dc_result);
    printf("Rotation points (Linear): %d\n", linear_result);
    printf("Rotation points positions: ");
    int first = 1;
    for (int i = 0; i < n - 1; i++) {
        if (A[i] > A[i + 1]) {
            if (!first) printf(", ");
            printf("[%d]", i);
            first = 0;
        }
    }
    if (first) printf("None");
    printf("\n");
}

int main() {
    printf("=== MAIN TEST CASES ===\n");
    
    // Test case 1
    printf("\n--- Test Case 1 ---\n");
    int Arr[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    int n1 = sizeof(Arr) / sizeof(Arr[0]);
    int dc1 = find_rotation_points(Arr, n1);
    int linear1 = linear_rotation_points(Arr, n1);
    print_rotation_details(Arr, n1, dc1, linear1);

    // Test case 2
    printf("\n--- Test Case 2 ---\n");
    int Arr2[] = {10, 9, 8, 7, 6};
    int n2 = sizeof(Arr2) / sizeof(Arr2[0]);
    int dc2 = find_rotation_points(Arr2, n2);
    int linear2 = linear_rotation_points(Arr2, n2);
    print_rotation_details(Arr2, n2, dc2, linear2);

    // Test case 3
    printf("\n--- Test Case 3 ---\n");
    int Arr3[] = {1, 2, 3, 4, 5};
    int n3 = sizeof(Arr3) / sizeof(Arr3[0]);
    int dc3 = find_rotation_points(Arr3, n3);
    int linear3 = linear_rotation_points(Arr3, n3);
    print_rotation_details(Arr3, n3, dc3, linear3);

    printf("\n--- Complexity Analysis ---\n");
    printf("Recurrence Relation: T(n) = 2T(n/2) + O(1)\n");
    printf("By Master Theorem case 1: T(n) = O(n)\n");
    printf("Same as linear scan but D&C has more overhead\n");

    printf("\n=== EDGE CASES ===\n");
    
    // Edge case 1: Single element
    printf("\n--- Edge Case 1: Single element ---\n");
    int edge1[] = {5};
    int edge1_dc = find_rotation_points(edge1, 1);
    int edge1_linear = linear_rotation_points(edge1, 1);
    print_rotation_details(edge1, 1, edge1_dc, edge1_linear);
    printf("Expected: 0 ✓\n");
    
    // Edge case 2: Two elements with rotation
    printf("\n--- Edge Case 2: Two elements with rotation ---\n");
    int edge2[] = {5, 2};
    int edge2_dc = find_rotation_points(edge2, 2);
    int edge2_linear = linear_rotation_points(edge2, 2);
    print_rotation_details(edge2, 2, edge2_dc, edge2_linear);
    printf("Expected: 1 ✓\n");
    
    // Edge case 3: Completely reversed (worst case for rotations)
    printf("\n--- Edge Case 3: Completely reversed ---\n");
    int edge3[] = {5, 4, 3, 2, 1};
    int edge3_dc = find_rotation_points(edge3, 5);
    int edge3_linear = linear_rotation_points(edge3, 5);
    print_rotation_details(edge3, 5, edge3_dc, edge3_linear);
    printf("Expected: 4 ✓\n");
    
    // Edge case 4: Alternating up-down
    printf("\n--- Edge Case 4: Alternating up-down ---\n");
    int edge4[] = {1, 5, 2, 4, 3};
    int edge4_dc = find_rotation_points(edge4, 5);
    int edge4_linear = linear_rotation_points(edge4, 5);
    print_rotation_details(edge4, 5, edge4_dc, edge4_linear);
    printf("Expected: 2 (at positions [1] and [3])\n");

    return 0;
}
