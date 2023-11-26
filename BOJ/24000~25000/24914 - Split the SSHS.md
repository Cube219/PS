---
author: Cube219
created: 2022-11-29T14:56:02+09:00
updated: 2022-11-29T14:56:02+09:00
---

[24914번: Split the SSHS](https://www.acmicpc.net/problem/24914)

# 풀이

트리 구조이기 때문에 간선의 양 옆 정점에 같은 색깔의 다른 간선이 있으면 분리되거나 합쳐짐

각 정점마다 모든 색깔을 저장할 순 없으므로 set이나 map 사용
