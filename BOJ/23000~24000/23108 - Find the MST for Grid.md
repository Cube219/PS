---
author: Cube219
created: 2023-12-03T22:40:34+09:00
updated: 2023-12-03T22:40:34+09:00
---

[23108번: Find the MST for Grid](https://www.acmicpc.net/problem/23108)

# 풀이

* A,B,C,D 전부 non-decreasing이기 때문에 맨 왼쪽col/위쪽row는 연결하는 것이 무조건 이득이다. 만약 연결을 안 한다면 돌아서 연결되는 경우인데, 그럴 바에는 그냥 연결하는 것이 이득이기 때문이다.
* 이제 남은 노드들을 왼쪽 혹은 위쪽에 연결하면 된다. 문제는 N,M<=100000라서 그냥 순회할 수 없다. (i,j)일 때 연결하는 값은 min(A(i-1)+B(j), C(i)+D(j-1))이다. 만약 왼쪽 값을 선택해야 한다면 A(i-1)+B(j) <= C(i)+D(j-1)가 되고, i와 j를 각각 몰아주면 A(i-1)-C(i) <= -B(j)+D(j-1)이 된다.
* 이제 i를 고정시켜 각 행마다 살펴보자. B,D를 -B(j)+D(j-1)로 정렬하고, 해당 값이 A(i-1)-C(i)보다 작으면 부등식을 만족 안 하므로 오른쪽을, 크거나 같으면 왼쪽을 선택하는 경우다. 각각의 범위를 알았으므로, A와 C는 그냥 개수를 곱해주고, B와 D는 prefix sum으로 구해주면 된다.
