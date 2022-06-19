#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

constexpr double PI = 3.141592653;

void solve()
{
    int n;
    cin >> n;
    double myLong, myLati;
    cin >> myLong >> myLati;
    myLong = myLong / 180 * PI;
    myLati = myLati / 180 * PI;

    double myX = (double)6371 * cos(myLong) * cos(myLati);
    double myY = (double)6371 * sin(myLong) * cos(myLati);
    double myZ = (double)6371 * sin(myLati);

    cout << fixed << setprecision(10);

    for(int i = 0; i < n; ++i) {
        double sLong, sLati, r, x;
        cin >> sLong >> sLati >> r >> x;
        sLong = sLong / 180 * PI;
        sLati = sLati / 180 * PI;

        x = x * 2 * PI;

        double sx = r * cos(x);
        double sy = r * cos(sLati) * sin(x);
        double sz = r * sin(x) * sin(sLati);

        // rotate
        double nx = sx * cos(sLong) - sy * sin(sLong);
        double ny = sx * sin(sLong) + sy * cos(sLong);

        double dx = myX - nx;
        double dy = myY - ny;
        double dz = myZ - sz;
        double dis = sqrt(dx * dx + dy * dy + dz * dz);

        double lim = sqrt(r * r - (6371 * 6371));
        if(dis > lim) cout << "no signal\n";
        else cout << dis / 299792.458 << "\n";
    }
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tNum = 1;
    // cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
