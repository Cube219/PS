#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll MOD = 1000000007;

struct Edge
{
    int a, b;
};

int n, m;
Edge d[2002];
ll res;
ll p3[2001];

int par[2001];
int find(int a)
{
    vector<int> st;
    while(a != par[a]) {
        st.push_back(a);
        a = par[a];
    }
    for(int i = 0; i < st.size(); ++i) {
        par[st[i]] = a;
    }
    return a;
}
void uni(int a, int b)
{
    int ar = find(a);
    int br = find(b);
    if(ar == br) return;
    par[br] = ar;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    p3[0] = 1;
    for(int i = 1; i < 2000; ++i) {
        p3[i] = (p3[i - 1] * 3) % MOD;
    }

    cin >> n >> m;
    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        d[i] = { a, b };
    }
    for(int i = 0; i < n; ++i) {
        par[i] = i;
    }

    for(int i = m - 1; i >= 0; --i) {
        int ar = find(d[i].a);
        int br = find(d[i].b);
        int str = find(0);
        int edr = find(n - 1);
        if((ar == str && br == edr) || (ar == edr && br == str)) {
            res = (res + p3[i]) % MOD;
        } else {
            uni(ar, br);
        }
    }

    cout << res;

    return 0;
}
