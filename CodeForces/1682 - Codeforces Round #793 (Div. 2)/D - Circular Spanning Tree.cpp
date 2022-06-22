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

void solve()
{
    int n;
    cin >> n;
    string d;
    cin >> d;

    int odd = 0;
    for(char ch : d) {
        if(ch == '1') odd++;
    }

    if(odd == 0 || odd & 1) {
        cout << "NO\n";
        return;
    }

    int st;
    for(st = 0; st < n; ++st) if(d[st] == '1') break;

    struct Edge
    {
        int u, v;
    };
    vector<Edge> res;
    vector<int> rt;
    int last = (st + 1) % n;
    for(int i = (st + 1) % n; i != st; i = (i + 1) % n) {
        if(d[i] == '0') res.push_back({ i, (i + 1) % n });
        else {
            rt.push_back(last);
            last = (i + 1) % n;
        }
    }
    rt.push_back(last);

    for(int i = 1; i < rt.size(); ++i) {
        res.push_back({ rt[0], rt[i] });
    }

    cout << "YES\n";
    for(auto [u, v] : res) cout << u + 1 << " " << v + 1 << "\n";
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
