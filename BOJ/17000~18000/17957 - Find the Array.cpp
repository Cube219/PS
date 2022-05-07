#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cassert>
#include <numeric>
#include <vector>
#include <sstream>
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
    maxQNum = 30;
    qNum = 0;

    // ----- Get data from cin -----
    d.resize(n);
    for(auto& v : d) cin >> v;
    // -----------------------------
#endif
}

int query1(int idx)
{
    stringstream ss;
    // ----- Query -----
    ss << "1 " << idx;
    // -----------------

    int res;
#ifdef CUBE_PS
    cout << "query: " << ss.str() << "\n";
    if((++qNum) > maxQNum) { cout << "WA: Too many queries (" << qNum << ")\n"; exit(1); }

    // ----- Get query result -----
    res = d[idx - 1];
    // ----------------------------

    cout << "  - result: " << res << "\n";
#else
    cout << ss.str() << endl;
    cin >> res;
#endif

    return res;
}

vector<int> query2(const vector<int>& pos)
{
    stringstream ss;
    // ----- Query -----
    ss << "2 " << pos.size();
    for(int v : pos) ss << " " << v;
    // -----------------

    vector<int> res(pos.size() * (pos.size() - 1) / 2);
#ifdef CUBE_PS
    cout << "query: " << ss.str() << "\n";
    if((++qNum) > maxQNum) { cout << "WA: Too many queries (" << qNum << ")\n"; exit(1); }

    // ----- Get query result -----
    int idx = 0;
    for(int i = 0; i < pos.size(); ++i) {
        for(int j = i + 1; j < pos.size(); ++j) {
            res[idx++] = abs(d[pos[i] - 1] - d[pos[j] - 1]);
        }
    }
    // ----------------------------

    cout << "  - result: ";
    for(int v : res) cout << v << " ";
    cout << "\n";
#else
    cout << ss.str() << endl;
    for(auto& v : res) cin >> v;
#endif

    return res;
}

void answer(const vector<int>& res)
{
    stringstream ss;
    // ----- Answer -----
    ss << "3";
    for(int v : res) ss << " " << v;
    // ------------------

#ifdef CUBE_PS
    cout << "answer: " << ss.str() << "\n";

    // ----- Check validation -----
    bool ck = true;
    for(int i = 0; i < d.size(); ++i) {
        if(d[i] != res[i]) ck = false;
    }
    // --------------------------

    if(ck == false) { cout << "WA: the answer is incorrect\n"; exit(1); }
    else cout << "Correct (" << qNum << " queries)\n";
#else
    cout << ss.str() << endl;
#endif
}

void solve()
{
    int n;
    cin >> n;
    get_data(n);

    if(n == 1) {
        int v = query1(1);
        vector<int> res = { v };
        answer(res);
        return;
    }

    vector<int> pos;
    for(int i = 1; i <= n; ++i) {
        pos.push_back(i);
    }
    auto all = query2(pos);
    int mx = -1;
    for(int v : all) {
        mx = max(mx, v);
    }

    int l = 1, r = n;
    while(l + 1 < r) {
        int m = (l + r) / 2;
        pos.clear();
        for(int i = 1; i <= m; ++i) {
            pos.push_back(i);
        }
        auto res = query2(pos);
        int cmx = -1;
        for(int v : res) cmx = max(cmx, v);

        if(mx == cmx) r = m;
        else l = m;
    }
    int baseIdx = r;

    auto inter = [](const vector<int>& s1, const vector<int>& s2) {
        vector<int> res;
        int i = 0, j = 0;
        while(i < s1.size() && j < s2.size()) {
            if(s1[i] == s2[j]) {
                res.push_back(s1[i]);
                i++; j++;
            } else if(s1[i] < s2[j]) i++;
            else j++;
        }
        return res;
    };
    auto sub = [](const vector<int>& s1, const vector<int>& s2) {
        vector<int> res;
        int i = 0, j = 0;
        while(i < s1.size() && j < s2.size()) {
            if(s1[i] == s2[j]) {
                i++; j++;
            } else if(s1[i] > s2[j]) j++;
            else {
                res.push_back(s1[i]);
                i++;
            }
        }
        for(; i < s1.size(); ++i) res.push_back(s1[i]);
        return res;
    };
    vector<vector<int>> sets;
    for(int i = 0; i < 10; ++i) {
        pos.clear();
        for(int j = 1; j <= n; ++j) {
            if(j == baseIdx) continue;
            if(j & (1 << i)) pos.push_back(j);
        }
        if(pos.size() <= 0) {
            sets.push_back({});
            continue;
        }

        vector<int> res1;
        if(pos.size() >= 2) res1 = query2(pos);
        pos.push_back(baseIdx);
        auto res2 = query2(pos);

        sort(res1.begin(), res1.end());
        sort(res2.begin(), res2.end());

        sets.push_back(sub(res2, res1));
    }

    vector<int> d(n);
    for(int i = 1; i <= n; ++i) {
        if(i == baseIdx) continue;

        vector<int> curSet;
        for(int j = 0; j < 10; ++j) {
            if(i & (1 << j)) {
                if(curSet.size() == 0) curSet = sets[j];
                else curSet = inter(curSet, sets[j]);
            }
        }
        for(int j = 0; j < 10; ++j) {
            if((i & (1 << j)) == 0) curSet = sub(curSet, sets[j]);
        }
        assert(curSet.size() == 1);
        d[i - 1] = curSet[0];
    }

    int baseV = query1(baseIdx);
    bool isReverse = false;
    for(int i = 1; i <= n; ++i) {
        d[i - 1] = baseV - d[i - 1];
        if(d[i - 1] <= 0) isReverse = true;
    }
    if(isReverse) {
        for(int i = 1; i <= n; ++i) {
            d[i - 1] = baseV * 2 - d[i - 1];
        }
    }
    d[baseIdx - 1] = baseV;

    answer(d);
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif

    int tNum = 1;
    // cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
