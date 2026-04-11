"""Question 1 – Divide and Conquer
You are given an unsorted array A[0…n−1] of n distinct integers. A rotation point is
an index i where A[i] > A[i+1]. The array may have zero, one, or more rotation
points. Design a divide-and-conquer algorithm to find the number of rotation points
in the array."""

def count_rotation_points(A, left, right):
    if right - left == 1: # only one adjacent pair to check
        return 1 if A[left] > A[right] else 0
    if left >= right: # single element, nothing to compare
        return 0
    
    mid = (left + right) // 2
    return count_rotation_points(A, left, mid) + count_rotation_points(A, mid, right)

def find_rotation_points(A):
    n = len(A)
    if n <= 1:
        return 0
    return count_rotation_points(A, 0, n - 1)

# linear scan for comparison
def linear_rotation_points(A):
    count = 0
    for i in range(len(A) - 1):
        if A[i] > A[i+1]:
            count += 1
    return count

Arr = [3, 1, 4, 1, 5, 9, 2, 6, 5, 3]
print("Array:", Arr)
print("Rotation points (D&C):", find_rotation_points(Arr))
print("Rotation points (Linear):", linear_rotation_points(Arr))

Arr2 = [10, 9, 8, 7, 6]
print("\nArray:", Arr2)
print("Rotation points (D&C):", find_rotation_points(Arr2))
print("Rotation points (Linear):", linear_rotation_points(Arr2))

Arr3 = [1, 2, 3, 4, 5]
print("\nArray:", Arr3)
print("Rotation points (D&C):", find_rotation_points(Arr3))
print("Rotation points (Linear):", linear_rotation_points(Arr3))

print("\nRecurrence Relation: T(n) = 2T(n/2) + O(1)")
print("By Master Theorem case 1: T(n) = O(n)")
print("Same as linear scan but D&C has more overhead")