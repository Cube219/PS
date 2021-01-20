#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

ll g;
vector<ll> d;
vector<ll> dsq;
vector<ll> res;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> g;
    d.push_back(1);
    dsq.push_back(1);
    for(ll i = 2; ; i++) {
        ll t = i * i;
        if(t - d.back() > g) break;
        d.push_back(t);
        dsq.push_back(i);
    }

    int st = 0;
    int ed = 0;
    ll cur = 0;
    while(1) {
        if(cur >= g) {
            st++;
            cur = d[ed - 1] - d[st];
        } else {
            if(ed == d.size()) break;
            ed++;
            cur = d[ed - 1] - d[st];
        }
        if(cur == g) {
            res.push_back(dsq[ed - 1]);
        }
    }

    if(res.size() == 0) cout << "-1";
    else {
        for(int i = 0; i < res.size(); i++) {
            cout << res[i] << "\n";
        }
    }

    return 0;
}
