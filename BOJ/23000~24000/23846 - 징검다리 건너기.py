import sys

[n, m] = map(int, input().split(' '))

dp = [[], []]
for i in range(n) :
    dp[0].append([2, 0])
    dp[1].append([0, 0])
    
for i in range(1, m) :
    sum = 0
    for j in range(n) :
        if (j > 0) :
            sum += dp[0][j - 1][0]
            sum += dp[0][j - 1][1] * 2
        dp[1][j][0] = sum
        dp[1][j][1] = dp[0][j][0] // 2
    dp[0], dp[1] = dp[1], dp[0]
    
res = 0
divisor = 1
for i in range(n - 1, -1, -1) :
    res += (dp[0][i][0] + dp[0][i][1]) * divisor
    divisor *= 3

print(f'{1 - (res / divisor):.10f}')
