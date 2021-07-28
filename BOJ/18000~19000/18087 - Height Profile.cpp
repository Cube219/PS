#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cassert>
#include <iomanip>
#include <map>
#include <set>
#include <vector>
using namespace std;

using ll = long long int;

struct Node
{
    int y;
    int idx;
    bool operator<(const Node& rhs)
    {
        return y < rhs.y;
    }
};

int n, k;
int h[100005], h2[100005];
// set<Node> d;
map<int, int> d;

double process()
{
    d.clear();
    d.insert({ h2[0], 0 });

    double res = -1;

    for(int i = 1; i <= n; ++i) {
        auto it = d.upper_bound(h2[i]);
        if(it == d.end()) {
            res = max(res, (double)i);
        } else if(it != d.begin()) {
            --it;
            assert(it->second != 0);

            int idx = it->second;
            int y1 = h2[idx - 1];
            int y2 = h2[idx];

            double a = (double)(y1 - h2[i]) / (double)(y1 - y2);
            double b = 1 - a;
            res = max(res, i - idx + b);
        }

        if(d.begin()->first > h2[i]) {
            d.insert({ h2[i], i });
        }
    }

    return res;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;
    for(int i = 0; i <= n; ++i) {
        cin >> h[i];
    }

    cout << fixed << setprecision(7);
    for(int i = 0; i < k; ++i) {
        double dg;
        cin >> dg;
        int g = dg * 10;

        for(int j = 0; j <= n; ++j) {
            h2[j] = h[j] - j * g;
        }

        double res = process();
        reverse(h2, h2 + n + 1);
        for(int j = 0; j <= n; ++j) {
            h2[j] = -h2[j];
        }
        res = max(res, process());

        if(res < 0) cout << "impossible\n";
        else cout << res << "\n";
    }

    return 0;
}
