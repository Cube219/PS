#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int tNum;
int n;
vector<ll> uni[200001];
ll sum[200001];
ll d1[200001], d2[200001];
ll res[200001];

void process(vector<ll>& d)
{
    sort(d.begin(), d.end());
    int dn = d.size();
    sum[0] = d[0];
    for(int i = 1; i < dn; ++i) {
        sum[i] = sum[i - 1] + d[i];
    }

    for(int i = 1; i <= dn; ++i) {
        ll tmp = dn % i;
        res[i] += sum[dn - 1];
        if(tmp > 0) {
            res[i] -= sum[tmp - 1];
        }
    }
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n;
        for(int i = 0; i < n; ++i) {
            cin >> d1[i];
            d1[i]--;
            uni[i].clear();
            res[i + 1] = 0;
        }
        for(int i = 0; i < n; ++i) {
            cin >> d2[i];
            uni[d1[i]].push_back(d2[i]);
        }

        for(int i = 0; i < n; ++i) {
            if(uni[i].size() > 0) {
                process(uni[i]);
            }
        }

        for(int i = 1; i <= n; ++i) {
            cout << res[i] << " ";
        }
        cout << "\n";
    }

    return 0;
}
