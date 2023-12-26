---
author: Cube219
created: 2023-12-17T17:53:28+09:00
updated: 2023-12-17T17:53:28+09:00
---

[19608번: Searching for Strings](https://www.acmicpc.net/problem/19608)

# 풀이

* N의 순열이 되려면, 알파벳 개수가 전부 같으면 된다. 이것은 투 포인터로 H를 훑으면 해당하는 subarray들을 구할 수 있다. 이제 이 subarray의 distinct개수를 세주면 되는데, 해싱으로 처리하는 것이 가장 쉽다.