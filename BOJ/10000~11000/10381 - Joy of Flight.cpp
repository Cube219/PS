#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <iomanip>
using namespace std;

using ll = long long int;

struct Point
{
    int x, y;
};
Point st, ed;
pair<Point, int> wind[10001];
int n, k, vmax;
bool pos;
vector<pair<double, double>> res;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << setprecision(15);
    cin >> st.x >> st.y >> ed.x >> ed.y;
    cin >> n >> k >> vmax;
    Point dt = st;
    for(int i = 0; i < n; ++i) {
        cin >> wind[i].second >> wind[i].first.x >> wind[i].first.y;
    }
    wind[n].second = 987654321;
    int windIdx = 0;
    for(int i = 0; i < k; ++i) {
        if(wind[windIdx + 1].second == i) {
            windIdx++;
        }
        dt.x += wind[windIdx].first.x;
        dt.y += wind[windIdx].first.y;
    }
    dt.x = ed.x - dt.x;
    dt.y = ed.y - dt.y;

    double cx = st.x;
    double cy = st.y;
    double dtx = (double)dt.x / k;
    double dty = (double)dt.y / k;
    {
        // ck
        ll a = (ll)dt.x * (ll)dt.x;
        a += (ll)dt.y * (ll)dt.y;
        ll b = (ll)vmax * vmax;
        b *= (ll)k * k;
        if(a > b) {
            pos = false;
        } else {
            pos = true;
        }
    }
    windIdx = 0;
    res.resize(k);
    for(int i = 0; i < k; ++i) {
        if(wind[windIdx + 1].second == i) {
            windIdx++;
        }
        cx += wind[windIdx].first.x;
        cy += wind[windIdx].first.y;
        cx += dtx;
        cy += dty;
        res[i] = { cx, cy };
    }

    if(pos == false) {
        cout << "No";
    } else {
        cout << "Yes\n";
        for(int i = 0; i < res.size(); ++i) {
            cout << res[i].first << " " << res[i].second << "\n";
        }
    }

    return 0;
}
