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

int n, m, s;
Node d[300001];
multiset<int> ain, bin, bout;
ll asum, bsum;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> s;
    for(int i = 0; i < n; ++i) {
        cin >> d[i].a >> d[i].b;
    }

    sort(d, d + n, [](const Node& l, const Node& r) {
        return l.a - l.b > r.a - r.b;
    });
    for(int i = 0; i < m; ++i) {
        ain.insert(d[i].a);
        asum += d[i].a;
    }
    for(int i = m; i < n; ++i) {
        if(bin.size() < s) {
            bin.insert(d[i].b);
            bsum += d[i].b;
        } else {
            auto it = bin.lower_bound(d[i].b);
            if(it != bin.begin()) {
                auto it2 = bin.begin();
                bsum -= *it2;
                bout.insert(*it2);
                bin.erase(it2);

                bin.insert(d[i].b);
                bsum += d[i].b;
            } else {
                bout.insert(d[i].b);
            }
        }
    }

    ll res = asum + bsum;
    for(int i = m; i + s < n; ++i) {
        // b에서 빼기
        {
            auto it = bout.find(d[i].b);
            if(it == bout.end()) {
                auto it2 = bin.find(d[i].b);
                bsum -= *it2;
                bin.erase(it2);

                auto it3 = prev(bout.end());
                bin.insert(*it3);
                bsum += *it3;
                bout.erase(it3);
            } else {
                bout.erase(it);
            }
        }

        // a에 넣기
        {
            auto it = ain.lower_bound(d[i].a);
            if(it != ain.begin()) {
                auto it2 = ain.begin();
                asum -= *it2;
                ain.erase(it2);

                ain.insert(d[i].a);
                asum += d[i].a;
            }
        }
        res = max(res, asum + bsum);
    }


    cout << res;

    return 0;
}
