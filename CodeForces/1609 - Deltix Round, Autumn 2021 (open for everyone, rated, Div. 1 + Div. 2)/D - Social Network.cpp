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


int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<int> par(n, 0), sz(n, 1);
    for(int i = 0; i < n; ++i) {
        par[i] = i;
    }

    auto find = [&](int v) {
        vector<int> st;
        while(par[v] != v) {
            st.push_back(v);
            v = par[v];
        }
        for(int t : st) par[t] = v;
        return v;
    };
    auto uni = [&](int a, int b) {
        int ar = find(a);
        int br = find(b);
        if(ar == br) return false;

        par[br] = ar;
        sz[ar] += sz[br];
        return true;
    };

    int remain = 0;
    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;

        bool ck = uni(a, b);
        if(ck == true) {
        } else {
            remain++;
        }

        vector<int> tmp;
        for(int j = 0; j < n; ++j) {
            if(par[j] != j) continue;
            tmp.push_back(sz[j]);
        }
        sort(tmp.begin(), tmp.end());
        ll res = 0;
        for(int j = 0; j <= remain; ++j) {
            if(tmp.size() == 0) break;
            res += tmp.back();
            tmp.pop_back();
        }

        cout << res - 1 << "\n";
    }

    return 0;
}
