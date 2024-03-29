---
author: Cube219
created: 2023-11-26T22:36:43+09:00
updated: 2023-11-26T22:36:43+09:00
---

[16071번: Jigsaw Puzzle](https://www.acmicpc.net/problem/16071)

# 풀이

* 바깥 edge는 전부 0, 안쪽 edge는 전부 0보다 커야 하므로, 0의 edge 개수는 (너비+높이)*2가 되어야한다. 이것을 n의 약수들로 너비와 높이 후보를 구할 수 있다.
* 너비와 높이를 구했으면, 왼쪽 위 모서리로 쓸 조각을 선택한다. 만약 높이가 1이면 3개의 edge가 0인 조각을 선택하고, 2 이상이면 0인 edge가 연속해서 2개인 조각을 선택한다. 그다음 위쪽과 왼쪽 조각에 맞는 조각을 찾아서 끼우면 된다. 마지막으로 edge들이 맞게 들어갔는지 확인하면 된다.
* 여기서 주의할 점이 직사각형일 경우 너비와 높이를 바꿔서도 확인해봐야 한다. 또한 n=1인 경우도 주의하자.
* 풀이는 쉽지만 구현이 까다로운데, 나는 Block이라는 구조체에 각 edge의 번호를 담은 eg 배열을 (상/왼/하/오)순으로 넣고, rotate함수를 구현했다. 특정 edge인 조각을 찾는 것은 각 edge 번호를 가진 index들을 미리 배열에 저장해서 가져오는 방식으로 했다.
