---
author: Cube219
created: 2023-12-28T18:38:12+09:00
updated: 2023-12-28T18:38:12+09:00
---

[24812번: Substitution Mania!](https://www.acmicpc.net/problem/24812)

# 풀이

* 모든 순서로 하기에는 12!이라서 시간 안에 안 나온다. 12밖에 안 되니까 meet-in-the-middle로 접근해보자.
* 먼저 테이블 N개 중에 절반을 고르자. 그리고 절반 고른 것 끼리 모든 순서로 테이블을 만들자.
* 이것을 plaintext는 정방향으로, ciphertext는 역방향으로 변환해서 같은 것이 해당하는 순서이다. 이것을 map<string, vector<int>>로 빠르게 찾아주면 된다. 이러면 최대 12C6 * 6! * log(6!)이라 시간 안에 나온다.
* 여기서 plaintext와 ciphertext를 그대로 하면 시간 안에 안 나오는데, 생각해보면 중복되는 알파벳들은 어차피 같으므로 빼고 계산하면 된다.
