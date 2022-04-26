#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

struct Point
{
    ll x, y;
    Point operator-(const Point& rhs) const
    {
        return { x - rhs.x, y - rhs.y };
    }
    ll len() const { return x * x + y * y; }
};

bool isSame(Point l2, Point l1, Point c, Point r1, Point r2)
{
    Point l, r;
    l = c - l1;
    r = r1 - c;
    if(l.len() != r.len()) return false;

    l = l2 - l1;
    r = r2 - r1;
    if(l.len() != r.len()) return false;

    l = l2 - c;
    r = c - r2;
    if(l.len() != r.len()) return false;

    return true;
}

struct Manacher
{
    // d1: ab c ba -> 2
    // d2: ab b a -> 2
    vector<int> d1, d2;

    void build(const vector<Point>& str)
    {
        int n = str.size();
        d1.clear();
        d2.clear();

        d1.resize(n);
        int l = 0, r = -1;
        for(int i = 0; i < n; ++i) {
            int k = 1;
            if(i <= r) {
                k = min(d1[l + r - i], r - i);
            }
            while(0 <= i - k && i + k < n && (k == 0 || isSame(str[i - k], str[i - k + 1], str[i], str[i + k - 1], str[i + k]))) k++;
            d1[i] = --k;
            if(i + k > r) {
                r = i + k;
                l = i - k;
            }
        }
    }
};


void solve()
{
    int n;
    cin >> n;
    vector<Point> d;
    for(int i = 0; i < n; ++i) {
        ll x, y;
        cin >> x >> y;
        x *= 2; y *= 2;

        if(i > 0) {
            Point t = d.back();
            d.push_back({ (t.x + x) / 2, (t.y + y) / 2 });
        }
        d.push_back({ x, y });
    }
    Point t1 = d.back();
    Point t2 = d[0];
    d.push_back({ (t1.x + t2.x) / 2, (t1.y + t2.y) / 2 });
    d.insert(d.end(), d.begin(), d.end());

    Manacher mc;
    mc.build(d);

    int res = 0;
    for(int v : mc.d1) {
        if(v >= n - 1) res++;
    }

    cout << res / 2 << "\n";
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tNum = 1;
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
