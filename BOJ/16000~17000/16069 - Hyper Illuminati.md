---
author: Cube219
created: 2022-12-18T23:37:48+09:00
updated: 2022-12-18T23:37:48+09:00
---

[16069번: Hyper Illuminati](https://www.acmicpc.net/problem/16069)

# 풀이

n과 s를 전부 다 해보면 된다.

n은 2번째 층에서 2^(n-1)을 하므로 대충 60정도만 돌리고, s는 돌리다가 m보다 크면 빠져나가는 식으로 하면 된다.
