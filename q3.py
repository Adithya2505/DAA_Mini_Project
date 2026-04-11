"""Question 3 – Dynamic Programming
You are given a set of n items, each with a weight wᵢ and a value vᵢ, and a knapsack
of capacity W. Design a dynamic programming algorithm to determine the
maximum value that can be obtained by selecting items such that the total weight
does not exceed W. Each item can be selected at most once (0/1 knapsack problem)."""

def knapsack(weights, values, W):
    n = len(weights)
    dp = [[0] * (W + 1) for _ in range(n + 1)]
    
    for i in range(1, n + 1):
        for w in range(W + 1):
            if weights[i-1] <= w:
                dp[i][w] = max(dp[i-1][w], dp[i-1][w - weights[i-1]] + values[i-1])
            else:
                dp[i][w] = dp[i-1][w]
    
    max_val = dp[n][W]
    
    selected = []
    w = W
    for i in range(n, 0, -1):
        if dp[i][w] != dp[i-1][w]:
            selected.append(i-1)
            w -= weights[i-1]
    
    return max_val, selected, dp

weights = [2, 3, 4, 5]
values = [3, 4, 5, 6]
W = 8
max_val, selected, dp = knapsack(weights, values, W)

print(f"Weights: {weights}")
print(f"Values:  {values}")
print(f"Capacity W = {W}")
print(f"Max Value: {max_val}")
print(f"Items selected (0-indexed): {selected}")
print(f"Total weight: {sum(weights[i] for i in selected)}")

print("\nDP Table:")
print("    ", end="")
for j in range(W+1):
    print(f"{j:3}", end="")
print()
for i in range(len(weights)+1):
    if i == 0:
        print(f" 0 |", end="")
    else:
        print(f" {i} |", end="")
    for j in range(W+1):
        print(f"{dp[i][j]:3}", end="")
    print()

print("\nExperimental Results:")
print(f"{'n':<6} {'W':<6} {'Max Value':<12}")
test_cases = [
    ([1,2,3], [6,10,12], 5),
    ([2,3,4,5], [3,4,5,6], 8),
    ([1,2,3,4,5], [1,6,10,16,15], 7),
    ([3,4,5,6], [4,5,6,7], 10),
]
for w_list, v_list, cap in test_cases:
    mv, _, _ = knapsack(w_list, v_list, cap)
    print(f"{len(w_list):<6} {cap:<6} {mv:<12}")

print("\nTime Complexity: O(n*W)")
print("Space Complexity: O(n*W) for the dp table")