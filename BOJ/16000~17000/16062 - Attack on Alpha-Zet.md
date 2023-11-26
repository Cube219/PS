---
author: Cube219
created: 2022-12-18T23:29:53+09:00
updated: 2022-12-18T23:29:53+09:00
---

[16074번: Mountaineers](https://www.acmicpc.net/problem/16074)

# 풀이

사이클이 없고, module간 경로는 하나밖에 없다는 것에서 이 구조는 트리임을 알 수 있다. 입력을 바탕으로 트리를 잘 만들고 경로를 따라 최단거리를 구하면 되고, 이는 sparse table을 이용한 LCA다.
