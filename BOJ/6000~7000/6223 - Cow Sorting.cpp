#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n;
int a[10001];
vector<int> vv;
bool finish[10001];

int getv(int v)
{
    return lower_bound(vv.begin(), vv.end(), v) - vv.begin();
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
        cin >> a[i];
        vv.push_back(a[i]);
    }
    sort(vv.begin(), vv.end());
    vv.erase(unique(vv.begin(), vv.end()), vv.end());
    for(int i = 0; i < n; ++i) {
        a[i] = getv(a[i]);
    }

    ll res = 0;
    vector<int> st;
    for(int i = 0; i < n; ++i) {
        if(finish[i] == true) continue;
        st.clear();
        int cur = i;
        do {
            st.push_back(cur);
            cur = a[cur];
        } while(cur != i);

        sort(st.begin(), st.end());
        finish[st[0]] = true;
        if(st.size() == 1) continue;

        ll r1 = 0;
        ll least = vv[st[0]];
        for(int j = 1; j < st.size(); ++j) {
            r1 += least + vv[st[j]];
            finish[st[j]] = true;
        }
        ll r2 = vv[0] + vv[st[0]];
        for(int j = 0; j < st.size(); ++j) {
            r2 += vv[0] + vv[st[j]];
        }
        res += min(r1, r2);
    }

    cout << res;

    return 0;
}
