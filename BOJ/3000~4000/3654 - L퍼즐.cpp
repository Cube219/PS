#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

// https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/2sat.h
struct TwoSat
{
    int N;
    vector<vector<int>> gr;
    vector<int> values; // 0 = false, 1 = true

    TwoSat(int n = 0) : N(n), gr(2 * n) {}

    int addVar()
    {
        // (optional)
        gr.emplace_back();
        gr.emplace_back();
        return N++;
    }

    void either(int f, int j)
    {
        f = max(2 * f, -1 - 2 * f);
        j = max(2 * j, -1 - 2 * j);
        gr[f].push_back(j ^ 1);
        gr[j].push_back(f ^ 1);
    }

    void setValue(int x) { either(x, x); }

    void atMostOne(const vector<int>& li)
    {
        // (optional)
        if(li.size() <= 1) return;
        int cur = ~li[0];
        for(int i = 0; i < li.size(); ++i) {
            int next = addVar();
            either(cur, ~li[i]);
            either(cur, next);
            either(~li[i], next);
            cur = ~next;
        }
        either(cur, ~li[1]);
    }

    vector<int> val, comp, z;
    int time = 0;

    int dfs(int i)
    {
        int low = val[i] = ++time, x;
        z.push_back(i);
        for(int e : gr[i])
            if(!comp[e]) low = min(low, val[e] ? val[e] : dfs(e));
        if(low == val[i])
            do {
                x = z.back();
                z.pop_back();
                comp[x] = low;
                if(values[x >> 1] == -1) values[x >> 1] = x & 1;
            } while(x != i);
        return val[i] = low;
    }

    bool solve()
    {
        values.assign(N, -1);
        val.assign(2 * N, 0);
        comp = val;
        for(int i = 0; i < N * 2; ++i) {
            if(!comp[i]) dfs(i);
        }
        for(int i = 0; i < N; ++i) {
            if(comp[2 * i] == comp[2 * i + 1]) return false;
        }
        return true;
    }
};

// a^b == (~a||~b) & (a||b)
// a eq b == (~a||b) & (a||~b)
// a -> b == (~a||b)
// (a+b+c<=1) == (~a||~b) & (~a||~c) & (~b||~c)

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<string> map(n);
    int bnum = 0, wnum = 0;
    for(auto& v : map) {
        cin >> v;
        for(char ch : v) {
            if(ch == 'B') bnum++;
            else if(ch == 'W') wnum++;
        }
    }
    if(bnum * 2 != wnum) {
        cout << "NO\n";
        return;
    }

    TwoSat sat(n * m * 2);
    auto getId = [&](int x1, int y1, int x2, int y2) {
        if(x1 > x2) swap(x1, x2);
        if(y1 > y2) swap(y1, y2);

        int id = x1 * m + y1;
        if(x1 == x2) return id * 2;
        else return id * 2 + 1;
    };
    bool res = true;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(map[i][j] == 'B') {
                int l = -1, r = -1, u = -1, d = -1;
                if(j > 0 && map[i][j - 1] == 'W') l = getId(i, j - 1, i, j);
                if(j < m - 1 && map[i][j + 1] == 'W') r = getId(i, j, i, j + 1);
                if(i > 0 && map[i - 1][j] == 'W') u = getId(i - 1, j, i, j);
                if(i < n - 1 && map[i + 1][j] == 'W') d = getId(i, j, i + 1, j);
                // lr xor
                if(l == -1 && r == -1) {
                    res = false;
                    break;
                } else if(l == -1) {
                    sat.setValue(r);
                } else if(r == -1) {
                    sat.setValue(l);
                } else {
                    sat.either(~l, ~r);
                    sat.either(l, r);
                }

                // ud xor
                if(u == -1 && d == -1) {
                    res = false;
                    break;
                } else if(u == -1) {
                    sat.setValue(d);
                } else if(d == -1) {
                    sat.setValue(u);
                } else {
                    sat.either(~u, ~d);
                    sat.either(u, d);
                }
            } else if(map[i][j] == 'W') {
                vector<int> lrud(4, -1);
                if(j > 0 && map[i][j - 1] == 'B') lrud[0] = getId(i, j - 1, i, j);
                if(j < m - 1 && map[i][j + 1] == 'B') lrud[1] = getId(i, j, i, j + 1);
                if(i > 0 && map[i - 1][j] == 'B') lrud[2] = getId(i - 1, j, i, j);
                if(i < n - 1 && map[i + 1][j] == 'B') lrud[3] = getId(i, j, i + 1, j);

                int cnt = 0, idx = 0;
                for(int a = 0; a < 4; ++a) {
                    if(lrud[a] != -1) {
                        cnt++;
                        idx = a;
                    }
                }
                if(cnt == 0) {
                    res = false;
                    break;
                } else if(cnt == 1) {
                    sat.setValue(lrud[idx]);
                } else {
                    for(int a = 0; a < 4; ++a) {
                        if(lrud[a] == -1) continue;
                        for(int b = 0; b < 4; ++b) {
                            if(a == b || lrud[b] == -1) continue;
                            sat.either(~lrud[a], ~lrud[b]);
                        }
                    }
                }
            }
        }
    }
    if(res == true) res = sat.solve();

    if(res == true) cout << "YES\n";
    else cout << "NO\n";
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
