#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

using ll = long long int;

ll n;
int d[300001];
map<int, int> mp;

void add(int v)
{
    auto it = mp.find(v);
    if(it == mp.end()) {
        it = mp.insert({ v, 0 }).first;
    }
    it->second++;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        add(a);
    }

    ll res = n * (n - 1) / 2;
    for(auto& it : mp) {
        if(it.second > 1) {
            ll v = it.second;
            res -= v * (v - 1) / 2;
        }
    }

    cout << res;

    return 0;
}
