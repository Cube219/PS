---
author: Cube219
created: 2022-11-29T15:02:56+09:00
updated: 2022-11-29T15:02:56+09:00
---

[10663번: Stack Maze](https://www.acmicpc.net/problem/10663)

# 풀이

$dp[sx][sy][ex][ey]$로 식 세우고 모든 영역에 대해서 dp 돌리면 됨

aAbB처럼 연속된 경우가 문젠데 이는 pivot을 무조건 알파벳이 있는 곳만 잡아서 계산해주면 시간을 줄일 수 있음

다만 대소문자 차이로 pair 계산할 때 N이랑 ,이랑 pair가 됨을 주의

저것때문에 맞왜틀;
