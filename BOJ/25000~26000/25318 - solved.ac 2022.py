from datetime import datetime

n = int(input())

d = []
for i in range(n) :
    date, time, score = input().split()
    date = date.replace('/', '-')
    t = datetime.fromisoformat(' '.join([date, time])).timestamp()
    d.append({ 't':t, 'score':int(score) })

if n == 0 :
    print('0')
    exit(0)

d.sort(key=lambda x : x['t'])

mxT = d[-1]['t']
p = []
for i in range(n) :
    p.append(max(0.5**((mxT - d[i]['t']) / 31536000), 0.9**(n-i-1)))

resu = 0
resd = 0
for i in range(n) :
    resu += p[i] * d[i]['score']
    resd += p[i]

res = resu / resd

print(round(res))
