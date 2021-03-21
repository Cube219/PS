#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int tNum;
int n;
ll a[100001];
ll pdt, ndt;
bool pos, inf;
ll m, c;

bool ck()
{
    ll cur = a[0];
    if(cur >= m) return false;
    for(int i = 1; i < n; ++i) {
        cur = (cur + c) % m;
        if(cur != a[i]) return false;
    }
    return true;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        pos = true;
        inf = false;
        cin >> n;
        for(int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        pdt = -1;
        ndt = 1;
        for(int i = 0; i < n - 1; ++i) {
            if(a[i] < a[i + 1]) {
                if(pdt == -1) {
                    pdt = a[i + 1] - a[i];
                } else if(pdt != a[i + 1] - a[i]) {
                    pos = false;
                    break;
                }
            } else {
                if(ndt == 1) {
                    ndt = a[i + 1] - a[i];
                } else if(ndt != a[i + 1] - a[i]) {
                    pos = false;
                    break;
                }
            }
        }

        if(pos == true) {
            if(pdt == -1 || ndt == 1) {
                inf = true;
            } else {
                ll km = 0;
                c = pdt;
                for(int i = 0; i < n - 1; ++i) {
                    if(a[i] > a[i + 1]) {
                        km = a[i] + pdt - a[i + 1];
                        break;
                    }
                }
                bool f = false;
                for(ll i = 1; i * i <= km; ++i) {
                    if(km % i != 0) continue;
                    m = km / i;
                    if(ck() == true) {
                        f = true;
                        break;
                    }
                    if(m <= pdt) break;
                }
                if(f == false) {
                    pos = false;
                }
            }
        }

        if(inf == true) {
            cout << "0\n";
        } else if(pos == false) {
            cout << "-1\n";
        } else {
            cout << m << " " << c << "\n";
        }
    }

    return 0;
}
