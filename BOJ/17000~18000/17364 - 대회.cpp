#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

using ll = long long int;

struct Node
{
    int st, ed;
};

int n, k;
Node d[100001];
multiset<int> mp;


int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;
    for(int i = 0; i < n; ++i) {
        cin >> d[i].st >> d[i].ed;
    }
    sort(d, d + n, [](const Node& l, const Node& r) {
        if(l.ed == r.ed) return l.st < r.st;
        return l.ed < r.ed;
    });

    for(int i = 0; i < k - 1; ++i) {
        mp.insert(-1);
    }

    int res = 0;
    int myend = -1;
    for(int i = 0; i < n; ++i) {
        if(myend >= d[i].st) continue;

        auto it = mp.lower_bound(d[i].st);
        if(it == mp.begin()) {
            myend = d[i].ed;
            res++;
        } else {
            --it;
            mp.erase(it);
            mp.insert(d[i].ed);
        }
    }

    cout << res;

    return 0;
}
