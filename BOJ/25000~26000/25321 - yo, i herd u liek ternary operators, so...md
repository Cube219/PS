---
author: Cube219
created: 2023-12-03T22:32:11+09:00
updated: 2023-12-03T22:32:11+09:00
---

[25321번: yo, i herd u liek ternary operators, so..](https://www.acmicpc.net/problem/25321)

# 풀이

* 일단 알파벳은 경우의 수를 세는데 필요없으므로 빼고 생각하자. 그리고 ?와 :를 각각 (,)인 괄호로 생각해보자. 예제 2처럼 (()) 중첩된 경우에는 순서를 바꿀 수 없으므로 1이다. 예제 1처럼 ()() 인 경우에는 2이다. ()()()인 경우에는 해보면 5임을 알 수 있다.
* a3=5인 것에서 이것이 카탈란 수라는 것을 짐작할 수 있고, 실제로 맞다 (괄호의 실행 순서를 binary operator의 실행 순서라고 생각하면 된다.). 카탈란 수는 미리 구해놓고, 스택을 이용해 계산하면 된다.
