#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, m, a, b;
int d[101][8];
vector<int> border;
vector<ll> sum, tmp;
bool res;

bool ck2(ll k)
{
    sum.clear();
    sum.resize(m, 0);

    int cnt = 0;
    for(int i = 0; i < n; ++i) {
        int idx = 0;
        tmp.clear();
        tmp.resize(m, 0);
        for(int j = 0; j < m; ++j) {
            tmp[idx] += d[i][j];
            if(border[idx] == j) idx++;
        }

        bool f = false;
        for(int j = 0; j <= b; ++j) {
            if(sum[j] + tmp[j] > k) {
                f = true;
                break;
            }
        }

        if(f == true) {
            if(sum[0] == 0) return false;
            cnt++;
            sum.clear();
            sum.resize(m, 0);
            i--;
        } else {
            for(int j = 0; j <= b; ++j) {
                sum[j] += tmp[j];
            }
        }
    }
    if(cnt <= a) return true;
    else return false;
}

void bt(int idx, int cur, ll k)
{
    if(cur >= m) return;
    if(idx == b) {
        border.push_back(m);
        if(ck2(k) == true) {
            res = true;
        }
        border.pop_back();
        return;
    }

    for(int i = cur; i < m; ++i) {
        border.push_back(i);
        bt(idx + 1, i + 1, k);
        if(res == true) return;
        border.pop_back();
    }
}

bool ck(ll k)
{
    border.clear();
    res = false;
    bt(0, 0, k);

    return res;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> a >> b;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            cin >> d[i][j];
        }
    }

    ll l = 0, r = 80000000;
    while(l + 1 < r) {
        ll mid = (l + r) / 2;
        if(ck(mid) == true) {
            r = mid;
        } else {
            l = mid;
        }
    }

    cout << r;

    return 0;
}
