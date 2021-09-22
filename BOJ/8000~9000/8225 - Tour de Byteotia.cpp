#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, m, k;
int par[1000001];

int find(int v)
{
    vector<int> st;
    while(par[v] != v) {
        st.push_back(v);
        v = par[v];
    }
    for(int a : st) {
        par[a] = v;
    }
    return v;
}

bool uni(int a, int b)
{
    int ar = find(a);
    int br = find(b);
    if(ar == br) return false;

    par[br] = ar;
    return true;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> k;
    k--;
    for(int i = 0; i < n; ++i) {
        par[i] = i;
    }

    vector<pair<int, int>> remain;
    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        if(a > k && b > k) uni(a, b);
        else remain.push_back({ a, b });
    }

    vector<pair<int, int>> res;
    for(auto p : remain) {
        if(uni(p.first, p.second) == false) res.push_back(p);
    }

    cout << res.size() << "\n";
    for(auto p : res) {
        cout << p.first + 1 << " " << p.second + 1 << "\n";
    }

    return 0;
}
