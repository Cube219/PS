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
constexpr ll INF = 300000000000;

// y = ax + b
struct Line
{
    ll a, b;
};

struct Node
{
    Line line;
    int idx;
    int qidx;
};

struct Frac
{
    ll u, d;
    Frac() : u(0), d(1)
    {}
    Frac(ll _u, ll _d)
    {
        ll g = gcd(abs(_u), abs(_d));
        u = _u / g; d = _d / g;
        if(d < 0) {
            u *= -1;
            d *= -1;
        }
    }
    bool operator<(const Frac& rhs) const
    {
        return (u * rhs.d) < (rhs.u * d);
    }
    bool operator<=(const Frac& rhs) const
    {
        return (u * rhs.d) <= (rhs.u * d);
    }
};


int n;
Node d[200001];
Frac res[200001];
vector<Line> st;
int ridx[200001];

Frac tfunc(ll idx, const Line& qline)
{
    Line& cur = st[idx];
    Frac x = Frac(qline.b - cur.b, cur.a - qline.a);
    if(x.u * x.d <= 0) return Frac(INF, 1);
    return x;
}

Frac tsearch(const Line& qline)
{
    ll l = 0, r = st.size() - 1;
    while(l + 2 < r) {
        ll p = (l * 2 + r) / 3;
        ll q = (l + r * 2) / 3;

        Frac pv = tfunc(p, qline);
        Frac qv = tfunc(q, qline);
        if(pv <= qv) r = q;
        else l = p;
    }

    Frac res = tfunc(l, qline);
    for(ll i = l + 1; i <= r; ++i) {
        res = min(res, tfunc(i, qline));
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

    cin >> n;
    for(int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        d[i].line.a = -(i + 1);
        d[i].line.b = a;
        d[i].idx = i;
    }
    for(int i = 0; i < n; ++i) {
        cin >> d[i].qidx;
        d[i].qidx--;
    }
    sort(d, d + n, [](const Node& l, const Node& r) {
        return l.line.b < r.line.b;
    });
    for(int i = 0; i < n; ++i) {
        ridx[d[i].idx] = i;
    }
    for(int i = 0; i < n; ++i) {
        d[i].qidx = ridx[d[i].qidx];
    }
    for(int i = n - 1; i >= 0; --i) {
        Line cur = d[i].line;
        while(st.size() > 0) {
            Line b1 = st.back();
            if(b1.a > cur.a) {
                st.pop_back();
                continue;
            }
            if(st.size() > 1) {
                Line b2 = st[st.size() - 2];
                Frac curx = Frac(b2.b - b1.b, b1.a - b2.a);
                Frac newx = Frac(b1.b - cur.b, cur.a - b1.a);
                if(curx < newx) {
                    st.pop_back();
                    continue;
                }
            }
            break;
        }
        st.push_back(cur);

        int qidx = d[i].qidx;
        if(qidx >= i) continue;

        Line qline = d[qidx].line;
        auto r = tsearch(qline);
        if(r.u != INF) {
            res[d[i].idx] = r;
        }
    }

    st.clear();
    for(int i = 0; i < n; ++i) {
        Line cur = d[i].line;
        while(st.size() > 0) {
            Line b1 = st.back();
            if(b1.a < cur.a) {
                st.pop_back();
                continue;
            }
            if(st.size() > 1) {
                Line b2 = st[st.size() - 2];
                Frac curx = Frac(b2.b - b1.b, b1.a - b2.a);
                Frac newx = Frac(b1.b - cur.b, cur.a - b1.a);
                if(curx < newx) {
                    st.pop_back();
                    continue;
                }
            }
            break;
        }
        st.push_back(cur);

        int qidx = d[i].qidx;
        if(qidx <= i) continue;

        Line qline = d[qidx].line;
        auto r = tsearch(qline);
        if(r.u != INF) {
            res[d[i].idx] = r;
        }
    }

    for(int i = 0; i < n; ++i) {
        if(res[i].u == 0 || res[i].u == INF) cout << "-1\n";
        else cout << res[i].u << "/" << res[i].d << "\n";
    }

    return 0;
}
