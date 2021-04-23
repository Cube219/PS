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

int n;
int d[1000001];
int dt[1000001];
map<int, int> k;
int maxk, maxcnt;
int allcnt;

void add(int v)
{
    auto it = k.find(v);
    if(it == k.end()) it = k.insert({ v, 0 }).first;
    it->second++;

    if(maxcnt < it->second) {
        maxcnt = it->second;
        maxk = v;
    }
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
        cin >> d[i];
    }
    for(int i = 1; i < n; ++i) {
        if(d[i - 1] < d[i]) {
            dt[i] = dt[i - 1] + 1;
        } else if(d[i-1] > d[i]) {
            dt[i] = dt[i - 1] - 1;
        } else {
            dt[i] = dt[i - 1];
        }
    }

    for(int i = 1; i < n; ++i) {
        int gap = d[i] - d[0];
        if(gap == 0) {
            if(dt[i] == 0) allcnt++;
            else add(0);
        } else {
            if((ll)gap * dt[i] < 0) continue;
            int agap = abs(gap);
            int adt = abs(dt[i]);
            if(adt == 0 || agap % adt != 0) continue;
            add(agap / adt);
        }
    }

    cout << maxcnt + allcnt + 1 << "\n";
    cout << maxk;

    return 0;
}
