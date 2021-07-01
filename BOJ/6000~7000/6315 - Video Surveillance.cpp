#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll INF = 99999999999999999;

int n;
ll minx, miny, maxx, maxy;

void update(ll lx, ll ly, ll x, ll y)
{
    if(lx == x) {
        if(ly < y) {
            minx = max(minx, x);
        } else {
            maxx = min(maxx, x);
        }
    } else { // ly == y
        if(lx < x) {
            maxy = min(maxy, y);
        } else {
            miny = max(miny, y);
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

    int tt = 0;
    while(1) {
        tt++;
        cin >> n;
        if(n == 0) break;

        minx = -INF;
        miny = -INF;
        maxx = INF;
        maxy = INF;

        ll fx, fy;
        cin >> fx >> fy;
        ll lx = fx, ly = fy;
        for(int i = 1; i < n; ++i) {
            ll x, y;
            cin >> x >> y;
            update(lx, ly, x, y);
            lx = x;
            ly = y;
        }
        update(lx, ly, fx, fy);

        cout << "Floor #" << tt << "\n";
        if(minx > maxx || miny > maxy) cout << "Surveillance is impossible.\n";
        else cout << "Surveillance is possible.\n";
        cout << "\n";
    }

    return 0;
}
