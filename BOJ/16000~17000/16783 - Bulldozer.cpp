#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cassert>
#include <numeric>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

struct SegTree
{
    struct Node
    {
        ll mx, lmx, rmx, sum;
    };
    int n;
    vector<Node> t;

    SegTree(int _n)
    {
        n = _n;
        t.resize(n * 2, emptyNode);
    }

    void initv(int idx, Node v)
    {
        t[n + idx] = v;
    }

    void build()
    {
        for(int i = n - 1; i > 0; --i) {
            t[i] = merge(t[i << 1], t[i << 1 | 1]);
        }
    }

    void update(int idx, ll v)
    {
        idx += n;
        t[idx] = { v, v, v, v };
        idx >>= 1;
        while(idx > 0) {
            t[idx] = merge(t[idx << 1], t[idx << 1 | 1]);
            idx >>= 1;
        }
    }

    Node find(int l, int r)
    {
        l += n;
        r += n + 1;
        Node resl = emptyNode;
        Node resr = emptyNode;
        while(l < r) {
            if(l & 1) resl = merge(resl, t[l++]);
            if(r & 1) resr = merge(t[--r], resr);
            l >>= 1;
            r >>= 1;
        }
        return merge(resl, resr);
    }

    Node merge(Node l, Node r)
    {
        Node res;
        res.mx = max(l.mx, r.mx);
        res.mx = max(res.mx, l.rmx + r.lmx);
        res.sum = l.sum + r.sum;
        res.lmx = max(l.lmx, l.sum + r.lmx);
        res.rmx = max(r.rmx, l.rmx + r.sum);

        return res;
    }

    const Node emptyNode = { 0, 0, 0, 0 };
};

struct R
{
    ll u, d;

    R(ll _u, ll _d) : u(_u), d(_d)
    {}

    bool operator<(const R& rhs) const
    {
        return u * rhs.d < rhs.u * d;
    }
    bool operator==(const R& rhs) const
    {
        return u * rhs.d == rhs.u * d;
    }
    bool operator!=(const R& rhs) const
    {
        return u * rhs.d != rhs.u * d;
    }
};

void solve()
{
    struct Node
    {
        int x, y, v;
    };
    int n;
    cin >> n;
    vector<Node> d(n);
    for(auto& v : d) cin >> v.x >> v.y >> v.v;

    sort(d.begin(), d.end(), [](const Node& l, const Node& r) {
        if(l.y == r.y) return l.x < r.x;
        return l.y < r.y;
    });

    struct ANode
    {
        int a, b;
        R angle;
    };
    vector<ANode> posLines, negLines;
    for(int i = 0; i < n; ++i) {
        for(int j = i + 1; j < n; ++j) {
            R angle = { d[j].y - d[i].y, d[j].x - d[i].x };
            if(angle.d >= 0) posLines.push_back({ i, j, angle });
            else negLines.push_back({ i, j, { angle.u, -angle.d } });
        }
    }

    ll res = 0;
    auto process = [&](vector<ANode>& lines) {
        sort(lines.begin(), lines.end(), [](const ANode& l, const ANode& r) {
            if(l.angle == r.angle) {
                if(l.a == r.a) return l.b < r.b;
                return l.a < r.a;
            }
            return l.angle < r.angle;
        });

        vector<int> idx(n);
        iota(idx.begin(), idx.end(), 0);
        struct ANode2
        {
            vector<int> points;
            R angle;
        };
        vector<ANode2> compLines;
        vector<bool> skip(n, false);
        R curAngle = { 0, 1 };
        int firstIdx = 0;
        for(int i = 0; i < lines.size(); ++i) {
            auto& l = lines[i];
            if(curAngle != l.angle) {
                for(int j = firstIdx; j < i; ++j) {
                    skip[lines[j].b] = false;
                }
                curAngle = l.angle;
                firstIdx = i;
            }

            if(skip[l.a]) continue;
            if(compLines.size() == 0 || compLines.back().angle != curAngle || compLines.back().points[0] != l.a) {
                compLines.push_back({ {}, curAngle });
                compLines.back().points.push_back(l.a);
            }
            compLines.back().points.push_back(l.b);
            skip[l.b] = true;
        }

        SegTree sg(n);
        for(int i = 0; i < n; ++i) {
            int v = d[i].v;
            sg.initv(i, { v, v, v, v });
        }
        sg.build();

        curAngle = { 0, 1 };
        firstIdx = 0;
        for(int i = 0; i < compLines.size(); ++i) {
            auto& l = compLines[i];
            if(curAngle != l.angle) {
                res = max(res, sg.find(0, n - 1).mx);
                // 합친 것 풀고 뒤집기
                for(int j = firstIdx; j < i; ++j) {
                    auto& curl = compLines[j];
                    int pNum = curl.points.size();
                    for(int l = 0; l < pNum; ++l) {
                        int r = pNum - l - 1;
                        if(l > r) break;
                        swap(idx[curl.points[l]], idx[curl.points[r]]);
                    }
                    for(int k = 0; k < pNum; ++k) {
                        sg.update(idx[curl.points[k]], d[curl.points[k]].v);
                    }
                }
                curAngle = l.angle;
                firstIdx = i;
                res = max(res, sg.find(0, n - 1).mx);
            }

            // 합치기
            ll v = 0;
            for(int j : l.points) v += d[j].v;
            sg.update(idx[l.points[0]], v);
            for(int j = 1; j < l.points.size(); ++j) {
                sg.update(idx[l.points[j]], 0);
            }
        }
        res = max(res, sg.find(0, n - 1).mx);
        // 합친 것 풀고 뒤집기
        for(int j = firstIdx; j < compLines.size(); ++j) {
            auto& curl = compLines[j];
            int pNum = curl.points.size();
            for(int l = 0; l < pNum; ++l) {
                int r = pNum - l - 1;
                if(l > r) break;
                swap(idx[curl.points[l]], idx[curl.points[r]]);
            }
            for(int k = 0; k < pNum; ++k) {
                sg.update(idx[curl.points[k]], d[curl.points[k]].v);
            }
            res = max(res, sg.find(0, n - 1).mx);
        }
    };

    process(posLines);
    process(negLines);

    cout << res;
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
