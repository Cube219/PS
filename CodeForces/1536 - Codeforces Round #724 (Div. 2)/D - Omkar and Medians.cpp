#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

using ll = long long int;

int tNum;
int n, d[200001];
multiset<int> mp;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        mp.clear();

        cin >> n;
        for(int i = 0; i < n; ++i) {
            cin >> d[i];
        }

        int lnum = 0, rnum = 0;
        bool pos = true;
        mp.insert(d[0]);
        auto cur = mp.begin();
        for(int i = 1; i < n; ++i) {
            if(*cur == d[i]) {
                lnum++; rnum++;
                continue;
            } else if(*cur < d[i]) {
                if(cur == prev(mp.end())) {
                    mp.insert(d[i]);
                    cur = next(cur);
                    rnum++;
                } else {
                    int nv = *next(cur);
                    if(nv < d[i]) {
                        pos = false;
                        break;
                    } else if(nv == d[i]) {
                        rnum += 2;
                        cur = next(cur);
                    } else {
                        mp.insert(d[i]);
                        cur = next(cur);
                        rnum++;
                    }
                }
            } else {
                if(cur == mp.begin()) {
                    mp.insert(d[i]);
                    cur = prev(cur);
                    lnum++;
                } else {
                    int pv = *prev(cur);
                    if(pv > d[i]) {
                        pos = false;
                        break;
                    } else if(pv == d[i]) {
                        lnum += 2;
                        cur = prev(cur);
                    } else {
                        mp.insert(d[i]);
                        cur = prev(cur);
                        lnum++;
                    }
                }
            }
        }

        if(pos == true) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
