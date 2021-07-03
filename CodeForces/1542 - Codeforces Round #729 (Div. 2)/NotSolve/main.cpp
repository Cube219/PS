#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll MOD = 998244353;

int n;
vector<pair<ll, int>> pos;
ll d[501];
int negsum[501];
ll res;
ll n2[501];
bool comp[501];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;

    n2[0] = 1;
    for(int i = 1; i <= n; ++i) {
        n2[i] = n2[i - 1] * 2;
        n2[i] %= MOD;
    }

    for(int i = 0; i < n; ++i) {
        char ch;
        cin >> ch;
        if(ch == '-') d[i] = -1;
        else {
            cin >> d[i];
            pos.push_back({ d[i], i });
        }
    }
    sort(pos.begin(), pos.end(), [](const auto& l, const auto& r) {
        if(l.first == r.first) return l.second < r.second;
        return l.first < r.first;
    });

    if(d[0] < 0) negsum[0] = 1;
    for(int i = 1; i < n; ++i) {
        negsum[i] = negsum[i - 1];
        if(d[i] < 0) negsum[i]++;
    }

    for(int i = 0; i < pos.size(); ++i) {
        int idx = pos[i].second;
        ll cnt = 0;
        int ns = 0;
        int ps = 0;
        for(int j = 0; j < pos[i].second; ++j) {
            if(comp[j] == true) ps++;
        }
        for(int j = pos[i].second + 1; j < n; ++j) {
            if(comp[j] == true) {
                ps++;
            } else {
                if(d[j] > 0) ns++;
            }
        }
        cnt += n2[ns + ps];
        cnt %= MOD;
        cnt *= n2[idx];
        cnt %= MOD;
        res += pos[i].first * cnt;
        res %= MOD;

        comp[pos[i].second] = true;
    }

    cout << res;

    return 0;
}
