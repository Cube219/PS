---
author: Cube219
created: 2022-11-30T20:45:43+09:00
updated: 2022-11-30T20:45:43+09:00
---

[24901번: Binary Game 2](https://www.acmicpc.net/problem/24901)

# 풀이

언어마다 주석 처리가 다른 것을 이용한다.

* C++/Swift: `#if` / `#endif`를 이용
* Java: `\u000a`가 개행으로 인식되어서 Java만의 주석 가능 ( `// \u000a /*` )
* Ruby: `#`이 한 줄 주석, `=begin` / `=end`가 여러줄 주석이고, `//`가 빈 regex 문자열임을 이용

이상하게 Swift에서

```
#if false
=end
#endif
```

이게 오류가 나서

```
#if false /*
=end
// # */
#endif
```

이렇게 추가로 주석을 쳤다.
