---
author: Cube219
created: 2022-12-02T12:44:40+09:00
updated: 2022-12-02T12:44:40+09:00
---

[23872번: Paired Up](https://www.acmicpc.net/problem/23872)

# 풀이

unpaired를 중심으로 생각하자. 일단 인접한 두 소가 `K`보다 멀다면 독립된 영역으로 나눌 수 있다. 나눈 영역별로 생각하자.

`T=1`인 경우는 쉽다. 영역이 짝수개면 인접하게 연결해서 0이다. 홀수개면 한 마리의 소만 제외시킬 수 있다. 결국 홀수 개의 소로 제외시킬 수 있는데, 한 개를 제외하고 다 합칠 수 있기 때문이다.

소가 제외될 수 있는 조건은

1. 앞에 짝수 개의 소가 있음
2. 바로 앞/뒤의 소 거리가 `K`이하라서 서로 연결되는 경우)

둘 중 하나만 만족하면 된다. 만족하는 소 중 최솟값이 답이다.

`T=2`인경우는 제외를 최대한으로 해야 한다. `dp[i][j]` = `[0,i]`까지 소가 있고, `j`개의 소를 제외했을 때 최댓값이라 하자. 만약 `i`번째 소를 제외시키지 않는다면 `dp[i-1][j]`값을 가져오면 된다. 만약 제외시킨다면 위의 조건을 똑같이 적용해보자.

1. 1번 조건: 만약 앞에 짝수 개의 소가 있는 경우, 자신 포함해서 홀수 개의 소가 있으므로 홀수 개의 소를 제외해야 한다. 이는 (이전 dp에서 짝수 개 소 제외 중 최댓값 + `y[i]`)가 된다.
   여기서 이전 dp는 현재 위치에서 `K`보다 멀리 있어야 한다. 제외된 소끼리 연결이 안 되어야 하기 때문이다. 이 위치는 투포인터나 이분탐색으로 구하면 된다. 만약 앞에 홀수 개의 소가 있는 경우 짝/홀만 바꿔서 하면 된다.
2. 2번 조건: 바로 앞/뒤의 소 거리가 `K` 이하라면 앞에 소 개수가 짝/홀 상관이 없으므로 짝/홀 경우 다 위의 방법으로 업데이트 하면 된다. 양 끝에 있는 경우도 포함된다. 여기서 `j`는 짝수/홀수만 쓰는 것으로 바꿀 수 있고, $O(N)$ 또는 $O(NlogN)$에 가능해진다.