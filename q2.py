"""Question 2 – Greedy Method
You are given n coins with denominations d₁, d₂, …, dₙ (not necessarily the standard
{1, 5, 10, 25}). Given an amount M, design a greedy algorithm to find the minimum
number of coins needed to make the amount M. Assume an unlimited supply of each
coin denomination."""

def greedy_coins(denominations, amount):
    denominations.sort(reverse=True)
    coins_used = []
    remaining = amount
    
    for coin in denominations:
        while remaining >= coin:
            coins_used.append(coin)
            remaining -= coin
    
    if remaining != 0:
        return -1, []
    
    return len(coins_used), coins_used

coins1 = [1, 5, 10, 25]
amount1 = 41
count, used = greedy_coins(coins1, amount1)
print(f"Coins: {coins1}, Amount: {amount1}")
print(f"Coins used: {used}, Total: {count}")

coins2 = [1, 3, 4]
amount2 = 6
count2, used2 = greedy_coins(coins2, amount2)
print(f"\nCoins: {coins2}, Amount: {amount2}")
print(f"Greedy gives: {used2}, Total: {count2}")
print("But optimal is [3, 3] = 2 coins. Greedy fails here")

coins3 = [1, 5, 6, 9]
amount3 = 11
count3, used3 = greedy_coins(coins3, amount3)
print(f"\nCoins: {coins3}, Amount: {amount3}")
print(f"Greedy gives: {used3}, Total: {count3}")
print("Optimal is [5, 6] = 2 coins. Greedy fails again")

print("\nTime Complexity: O(n log n) for sorting + O(amount) for loop = O(n log n + M)")