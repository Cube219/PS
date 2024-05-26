---
author: Cube219
created: 2023-12-24T16:32:56+09:00
updated: 2023-12-24T16:32:56+09:00
---

[18878번: Cereal](https://www.acmicpc.net/problem/18878)

# 풀이

* 소가 앞에서부터 지워지는 것이 아닌, 뒤에서부터 추가된다고 생각하자. 그러면 현재 맨 앞에 있는 소가 1번째 시리얼을 먹을텐데, 해당 시리얼을 먹고 있는 소가 있다면 우선순위에서 밀리게 된다. 그러면 밀려난 소를 기준으로 1,2번째 시리얼을 먹어보고, 우선순위를 밀 수 있으면 밀고...
* 이것을 반복하면 된다. 각 소마다 (1번째/2번째/탈락) 이렇게 3번만 방문하기 때문에 O(N)이다. 각 시리얼마다 현재 점유하고 있는 소의 번호를 기록해서 우선순위를 관리하면 된다. 만약 밀려난 소가 더이상 시리얼을 못 먹으면 먹은 소의 개수는 유지되고, 더이상 안 밀린다면 +1해주면 된다.