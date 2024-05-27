#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <numeric>
#include <sstream>
#include <utility>
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
    maxQNum = 47;
    qNum = 0;

    // ----- Get the data from cin -----
    d.clear();
    d.resize(n, 0);
    int a, b;
    cin >> a >> b;
    d[a - 1] = d[b - 1] = 1;
    // -----------------------------
#endif
}

char query(int l, int r)
{
    stringstream ss;
    // ----- Query -----
    ss << "AK " << l << " " << r;
    // -----------------

    char res;
#ifdef CUBE_PS
    // cout << "query: " << ss.str() << "\n";
    qNum++;
    if (qNum > maxQNum) {
        cout << "WA: Too many queries (" << qNum << ")\n";
        exit(1);
    }

    // ----- Generate a query result -----
    int cnt = 0;
    for (int i = l; i <= r; ++i) {
        cnt += d[i - 1];
    }
    if (cnt == 0 || cnt == 2) res = 'X';
    else res = 'O';
        // ----------------------------

        // cout << "  - result: " << res << "\n";
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

    // ----- Check the answer -----
    bool res = false;
    if (d[a - 1] == 1 && d[b - 1] == 1) res = true;
    // --------------------------

    if (res == false) {
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

    if (n == 2) {
        answer(1, 2);
        return;
    }

    char res = query(1, n / 2);
    if (res == 'O') {
        // Left
        int lo = 0, hi = n / 2;
        while (lo + 1 < hi) {
            int mid = (lo + hi) / 2;
            res = query(1, mid);
            if (res == 'O') hi = mid;
            else lo = mid;
        }
        int lRes = hi;
        // Right
        lo = n / 2 + 1;
        hi = n + 1;
        while (lo + 1 < hi) {
            int mid = (lo + hi) / 2;
            res = query(mid, n);
            if (res == 'O') lo = mid;
            else hi = mid;
        }
        int rRes = lo;

        answer(lRes, rRes);
        return;
    } else {
        int l = n / 2, r = n / 2 + 1;
        bool isOK = false;
        vector<pair<int, int>> candi;
        while (l >= 1 && r < n) {
            res = query(l, r);
            if (res == 'O') {
                if (isOK == false) {
                    candi.push_back({l, r});
                    isOK = true;
                }
            } else {
                if (isOK == true) {
                    candi.push_back({l, r});
                    break;
                }
            }
            l--;
            r++;
        }

        if (candi.size() == 0) {
            res = query(1, 1);
            if (res == 'O') {
                answer(1, n);
            } else {
                answer(n / 2, n / 2 + 1);
            }
        } else if (candi.size() == 1) {
            res = query(candi[0].first, n / 2);
            if (res == 'O') {
                answer(1, candi[0].first);
            } else {
                answer(candi[0].second, n);
            }
        } else {
            assert(candi.size() == 2);

            res = query(candi[0].first, n / 2);
            if (res == 'O') {
                answer(candi[0].first, candi[1].first);
            } else {
                answer(candi[0].second, candi[1].second);
            }
        }
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
    for (int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
