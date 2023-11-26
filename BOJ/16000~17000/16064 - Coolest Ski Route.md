---
author: Cube219
created: 2022-12-18T23:34:20+09:00
updated: 2022-12-18T23:34:20+09:00
---

[16064번: Coolest Ski Route](https://www.acmicpc.net/problem/16064)

# 풀이

입력의 마지막에 같은 point로 가지 않는다고 하므로, 그래프는 DAG가 된다. 그러므로 위상정렬 + dp로 해당 위치의 최댓값을 갱신해주면 된다.
