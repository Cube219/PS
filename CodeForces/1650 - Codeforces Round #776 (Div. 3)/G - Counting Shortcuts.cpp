#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <queue>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

template <int mod>
struct ModInt
{
    ll v;
    ModInt(ll _v = 0) : v((_v % mod + mod) % mod) {}
    ModInt& operator+=(const ModInt& rhs) {
        v += rhs.v;
        if(v >= mod) v -= mod;
        return *this;
    }
    ModInt& operator-=(const ModInt& rhs) {
        v -= rhs.v;
        if(v < 0) v += mod;
        return *this;
    }
    ModInt& operator*=(const ModInt& rhs) {
        v *= rhs.v;
        v %= mod;
        return *this;
    }
    ModInt& operator/=(const ModInt& rhs) {
        ll n = mod - 2;
        ModInt rev = 1, b = rhs;
        while(n > 0) {
            if(n & 1) rev *= b;
            b *= b;
            n >>= 1;
        }
        return *this *= rev;
    }
    ModInt operator+(const ModInt& rhs) const {
        ModInt lhs(*this);
        return lhs += rhs;
    }
    ModInt operator-() const { return ModInt() -= *this; }
    ModInt operator-(const ModInt& rhs) const {
        ModInt lhs(*this);
        return lhs -= rhs;
    }
    ModInt operator*(const ModInt& rhs) const {
        ModInt lhs(*this);
        return lhs *= rhs;
    }
    ModInt operator/(const ModInt& rhs) const {
        ModInt lhs(*this);
        return lhs /= rhs;
    }
    friend std::ostream& operator<<(std::ostream& os, const ModInt& n) { return os << n.v; }
    friend std::istream& operator>>(std::istream& is, ModInt& n) {
        ll x;
        is >> x;
        n = ModInt(x);
        return is;
    }
    bool operator==(const ModInt& rhs) const { return v == rhs.v; }
    bool operator!=(const ModInt& rhs) const { return v != rhs.v; }
    ModInt pow(ll k) const {
        ModInt res = 1, p = v;
        while(k > 0) {
            if(k & 1) res *= p;
            p *= p;
            k >>= 1;
        }
        return res;
    }
};
using mint = ModInt<MOD>;

void solve()
{
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    s--; t--;
    vector<vector<int>> g(n);
    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<ll> dst, dst2;
    vector<mint> dstCnt, dstCnt2;
    vector<char> visit, visit2;
    auto dijk = [&](int st) -> void {
        dst.resize(n, INF);
        dst2.resize(n, INF);
        dstCnt.resize(n, 0);
        dstCnt2.resize(n, 0);
        visit.resize(n, false);
        visit2.resize(n, false);
        dst[st] = 0;
        dst2[st] = 0;
        dstCnt[st] = 1;
        dstCnt2[st] = 0;
        struct PNode
        {
            ll v;
            int cur;
            bool isSecond;
            bool operator<(const PNode& rhs) const { return v > rhs.v; }
        };
        priority_queue<PNode> pq;
        pq.push({ 0, st, false });
        while(pq.empty() == false) {
            int cur = pq.top().cur;
            bool isSecond = pq.top().isSecond;
            pq.pop();

            if(isSecond == false) {
                if(visit[cur] == true) continue;
                visit[cur] = true;
            } else {
                if(visit2[cur] == true) continue;
                visit2[cur] = true;
            }

            int myCost;
            mint myCnt;
            if(isSecond == false) {
                // use visit
                myCost = dst[cur];
                myCnt = dstCnt[cur];
            } else {
                // use visit2
                myCost = dst2[cur];
                myCnt = dstCnt2[cur];
            }

            for(int nxt : g[cur]) {
                if(dst[nxt] > myCost + 1) {
                    dst2[nxt] = dst[nxt];
                    dstCnt2[nxt] = dstCnt[nxt];

                    dst[nxt] = myCost + 1;
                    dstCnt[nxt] = myCnt;
                    pq.push({ dst[nxt], nxt, false });
                } else if(dst[nxt] == myCost + 1) {
                    dstCnt[nxt] += myCnt;
                } else if(dst2[nxt] > myCost + 1) {
                    dst2[nxt] = myCost + 1;
                    dstCnt2[nxt] = myCnt;

                    pq.push({ dst2[nxt], nxt, true });
                } else if(dst2[nxt] == myCost + 1) {
                    dstCnt2[nxt] += myCnt;
                }
            }
        }
    };
    dijk(s);

    mint res = dstCnt[t];
    if(dst2[t] == dst[t] + 1) res += dstCnt2[t];

    cout << res << "\n";
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
