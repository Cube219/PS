---
author: Cube219
created: 2023-12-03T22:29:18+09:00
updated: 2023-12-03T22:29:18+09:00
---

[25317번: functionx](https://www.acmicpc.net/problem/25317)

# 풀이

* ax+b가 들어올 때 마다 -b/a의 해가 늘어나게 된다. set으로 해당 값을 저장해서 만약 해당 값이 나오면 0을 출력한다. 이제 부호만 판별하면 되므로, -INF에서 시작해보자. 해당 부호는 현재 차수/최고차항 계수의 부호 2가지로 결정이 된다.
* 그리고 -INF와 c 사이에 해들이 있는데, 해를 지날때마다 부호가 바뀌는 것을 알 수 있다. 이것을 ordered set이나 좌표압축+segment tree로 구하면 된다. 주의해야 할 점은 a가 0인 경운데, 이러면 차수가 늘어나지 않고 계수의 부호만 b에 의해 바뀐다. 만약 b도 0이라면 그냥 0이 된다.