---
author: Cube219
created: 2024-10-03T17:44:23+09:00
number: BOJ32188
---

[32188번: Portal Game](https://www.acmicpc.net/problem/32188)

> 출처: [제 1회 2024 디미고 프로그래밍 챌린지](https://www.acmicpc.net/category/detail/4273) E번

# 풀이

* 일자인 그래프에 포탈이 있는 것으로 생각할 수 있다.
* 1초후 이동을 간선의 비용이 1 / 0초후 이동을 간선의 비용이 0인 그래프로 생각할 수 있다.
* 이는 0-1 BFS 최단경로로, Dijkstra나 deque를 이용해 풀 수 있다.
