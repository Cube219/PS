#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cassert>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <cmath>
using namespace std;

using ll = long long int;

int tNum;
int strnum;
unordered_map<string, int> str2num;
unordered_map<int, string> num2str;
int pnum;
struct Pair
{
    short a, b;
    short res;
};
Pair p[201];

struct Node
{
    short color;
    double p;
};
int n;
vector<Node> d[501];

map<short, double> dp[125300];
int bidx[505];
int adj[302][302];

int getidx(int x, int y)
{
    return bidx[x] + (y - x);
}

short getnum(string& str)
{
    auto it = str2num.find(str);
    if(it == str2num.end()) {
        it = str2num.insert({ str, ++strnum }).first;
        num2str.insert({ strnum, str });
    }
    return it->second;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> pnum;
    for(int i = 0; i < pnum; ++i) {
        string s1, s2, s3;
        cin >> s1 >> s2 >> s3;
        p[i] = { getnum(s1), getnum(s2), getnum(s3) };
        adj[p[i].a][p[i].b] = p[i].res;
        adj[p[i].b][p[i].a] = p[i].res;
    }

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n;
        int sum = 0;
        for(int i = n; i >= 0; --i) {
            sum += i;
            bidx[n - i + 1] = sum;
        }
        for(int i = 0; i < n; ++i) {
            d[i].clear();
            d[i].shrink_to_fit();
            while(1) {
                string str;
                cin >> str;
                if(str == "END") break;
                double v;
                cin >> v;
                v = log2(v);
                d[i].push_back({ getnum(str), v });
            }
        }
        for(short i = 0; i < n; ++i) {
            int idx = getidx(i, i);
            for(int j = 0; j < d[i].size(); ++j) {
                dp[idx].insert({ d[i][j].color, d[i][j].p });
            }
        }

        for(short sz = 2; sz <= n; ++sz) {
            for(short l = 0; l < n - sz + 1; ++l) {
                short r = l + sz - 1;
                int curidx = getidx(l, r);
                auto& curdp = dp[curidx];
                for(short k = l; k < r; ++k) {
                    int lidx = getidx(l, k);
                    int ridx = getidx(k + 1, r);
                    auto& ldp = dp[lidx];
                    auto& rdp = dp[ridx];
                    for(auto& lit : ldp) {
                        for(auto& rit : rdp) {
                            short res = adj[lit.first][rit.first];
                            if(res == 0) continue;
                            double v = lit.second + rit.second;
                            auto cit = curdp.find(res);
                            if(cit == curdp.end()) {
                                curdp.insert({ res, v });
                            } else {
                                if(cit->second < v) cit->second = v;
                            }
                        }
                    }
                }
            }
        }
        auto& curdp = dp[getidx(0, n - 1)];
        short maxcolor = -1;
        double maxv = -99999999999999.0;
        for(auto& it : curdp) {
            if(it.second > maxv) {
                maxv = it.second;
                maxcolor = it.first;
            }
        }

        if(maxcolor == -1) cout << "GAMEOVER\n";
        else cout << num2str[maxcolor] << "\n";

        for(int i = 0; i < n; ++i) {
            for(int j = i; j < n; ++j) {
                int idx = getidx(i, j);
                dp[idx].clear();
            }
        }
    }

    return 0;
}
