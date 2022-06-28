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
    maxQNum = 15;
    qNum = 0;

    // ----- Get data from cin -----
    d.resize(n);
    for(auto& v : d) cin >> v;
    // -----------------------------
#endif
}

vector<int> query(int l, int r)
{
    stringstream ss;
    // ----- Query -----
    ss << "? " << l << " " << r;
    // -----------------

    vector<int> res;
#ifdef CUBE_PS
    cout << "query: " << ss.str() << "\n";
    qNum++;
    if(qNum > maxQNum) {
        cout << "WA: Too many queries (" << qNum << ")\n";
        exit(1);
    }

    // ----- Get query result -----
    for(int i = l; i <= r; ++i) {
        res.push_back(d[i - 1]);
    }
    sort(res.begin(), res.end());
    // ----------------------------


    cout << "  - result: ";
    for(int v : res) cout << v << " ";
    cout << "\n";
#else
    cout << ss.str() << endl;
    for(int i = l; i <= r; ++i) {
        int v;
        cin >> v;
        res.push_back(v);
    }
#endif

    return res;
}

void answer(int idx)
{
    stringstream ss;
    // ----- Answer -----
    ss << "! " << idx;
    // ------------------

#ifdef CUBE_PS
    cout << "answer: " << ss.str() << "\n";

    // ----- Check validate -----
    bool res = true;
    if(d[idx - 1] != idx) res = false;

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

    vector<int> d(n + 1);
    iota(d.begin(), d.end(), 0);
    int l = 1, r = n;

    int ans = -1;

    while(1) {
        int mid = (l + r) / 2;
        auto res = query(l, mid);

        int num = 0;
        for(int v : res) {
            if(l <= v && v <= mid) num++;
        }

        if(num == 1) {
            for(int v : res) {
                if(l <= v && v <= mid) {
                    ans = v;
                    break;
                }
            }
            break;
        }

        if(num & 1) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }

    answer(ans);
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif

    int tNum = 1;
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
