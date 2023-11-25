n = int(input())

data = [
    [], # 0
    [ # 1
        [1, 1, 1],
        [2, 3, 5, 8],
        [1, 5, 6, 8, 9]
    ],
    [ # 2
        [2, 2, 2],
        [1, 3, 5, 8],
        [2, 5, 6, 8, 9]
    ],
    [ # 3
        [3, 3, 3],
        [1, 2, 5, 8],
        [3, 5, 6, 8, 9]
    ],
    [ # 4
        [4, 4, 4],
        [1, 2, 3, 4, 5, 8],
        [4, 5, 6, 8, 9]
    ],
    [ # 5
        [1, 2, 3, 8],
        [5, 5, 5],
        [1, 2, 3, 5, 6, 9]
    ],
    [ # 6
        [1, 2, 3, 9],
        [6, 6, 6],
        [1, 2, 3, 5, 6, 8]
    ],
    [ # 7
        [7, 7, 7],
        [1, 2, 3, 5, 7, 8],
        [5, 6, 7, 8, 9]
    ],
    [ # 8
        [1, 2, 3, 5],
        [5, 6, 9],
        [1, 2, 3, 6, 8, 9]
    ],
    [ # 9
        [1, 2, 3, 6],
        [5, 6, 8],
        [1, 2, 3, 5, 8, 9]
    ],
]

digits = []
nn = n
while nn > 0:
    digits.append(nn % 10)
    nn = nn // 10

digits.reverse()

res = -1
resCnt = -1

for i in range(2, 10) :
    cur = 0
    for digit in digits :
        has = False
        for arr in data[digit]:
            if len(arr) == i:
                cur += sum(arr)
                has = True
        
        if has == False :
            cur = 0
            break
        
        cur = cur * 10
    
    cur = cur // 10
    if cur != 0 and (res == -1 or res > cur) :
        res = cur
        resCnt = i

print(res, resCnt)
for i in range(resCnt):
    for digit in digits :
        for arr in data[digit]:
            if len(arr) == resCnt:
                print(arr[i], end="")
    print()
