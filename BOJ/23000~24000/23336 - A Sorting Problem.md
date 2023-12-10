---
author: Cube219
created: 2023-11-28T22:20:33+09:00
updated: 2023-11-28T22:20:33+09:00
---

[23336번: A Sorting Problem](https://www.acmicpc.net/problem/23336)

# 풀이

* 결론적으로는 inversion의 개수를 출력하면 된다. 왜 되는가? 차이가 1 나는 두 수만 swap을 하기 때문에 그 두 수 말고는 다른 수들은 inversion이 바뀌지 않는다. 두 수는 (서로 inversion 바뀜 + 큰 수는 1 감소)가 된다. 따라서 inversion 총 개수 만큼만 바꿔주면 된다.
* inversion은 세그먼트 트리로 쉽게 구현 가능하다.
