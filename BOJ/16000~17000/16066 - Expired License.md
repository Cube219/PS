---
author: Cube219
created: 2022-12-18T23:35:14+09:00
updated: 2022-12-18T23:35:14+09:00
---

[16066번: Expired License](https://www.acmicpc.net/problem/16066)

# 풀이

정수로 바꾸어서 기약분수로 만들어 주면 되는 문제. 실수 오차 때문에 문자열로 받아서 정수로 변환해야 한다.

여기에 한 가지 예외가 있는데, 만약 분자와 분모가 같으면 1/1이 되는데, 1은 소수가 아니라서 2를 곱한 2/2가 답이 된다.
