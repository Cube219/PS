#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
#include <cmath>
#include <map>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n;
    cin >> n;
    struct Block
    {
        int idx;
        int eg[4]; // u, l, d, r
        Block()
        {
            eg[0] = eg[1] = eg[2] = eg[3] = 0;
            idx = -1;
        }
        void rotate()
        {
            int v = eg[3];
            for(int i = 4 - 1; i >= 1; --i) {
                eg[i] = eg[i - 1];
            }
            eg[0] = v;
        }
    };
    vector<Block> d(n);
    int zNum = 0;
    int egMx = 0;
    for(int i = 0; i < n; ++i) {
        auto& v = d[i];
        for(int j = 0; j < 4; ++j) {
            cin >> v.eg[j];
            if(v.eg[j] == 0) zNum++;
            egMx = max(egMx, v.eg[j]);
        }
        v.idx = i;
    }

    vector<vector<int>> table(egMx + 1);
    for(auto& b : d) {
        for(int i = 0; i < 4; ++i) {
            table[b.eg[i]].push_back(b.idx);
        }
    }

    vector<vector<Block>> res;
    auto process = [&](int a, int b) -> bool {
        if(a == 1 && b == 1) {
            bool ck = true;
            for(int i = 0; i < 4; ++i) {
                if(d[0].eg[i] != 0) ck = false;
            }
            if(!ck) return false;
            else {
                res = vector<vector<Block>>(a + 2, vector<Block>(b + 2));
                res[1][1] = d[0];
                return true;
            }
        }

        vector<Block> corner;
        if(a == 1) {
            for(auto& b : d) {
                int num = 0;
                for(int i = 0; i < 4; ++i) if(b.eg[i] == 0) num++;
                if(num == 3) corner.push_back(b);
            }
            if(corner.size() != 2) return false;
        } else {
            for(auto& b : d) {
                int num = 0;
                for(int i = 0; i < 4; ++i) if(b.eg[i] == 0) num++;
                if(num == 2) {
                    if((b.eg[0] == 0 && b.eg[1] == 0) ||
                        (b.eg[1] == 0 && b.eg[2] == 0) ||
                        (b.eg[2] == 0 && b.eg[3] == 0) ||
                        (b.eg[3] == 0 && b.eg[0] == 0))
                    {
                        corner.push_back(b);
                    }
                }
            }
            if(corner.size() != 4) return false;
        }

        res = vector<vector<Block>>(a + 2, vector<Block>(b + 2));
        vector<char> use(n, false);
        if(a == 1) {
            Block b = corner[0];
            while(b.eg[3] == 0) b.rotate();
            res[1][1] = b;
            use[b.idx] = true;
        } else {
            Block b = corner[0];
            while(b.eg[2] == 0 || b.eg[3] == 0) b.rotate();
            res[1][1] = b;
            use[b.idx] = true;
        }

        auto get = [&](int egNum) {
            for(int idx : table[egNum]) {
                if(use[idx] == false) {
                    use[idx] = true;
                    return idx;
                }
            }
            return -1;
        };

        auto insert = [&](int x, int y, Block b) {
            int up = res[x - 1][y].eg[2];
            int left = res[x][y - 1].eg[3];
            for(int i = 0; i < 4; ++i) {
                if(b.eg[0] == up && b.eg[1] == left) {
                    res[x][y] = b;
                    return true;
                }
                b.rotate();
            }
            return false;
        };

        for(int i = 1; i <= a; ++i) {
            if(i > 1) {
                int idx = get(res[i - 1][1].eg[2]);
                if(idx == -1) return false;
                bool r = insert(i, 1, d[idx]);
                if(!r) return false;
            }
            for(int j = 2; j <= b; ++j) {
                int idx = get(res[i][j - 1].eg[3]);
                if(idx == -1) return false;
                bool r = insert(i, j, d[idx]);
                if(!r) return false;
            }
        }


        // Check boundary
        for(int i = 1; i <= b; ++i) {
            if(res[a][i].eg[2] != 0) return false;
            if(res[1][1].eg[0] != 0) return false;
        }
        for(int i = 1; i <= a; ++i) {
            if(res[i][b].eg[3] != 0) return false;
            if(res[i][1].eg[1] != 0) return false;
        }

        // Check inside
        for(int i = 1; i <= a; ++i) {
            for(int j = 1; j <= b; ++j) {
                if(i > 1 && res[i][j].eg[0] == 0) return false;
                if(j > 1 && res[i][j].eg[1] == 0) return false;
            }
        }

        return true;
    };

    int sqn = sqrt(n);
    for(int a = 1; a <= sqn; ++a) {
        if(n % a != 0) continue;
        int b = n / a;
        if((a + b) * 2 != zNum) continue;

        if(process(a, b)) {
            cout << a << " " << b << "\n";
            for(int i = 1; i <= a; ++i) {
                for(int j = 1; j <= b; ++j) {
                    cout << res[i][j].idx + 1 << " ";
                }
                cout << "\n";
            }
            return;
        }
        if(a == b) continue;
        if(process(b, a)) {
            cout << b << " " << a << "\n";
            for(int i = 1; i <= b; ++i) {
                for(int j = 1; j <= a; ++j) {
                    cout << res[i][j].idx + 1 << " ";
                }
                cout << "\n";
            }
            return;
        }
    }

    cout << "impossible";
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
