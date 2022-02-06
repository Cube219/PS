#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <sstream>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

int qNum, maxQNum;
vector<int> d;

void get_data(int n)
{
#ifdef CUBE_PS
    maxQNum = n * 2 - 2;
    qNum = 0;

    // ----- Get data from cin -----
    d.resize(n);
    for(auto& v : d)cin >> v;
    // -----------------------------
#endif
}

int query(int a, int b, int c)
{
    stringstream ss;
    // ----- Query -----
    ss << "? " << a << " " << b << " " << c;
    // -----------------

    int res;
#ifdef CUBE_PS
    cout << "query: " << ss.str() << "\n";
    qNum++;
    if(qNum > maxQNum) {
        cout << "WA: Too many queries (" << qNum << ")\n";
        exit(1);
    }

    // ----- Get query result -----
    a--; b--; c--;
    int mx = d[a], mn = d[a];
    mx = max(mx, d[b]);
    mx = max(mx, d[c]);

    mn = min(mn, d[b]);
    mn = min(mn, d[c]);
    res = mx - mn;
    // ----------------------------


    cout << "  - result: " << res << "\n";
#else
    cout << ss.str() << endl;
    cin >> res;
#endif

    return res;
}

void answer(int a, int b)
{
    stringstream ss;
    // ----- Answer -----
    ss << "! " << a << " " << b;
    // ------------------

#ifdef CUBE_PS
    cout << "answer: " << ss.str() << "\n";

    // ----- Check validate -----
    bool res = false;
    a--; b--;
    if(d[a] == 0 || d[b] == 0) res = true;
    // --------------------------

    if(res == false) {
        cout << "WA: the answer is incorrect\n";
        exit(1);
    } else {
        cout << "Correct (" << qNum << " queries)\n";
    }
#else
    cout << ss.str() << endl;
#endif
}

void solve()
{
    int n;
    cin >> n;

    get_data(n);

    int init = query(1, 2, 3);
    int mx = init, mxidx = 0;
    for(int i = 4; i <= n; ++i) {
        int v = query(1, 2, i);
        if(mx < v) {
            mx = v;
            mxidx = i;
        }
    }

    int a = 1, b = mxidx;
    if(mxidx == 0) {
        b = 3;
    }

    mx = 0, mxidx = 0;
    for(int i = 1; i <= n; ++i) {
        if(i == a || i == b) continue;
        int v = query(a, b, i);
        if(mx < v) {
            mx = v;
            mxidx = i;
        }
    }

    int t1 = mxidx, t2 = b;
    int mid = 0;
    for(int i = 1; i <= n; ++i) {
        if(i == t1 || i == t2) continue;
        mid = i;
        break;
    }

    int other = 0;
    for(int i = 1; i <= n; ++i) {
        if(i == t1 || i == t2 || i == mid) continue;
        other = i;
        break;
    }

    int v = query(t1, mid, other);
    int v2 = query(mid, t2, other);
    if(v == mx) {
        answer(t1, mid);
    } else if(v2 == mx) {
        answer(mid, t2);
    } else {
        answer(t1, t2);
    }
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    // ios_base::sync_with_stdio(false);
    // cin.tie(0);

    int tNum = 1;
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
