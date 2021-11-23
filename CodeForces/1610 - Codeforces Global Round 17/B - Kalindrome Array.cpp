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

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        int n;
        cin >> n;
        vector<int> a(n);
        for(int& v : a) cin >> v;

        int l = 0, r = n - 1;
        while(l < r && a[l] == a[r]) {
            l++;
            r--;
        }
        if(l >= r) {
            cout << "YES\n";
            continue;
        }

        int ll = l, rr = r;
        // delete d[l]
        int v = a[l];
        while(ll < rr) {
            if(a[ll] == a[rr]) {
                ll++;
                rr--;
                continue;
            } else if(a[ll] == v) {
                ll++;
                continue;
            }else if(a[rr] == v) {
                rr--;
                continue;
            } else {
                break;
            }
        }
        if(ll >= rr) {
            cout << "YES\n";
            continue;
        }

        // delete d[r]
        ll = l;
        rr = r;
        v = a[r];

        while(ll < rr) {
            if(a[ll] == a[rr]) {
                ll++;
                rr--;
                continue;
            } else if(a[ll] == v) {
                ll++;
                continue;
            } else if(a[rr] == v) {
                rr--;
                continue;
            } else {
                break;
            }
        }
        if(ll >= rr) {
            cout << "YES\n";
            continue;
        }

        cout << "NO\n";
    }

    return 0;
}
