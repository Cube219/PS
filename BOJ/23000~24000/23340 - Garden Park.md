---
author: Cube219
created: 2023-11-28T22:23:52+09:00
updated: 2023-11-28T22:23:52+09:00
---

[23340번: Garden Park](https://www.acmicpc.net/problem/23340)

# 풀이

* 트리 DP를 하면 되는데, subtree의 root로 up/down할 수 있는 개수를 구해주면 된다. 이때 갈 수 있는 경로는 자식들 중 간선의 cost가 작은 곳 -> 큰 곳 으로 가야하는데, 이는 정렬+누적합으로 빠르게 구할 수 있다.
