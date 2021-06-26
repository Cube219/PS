#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

using ll = long long int;

struct Node
{
    int a, b;
};

int n, m;
Node cow[100001], gr[100001];
multiset<int> mp;
ll res = 0;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < n; ++i) {
        cin >> cow[i].a >> cow[i].b;
    }
    for(int i = 0; i < m; ++i) {
        cin >> gr[i].a >> gr[i].b;
    }
    sort(cow, cow + n, [](const Node& l, const Node& r) {
        if(l.b == r.b) return l.a > r.a;
        return l.b > r.b;
    });
    sort(gr, gr + m, [](const Node& l, const Node& r) {
        if(l.b == r.b) return l.a > r.a;
        return l.b > r.b;
    });

    int gridx = 0;
    for(int i = 0; i < n; ++i) {
        while(gridx < m && cow[i].b <= gr[gridx].b) {
            mp.insert(gr[gridx].a);
            gridx++;
        }
        auto it = mp.lower_bound(cow[i].a);
        if(it == mp.end()) {
            res = -1;
            break;
        }
        res += *it;
        mp.erase(it);
    }

    cout << res;

    return 0;
}
