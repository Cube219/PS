#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

using ll = long long int;

struct Node
{
    ll x;
    ll v;
};
struct QNode
{
    ll dis;
    ll v;
    int idx1;
    int idx2;
};
bool operator<(const QNode& l, const QNode& r)
{
    ll lv = (ll)l.dis * r.v;
    ll rv = (ll)r.dis * l.v;
    return abs(lv) > abs(rv);
}

int n;
Node d[100005];
bool isdie[100005];
int l[100005], r[100005];
priority_queue<QNode> pq;

void addpq(int a, int b)
{
    if(isdie[a] == true || isdie[b] == true) {
        return;
    }
    QNode tmp;
    tmp.dis = d[b].x - d[a].x;
    tmp.idx1 = a;
    tmp.idx2 = b;
    if(d[a].v <= 0 && d[b].v >= 0) return;
    if(d[a].v >= 0 && d[b].v <= 0) {
        tmp.v = abs(d[a].v) + abs(d[b].v);
    } else if(d[a].v > d[b].v) {
        tmp.v = abs(d[b].v - d[a].v);
    } else {
        return;
    }
    pq.push(tmp);
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 1; i <= n; ++i) {
        int x, v;
        cin >> x >> v;
        d[i] = { x, v };
        l[i] = i - 1;
        r[i] = i + 1;
    }
    isdie[0] = true;
    l[1] = 0;
    r[n] = 0;
    for(int i = 1; i <= n - 1; ++i) {
        addpq(i, i + 1);
    }
    while(pq.empty() == false) {
        QNode cur = pq.top();
        pq.pop();
        if(isdie[cur.idx1] == true || isdie[cur.idx2] == true) continue;
        isdie[cur.idx1] = true;
        isdie[cur.idx2] = true;
        r[l[cur.idx1]] = r[cur.idx2];
        l[r[cur.idx2]] = l[cur.idx1];
        addpq(l[cur.idx1], r[cur.idx2]);
    }

    vector<int> res;
    for(int i = 1; i <= n; ++i) {
        if(isdie[i] == false) res.push_back(i);
    }
    cout << res.size() << "\n";
    for(int i = 0; i < res.size(); ++i) {
        cout << res[i] << " ";
    }

    return 0;
}
