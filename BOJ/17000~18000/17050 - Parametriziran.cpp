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

int n, m;
ll res;
char str[500001][10];
map<ll, int> num[64];

int mask;
string tmpstr;

ll pw(int a)
{
    ll ret = 1;
    for(int i = 0; i < a; ++i) {
        ret *= 27;
    }
    return ret;
}

ll p(int idx, ll v)
{
    if(idx == tmpstr.size()) {
        auto it = num[mask].find(v);
        if(it != num[mask].end()) return it->second;
        else return 0;
    }

    ll ret = 0;
    // normal
    ll tv = pw(idx) * (ll)(tmpstr[idx] - 'a');
    ret += p(idx + 1, v + tv);

    // ?
    tv = pw(idx) * 26;
    ret += p(idx + 1, v + tv);
    return ret;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < n; ++i) {
        cin >> str[i];

        mask = 0;
        tmpstr.clear();
        for(int j = 0; j < m; ++j) {
            if(str[i][j] == '?') mask |= 1 << j;
            else tmpstr.push_back(str[i][j]);
        }
        res += p(0, 0);

        for(int j = 0; j < 1 << m; j++) {
            int cnt = 0;
            ll v = 0;
            for(int k = 0; k < m; ++k) {
                if((j & (1 << k)) > 0) continue;
                ll tmp;
                if(str[i][k] == '?') tmp = 26;
                else tmp = str[i][k] - 'a';
                v = v + tmp * pw(cnt);
                cnt++;
            }
            auto it = num[j].find(v);
            if(it == num[j].end()) {
                num[j].insert({ v, 1 });
            } else {
                it->second++;
            }
        }
    }

    cout << res;

    return 0;
}
