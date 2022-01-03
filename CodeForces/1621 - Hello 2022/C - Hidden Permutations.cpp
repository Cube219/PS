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

int qNum, maxQNum;
vector<int> d, q;

void get_data(int n)
{
#ifdef CUBE_PS
    maxQNum = n * 2;
    qNum = 0;
    // Get data from cin
    d.resize(n);
    for(auto& v : d) {
        cin >> v;
        v--;
    }
    q.resize(n);
    iota(q.begin(), q.end(), 0);

#endif
}

int query(int idx)
{
    int res;
#ifdef CUBE_PS
    cout << "query: ? " << idx << "\n";
    // Get query result
    res = q[idx - 1] + 1;

    if(qNum >= maxQNum) {
        cout << "WA: Too many queries (" << qNum << ")\n";
        exit(1);
    }
    qNum++;
    cout << "  - result: " << res << "\n";

    vector<int> q2(d.size());
    for(int i = 0; i < d.size(); ++i) {
        q2[i] = q[d[i]];
    }
    q = q2;
#else
    cout << "? " << idx << endl;
    cin >> res;
#endif

    return res;
}

void answer(vector<int>& rr)
{
#ifdef CUBE_PS
    bool res = true;
    // Check validate
    for(int i = 0; i < d.size(); ++i) {
        if(rr[i] - 1 != d[i]) {
            res = false;
            break;
        }
    }

    if(res == false) {
        cout << "WA: the answer is incorrect\n";
        exit(1);
    } else {
        cout << "Correct (" << qNum << " queries)\n";
    }
#else
    cout << "! ";
    for(int v : rr) cout << v << " ";
    cout << endl;
#endif
}


void solve()
{
    int n;
    cin >> n;
    get_data(n);

    vector<int> res(n, 0), st;
    vector<char> ck(n, false);
    int idx = 0, step = 0;
    while(idx < n) {
        if(st.size() == 0 && ck[idx] == true) {
            idx++;
            continue;
        }
        int qr = query(idx + 1) - 1;

        if(ck[qr] == true) {
            for(int i = 0; i < st.size(); ++i) {
                res[st[(step + i) % st.size()]] = st[(step + i + 1) % st.size()] + 1;
            }
            st.clear();
        } else {
            ck[qr] = true;
            st.push_back(qr);
        }
        step++;
    }

    answer(res);
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
