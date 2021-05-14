#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

ll l, a, b, t, r;
int n;
ll d[500001];
double dp[500001];
int rec[500001];
ll prelen, boostlen;

double gettime(ll src, ll dst)
{
    ll len = dst - src;

    if(len <= prelen) {
        return (double)len / a;
    } else if(len <= prelen + boostlen) {
        return t + (double)(len - prelen) / b;
    } else {
        return t + r + (double)(len - prelen - boostlen) / a;
    }
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> l >> a >> b >> t >> r;
    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
    }

    prelen = a * t;
    boostlen = b * r;

    dp[n - 1] = gettime(d[n - 1], l);
    rec[n - 1] = -1;
    for(int i = n - 2; i >= 0; --i) {
        ll pos = d[i];
        ll prepos = pos + prelen;
        ll boostpos = prepos + boostlen;

        dp[i] = dp[i + 1] + gettime(d[i], d[i + 1]);
        rec[i] = i + 1;
        auto it = upper_bound(d + i, d + n, boostpos);
        int idx = (it - 1) - d;
        if(i < idx) {
            double v = dp[idx] + gettime(d[i], d[idx]);
            if(dp[i] > v) {
                dp[i] = v;
                rec[i] = idx;
            }
        }
        idx = it - d;
        if(i < idx && idx < n) {
            double v = dp[idx] + gettime(d[i], d[idx]);
            if(dp[i] > v) {
                dp[i] = v;
                rec[i] = idx;
            }
        } else {
            double v = gettime(d[i], l);
            if(dp[i] > v) {
                dp[i] = v;
                rec[i] = -1;
            }
        }
    }

    vector<int> res;
    int cur = 0;
    if(n > 0) {
        while(cur != -1) {
            res.push_back(cur);
            cur = rec[cur];
        }
    }

    cout << res.size() << "\n";
    for(int i = 0; i < res.size(); ++i) {
        cout << res[i] << " ";
    }

    return 0;
}
