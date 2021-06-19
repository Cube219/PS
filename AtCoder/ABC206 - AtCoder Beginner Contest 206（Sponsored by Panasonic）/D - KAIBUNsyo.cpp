#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, d[200001];
int p[200001];

int find(int v)
{
    vector<int> st;
    while(v != p[v]) {
        st.push_back(v);
        v = p[v];
    }
    for(int i = 0; i < st.size(); ++i) {
        p[st[i]] = v;
    }
    return v;
}

void uni(int a, int b)
{
    int ar = find(a);
    int br = find(b);
    if(ar == br) return;
    p[ar] = br;
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
        cin >> d[i];
        p[d[i]] = d[i];
    }

    int res = 0;
    for(int i = 0; i < n; ++i) {
        int j = n - i - 1;
        if(i >= j) break;

        int lv = find(d[i]);
        int rv = find(d[j]);
        if(lv == rv) continue;
        res++;
        uni(lv, rv);
    }

    cout << res;

    return 0;
}
