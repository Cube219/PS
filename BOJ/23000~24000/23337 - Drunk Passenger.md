---
author: Cube219
created: 2023-11-28T22:21:16+09:00
updated: 2023-11-28T22:21:16+09:00
---

[23337번: Drunk Passenger](https://www.acmicpc.net/problem/23337)

# 풀이

* dp[i] = i번째 사람이 자기자리에 못 앉을 확률이라 정의하면, dp[i]는 (1번째 사람이 자기자리에 앉음 + 2번째 사람이 자기자리에 앉음 + ...)로 구할 수 있다.
