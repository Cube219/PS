#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
using namespace std;

using ll = long long int;

struct Node
{
    ll a;
    ll cnt;
    ll idx;
};

int k;
ll n, m;
multimap<ll, Node> mp;
ll a[100001];
ll res[100001];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> k >> n >> m;
    for(int i = 0; i < k; ++i) {
        cin >> a[i];
    }
    for(int i = 1; i < k; ++i) {
        mp.insert({ -a[i] * m, {a[i] * m, 0, i} });
    }
    mp.insert({ n * m - a[0] * m, {a[0] * m, m, 0} });
    while(1) {
        auto stit = mp.begin();
        auto edit = mp.end();
        --edit;
        auto st = stit->second;
        auto ed = edit->second;

        ll gap = (n * ed.cnt - ed.a) - (n * st.cnt - st.a);
        gap /= 2;
        if(gap % n > n / 2) gap += n;
        gap /= n;
        if(gap == 0) break;
        // cout << gap << "\n";
        ed.cnt -= gap;
        st.cnt += gap;
        mp.erase(stit);
        mp.erase(edit);
        mp.insert({n * st.cnt - st.a, st });
        mp.insert({n * ed.cnt - ed.a, ed });
    }

    for(auto it : mp) {
        res[it.second.idx] = it.second.cnt;
    }

    for(int i = 0; i < k; ++i) {
        cout << res[i] << " ";
    }

    return 0;
}
