---
author: Cube219
created: 2023-11-26T22:40:31+09:00
updated: 2023-11-26T22:40:31+09:00
---

[16074번: Mountaineers](https://www.acmicpc.net/problem/16074)

# 풀이

* 딱 보면 PBS를 쓰고 싶게 생겼다. 각 쿼리마다 최대 높이를 이분탐색으로 고정시키자. 그러면 A에서 B로 가는 경우는 disjoint set으로 빠르게 구할 수 있다. 여기서 시작-도착이 같은 경우만 예외처리하면 된다. 다르게는 smaller-to-larger로도 풀 수 있다고 한다.
