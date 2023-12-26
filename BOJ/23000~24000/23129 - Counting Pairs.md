---
author: Cube219
created: 2023-12-17T12:31:48+09:00
updated: 2023-12-17T12:31:48+09:00
---

[23129번: Counting Pairs](https://www.acmicpc.net/problem/23129)

# 풀이

* a,b) pair일 때 값은 degree[a]+degree[b]-edge_num(a,b)가 된다. 일단 edge_num은 나중에 생각하자. 그러면 각 정점 pair의 degree 합의 개수는, degree 값의 개수를 담은 배열을 FFT로 convolution하면 된다.
* 이때 convolution 결과에는 a+b, b+a 둘 다 들어있기 때문에 중복을 제거해야 한다. 만약 값이 홀수라면 정확히 2배만큼 있으므로 2로 나누면 된다. 값이 짝수라면, v/2+v/2의 개수를 지우고, 2로 나누고, v/2의 경우의 수를 다시 더해주면 된다.
* 이제 edge_num을 처리해야 한다. edge들을 순회하면서, degree[a]+degree[b]에 있는 개수를 -1 해주고, degree[a]+degree[b]-edge_num(a,b)를 +1해주면 된다. 값이 좀 크므로, FFT를 할 때 정확도가 높아야 한다. 본인은 NTT 2개와 CRT를 이용했다(씽크스몰 문제처럼).
* ps: 쿼리의 값이 10^6이하인 점을 이용해, FFT없이 뒤에서부터 계산할 수도 있다.