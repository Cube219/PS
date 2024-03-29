---
author: Cube219
created: 2022-12-02T12:34:38+09:00
updated: 2022-12-02T12:34:38+09:00
---

[16791번: Bubble Sort 2](https://www.acmicpc.net/problem/16791)

# 풀이

각 원소를 기준으로 생각해보면, 횟수는 자신보다 앞(왼쪽)에 있는 큰 수의 개수가 된다. 앞에 있는 큰 수가 자신을 넘어가면 자동으로 자신의 자리로 가기 때문이다. 그러면 각 원소들의 값의 최댓값이 답이다. 다만 이 구조로는 쿼리를 빠르게 처리하기가 힘들다.

생각하기 어려운데... 위 값은 (현재 위치-정렬된 위치)로 바꿀 수 있다. 정렬되어 있으면, 앞에 있는 수는 자신보다 모두 작은 수가 된다. 여기서 뒤로 밀려났다는 것은 내 앞에 큰 수가 끼어든 것이고, 그러면 위치 차이를 앞에 있는 큰 수의 개수라고 생각할 수 있다.

(물론 작은 수가 뒤로 가고 큰 수가 끼어들었다면 위치는 그대로지만, 어차피 최댓값을 찾는 것이기 때문에 뒤로 간 작은 수를 기준으로 구하면 된다.) 중복되는 값은 맨 뒤 값을 기준으로 하면 된다. 같은 값이면 뒤로 갈수록 차이가 커지거나 같기 때문이다.

정렬된 위치는 (자신보다 작거나 같은 개수 - 1)로 바꿀 수 있다. 작거나 같은 개수는 좌표압축 후 값을 index로 하는 lazy segment tree를 사용하면 된다. 여기에 set을 이용해 같은 값들을 처리해주면 된다.
