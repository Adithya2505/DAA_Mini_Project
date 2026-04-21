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
    printf("]\n");
}

int main() {
    int Arr[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    int n1 = sizeof(Arr) / sizeof(Arr[0]);
    
    printf("Array: ");
    print_array(Arr, n1);
    printf("Rotation points (D&C): %d\n", find_rotation_points(Arr, n1));
    printf("Rotation points (Linear): %d\n", linear_rotation_points(Arr, n1));

    int Arr2[] = {10, 9, 8, 7, 6};
    int n2 = sizeof(Arr2) / sizeof(Arr2[0]);
    
    printf("\nArray: ");
    print_array(Arr2, n2);
    printf("Rotation points (D&C): %d\n", find_rotation_points(Arr2, n2));
    printf("Rotation points (Linear): %d\n", linear_rotation_points(Arr2, n2));

    int Arr3[] = {1, 2, 3, 4, 5};
    int n3 = sizeof(Arr3) / sizeof(Arr3[0]);
    
    printf("\nArray: ");
    print_array(Arr3, n3);
    printf("Rotation points (D&C): %d\n", find_rotation_points(Arr3, n3));
    printf("Rotation points (Linear): %d\n", linear_rotation_points(Arr3, n3));

    printf("\nRecurrence Relation: T(n) = 2T(n/2) + O(1)\n");
    printf("By Master Theorem case 1: T(n) = O(n)\n");
    printf("Same as linear scan but D&C has more overhead\n");

    return 0;
}
