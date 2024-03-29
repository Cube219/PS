---
author: Cube219
created: 2023-12-26T22:34:14+09:00
updated: 2023-12-26T22:34:14+09:00
---

[23949번: Shifts](https://www.acmicpc.net/problem/23949)

# 풀이

* N이 작지만 모든 경우의 수를 돌려보면 3^20으로 너무 많다. N이 작으므로 meet-in-the-middle을 생각해보자.
* 그룹을 나누고, 왼쪽을 브루트 포스로 돌리면 각 경우마다 부족한 a와 b의 값이 나오고, 이것이 오른쪽 경우중에 a와 b둘다 크거나 같은 경우의 수를 계산하면 된다.
* 여러 방법이 있겠지만, 본인은 2차원 prefix sum을 이용했다. 이러면 전처리만 하면 O(1)에 구할 수 있다.
* 그룹의 크기를 s1, s2라고 했을 때, 전자는 O(3^s1), 후자는 전처리에 O((3^s2)^2)이 걸린다. 두 시간복잡도를 합쳤을 때 가장 작은 크기를 선택하면 된다.