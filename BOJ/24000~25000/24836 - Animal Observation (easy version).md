---
author: Cube219
created: 2023-12-26T17:01:10+09:00
updated: 2023-12-26T17:01:10+09:00
---

[24836번: Animal Observation (easy version)](https://www.acmicpc.net/problem/24836)

# 풀이

* 우리가 구하고자 하는 값은 2 x K의 영역이므로, 해당 영역의 왼쪽 위를 기준으로 값들을 미리 계산하고 생각해보자.
* 만약 i번째 날에 카메라를 둔다면, i-1번째에 둔 카메라의 위치에만 영향을 받는다. 이를 dp식으로 세워보면 `dp[i][j] = i번째날에 j위치에 카메라를 둘 때 최대값 = max(dp[i-1][k] + d[i][k] - 겹치는 영역), k=[0, m-k-1]` 이 된다.
* 이때, k가 최대 20이므로, 한 위치에 카메라를 두면 겹치는 영역은 2 * K - 1이므로 최대 39밖에 안 된다.
* 그러므로 k에서 모든 영역을 할 필요없이, 현재 위치에서 이전 dp가(왼쪽에 안 겹치는 경우 / 겹치는 경우 / 오른쪽에 안 겹치는 경우) 이 3경우만 확인하면 된다.
* 왼쪽/오른쪽에 안 겹치는 경우는, 미리 prefix sum 비슷하게 왼쪽/오른쪽에서 가장 큰 dp값을 전처리햐면 O(1)에 구할 수 있고, 겹치는 경우는 k를 이동시키면서 구하면 된다.
