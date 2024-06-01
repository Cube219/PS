#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

struct ERes
{
    ll x, y, g;
};
ERes eeuc(ll a, ll b)
{
    if (b == 0) return {1, 0, a};

    ERes res = eeuc(b, a % b);
    ll x = res.y;
    ll y = res.x - a / b * res.y;
    return {x, y, res.g};
}
// Ax+By=C, D=gcd(A,B)=g
// x0 = x * C/D       y0 = y * C/D
// s = x0 + k*B/D   t = y0 - k*A/D   (k=임의의 정수)

void solve()
{
    ll n, p, q;
    cin >> n >> p >> q;
    struct Node
    {
        ll a, b, ab;
        ll resA, resB;
    };
    vector<Node> d(n);
    for (auto& v : d) cin >> v.a;
    for (auto& v : d) cin >> v.b;

    for (auto& v : d) {
        v.ab = v.b - v.a;
        v.resA = 0;
        v.resB = 0;
    }
    bool isOK = true;
    q = -q;
    ERes er = eeuc(p, q);
    for (auto& v : d) {
        if (v.ab % er.g != 0) {
            isOK = false;
            break;
        }
        ll x = er.x * v.ab / er.g;
        ll y = er.y * v.ab / er.g;

        ll g = -abs(er.g);

        ll k = (y / (p / g));
        if (y - k * p / g < 0) k++;

        ll k2 = -(x / (q / g));
        if (x + k2 * q / g < 0) k2++;

        k = max(k, k2);

        x = x + k * q / g;
        y = y - k * p / g;

        assert(x >= 0 && y >= 0);
        v.resA = x;
        v.resB = y;
    }

    q = -q;
    ll aSum = 0, bSum = 0;
    for (auto& v : d) {
        aSum += v.resA;
        bSum += v.resB;
    }
    if (aSum != bSum) {
        ll remain = aSum < bSum ? -p * (bSum - aSum) : q * (aSum - bSum);
        if ((remain > 0 && q - p > 0) || (remain < 0 && q - p < 0)) {
            isOK = false;
        } else if (remain % (q - p) != 0) {
            isOK = false;
        } else {
            ll num = -remain / (q - p);
            d.back().resA += num;
            d.back().resB += num;
            if (aSum > bSum) d.back().resB += abs(bSum - aSum);
            else d.back().resA += abs(bSum - aSum);
        }
    }

    if (isOK) {
        cout << "YES\n";
        for (auto& v : d) cout << v.resA << " ";
        cout << "\n";
        for (auto& v : d) cout << v.resB << " ";
    } else {
        cout << "NO";
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
    for (int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
