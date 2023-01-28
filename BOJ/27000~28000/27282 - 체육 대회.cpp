#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <algorithm>
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

void solve()
{
    struct Player
    {
        int a, b, c;
    };
    vector<Player> a(15), b(15), c(15), d(15);
    auto read = [&](vector<Player>& d) {
        for(auto& v : d) cin >> v.a;
        for(auto& v : d) cin >> v.b;
        for(auto& v : d) cin >> v.c;
    };
    read(a);
    read(b);
    read(c);
    read(d);

    vector<vector<int>> aList, bList, cList, dList;
    auto calList = [&](vector<Player>& d, vector<vector<int>>& list) {
        vector<int> idx = {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2};
        vector<vector<int>> mx(76, vector<int>(76, -1));
        do {
            int aSum = 0, bSum = 0, cSum = 0;
            for(int i = 0; i < 15; ++i) {
                switch(idx[i]) {
                case 0:
                    aSum += d[i].a;
                    break;
                case 1:
                    bSum += d[i].b;
                    break;
                case 2:
                    cSum += d[i].c;
                    break;
                }
            }
            mx[aSum][bSum] = max(mx[aSum][bSum], cSum);
        } while(next_permutation(idx.begin(), idx.end()));

        for(int i = 1; i <= 75; ++i) {
            for(int j = 1; j <= 75; ++j) {
                if(mx[i][j] != -1) list.push_back({i, j, mx[i][j]});
            }
        }
    };
    calList(a, aList);
    calList(b, bList);
    calList(c, cList);
    calList(d, dList);

    bool res = false;
    for(auto& aa : aList) {
        vector<char> bWin(8, false), cWin(8, false), dWin(8, false);
        for(auto& bb : bList) {
            int v = 0;
            if(aa[0] <= bb[0]) v |= (1 << 0);
            if(aa[1] <= bb[1]) v |= (1 << 1);
            if(aa[2] <= bb[2]) v |= (1 << 2);

            bWin[v] = true;
        }
        for(auto& cc : cList) {
            int v = 0;
            if(aa[0] <= cc[0]) v |= (1 << 0);
            if(aa[1] <= cc[1]) v |= (1 << 1);
            if(aa[2] <= cc[2]) v |= (1 << 2);

            cWin[v] = true;
        }
        for(auto& dd : dList) {
            int v = 0;
            if(aa[0] <= dd[0]) v |= (1 << 0);
            if(aa[1] <= dd[1]) v |= (1 << 1);
            if(aa[2] <= dd[2]) v |= (1 << 2);

            dWin[v] = true;
        }
        bool ck = true;
        for(int bb = 0; bb < 8; ++bb) {
            for(int cc = 0; cc < 8; ++cc) {
                for(int dd = 0; dd < 8; ++dd) {
                    if(bWin[bb] && cWin[cc] && dWin[dd]) {
                        int tmp = (bb | cc | dd);
                        int cnt = 0;
                        if(tmp & 1) cnt++;
                        if(tmp & (1 << 1)) cnt++;
                        if(tmp & (1 << 2)) cnt++;

                        if(cnt >= 2) ck = false;
                    }
                }
            }
        }
        if(ck) {
            res = true;
            break;
        }
    }
    if(res)
        cout << "YES";
    else
        cout << "NO";
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
