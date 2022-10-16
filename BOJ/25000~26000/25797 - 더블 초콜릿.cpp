#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <map>
#include <numeric>
#include <unordered_map>
#include <vector>
#include <queue>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    vector<int> dx = { 0, 1, 0, -1 }, dy = { 1, 0, -1, 0 };

    int n;
    cin >> n;
    vector<vector<int>> d(n, vector<int>(n));
    for(auto& v : d) for(auto& v2 : v) cin >> v2;

    vector<vector<int>> d2(n, vector<int>(n, 0));
    int k;
    cin >> k;
    for(int i = 0; i < k; ++i) {
        int x, y, c;
        cin >> x >> y >> c;
        x--; y--;
        d2[x][y] = c;
    }
    vector<string> map(n * 2 + 1);
    for(auto& v : map) cin >> v;

    vector<vector<int>> area(n, vector<int>(n, -1));
    vector<vector<pair<int, int>>> areaIdx;
    int areaNum = 0;
    for(int i = 0; i < n * 2 + 1; ++i) {
        for(int j = 0; j < n * 2 + 1; ++j) {
            if(map[i][j] != '.') continue;

            areaIdx.emplace_back();
            queue<pair<int, int>> q;
            q.push({ i, j });
            map[i][j] = '0';
            while(!q.empty()) {
                auto [x, y] = q.front(); q.pop();
                for(int k = 0; k < 4; ++k) {
                    int nx = x + dx[k];
                    int ny = y + dy[k];
                    if(nx < 0 || ny < 0 || nx >= n * 2 + 1 || ny >= n * 2 + 1) continue;
                    if(map[nx][ny] != '.') continue;

                    map[nx][ny] = '0';
                    if(area[(nx - 1) / 2][(ny - 1) / 2] == -1) {
                        areaIdx.back().push_back({ (nx - 1) / 2, (ny - 1) / 2 });
                    }
                    area[(nx - 1) / 2][(ny - 1) / 2] = areaNum;
                    q.push({ nx, ny });
                }
            }
            areaNum++;
        }
    }

    bool pos = true;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            for(int k = 0; k < 4; ++k) {
                int nx = i + dx[k];
                int ny = j + dy[k];
                if(nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
                if(area[i][j] != area[nx][ny]) continue;

                int midX = ((i * 2 + 1) + (nx * 2 + 1)) / 2;
                int midY = ((j * 2 + 1) + (ny * 2 + 1)) / 2;
                if(map[midX][midY] != '0') {
                    pos = false;
                }
            }
        }
    }

    using vvi = vector<vector<int>>;
    auto compSize = [&](vvi& d) {
        int res = 0;
        auto tmp = d;
        int n = tmp.size(), m = tmp[0].size();
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                if(tmp[i][j] == 1) {
                    if(res != 0) {
                        res = -1;
                        break;
                    }

                    queue<pair<int, int>> q;
                    q.push({ i, j });
                    tmp[i][j] = 0;
                    while(!q.empty()) {
                        auto [x, y] = q.front(); q.pop();
                        res++;
                        for(int k = 0; k < 4; ++k) {
                            int nx = x + dx[k];
                            int ny = y + dy[k];
                            if(nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
                            if(tmp[nx][ny] == 0) continue;

                            tmp[nx][ny] = 0;
                            q.push({ nx, ny });
                        }
                    }
                }
            }
            if(res == -1) break;
        }

        return res;
    };

    auto crop = [](vvi& d) {
        int n = d.size(), m = d[0].size();

        int mnX = n, mxX = 0, mnY = m, mxY = 0;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                if(d[i][j] == 0) continue;
                mnX = min(mnX, i);
                mxX = max(mxX, i);
                mnY = min(mnY, j);
                mxY = max(mxY, j);
            }
        }
        vvi res = vector<vector<int>>(mxX - mnX + 1, vector<int>(mxY - mnY + 1));
        for(int i = mnX; i <= mxX; ++i) {
            for(int j = mnY; j <= mxY; ++j) {
                res[i - mnX][j - mnY] = d[i][j];
            }
        }
        d = move(res);
    };

    auto isSame = [](vvi& a, vvi& b) {
        int an = a.size(), am = a[0].size();
        int bn = b.size(), bm = b[0].size();

        if(an != bn || am != bm) return false;

        for(int i = 0; i < an; ++i) {
            for(int j = 0; j < am; ++j) {
                if(a[i][j] != b[i][j]) return false;
            }
        }
        return true;
    };

    auto rotate = [](vvi& d) {
        int n = d.size(), m = d[0].size();
        vector<vector<int>> res(m, vector<int>(n));

        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                res[j][n - i - 1] = d[i][j];
            }
        }

        d = move(res);
    };
    auto flip = [](vvi& d) {
        int n = d.size(), m = d[0].size();
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m / 2; ++j) {
                swap(d[i][j], d[i][m - 1 - j]);
            }
        }
    };

    vector<vector<int>> zero, one;
    for(auto& idx : areaIdx) {
        zero = vector<vector<int>>(n, vector<int>(n, 0));
        one = zero;

        int zeroFixSz = -1, oneFixSz = -1;

        for(auto [x, y] : idx) {
            if(d[x][y] == 0) {
                zero[x][y] = 1;
                if(d2[x][y] > 0) {
                    if(zeroFixSz != -1) pos = false;
                    zeroFixSz = d2[x][y];
                }
            }
            else {
                one[x][y] = 1;
                if(d2[x][y] > 0) {
                    if(oneFixSz != -1) pos = false;
                    oneFixSz = d2[x][y];
                }
            }
        }

        int zeroSz = compSize(zero);
        int oneSz = compSize(one);
        if(zeroSz <= 0 || oneSz <= 0 || zeroSz != oneSz) {
            pos = false;
            break;
        }
        if(zeroFixSz != -1 && oneFixSz != -1) {
            pos = false;
            break;
        }
        if(zeroFixSz != -1 && zeroFixSz != zeroSz) {
            pos = false;
            break;
        }
        if(oneFixSz != -1 && oneFixSz != oneSz) {
            pos = false;
            break;
        }

        crop(zero);
        crop(one);

        bool f = false;
        rotate(one);
        if(isSame(zero, one)) f = true;
        rotate(one);
        if(isSame(zero, one)) f = true;
        rotate(one);
        if(isSame(zero, one)) f = true;
        rotate(one);
        if(isSame(zero, one)) f = true;
        
        flip(one);
        rotate(one);
        if(isSame(zero, one)) f = true;
        rotate(one);
        if(isSame(zero, one)) f = true;
        rotate(one);
        if(isSame(zero, one)) f = true;
        rotate(one);
        if(isSame(zero, one)) f = true;
        
        if(!f) {
            pos = false;
        }
    }

    if(pos) cout << "1";
    else cout << "0";
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
