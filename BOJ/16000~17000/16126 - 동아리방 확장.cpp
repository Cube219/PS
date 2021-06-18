#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

vector<int> g[20005];
int a[20005], b[20005];
bool isComp[20005];
bool bp(int cur)
{
    isComp[cur] = true;
    for(int nxt : g[cur]) {
        if(b[nxt] == -1) {
            a[cur] = nxt;
            b[nxt] = cur;
            return true;
        } else if(isComp[b[nxt]] == false) {
            bool f = bp(b[nxt]);
            if(f == true) {
                a[cur] = nxt;
                b[nxt] = cur;
                return true;
            }
        }
    }
    return false;
}

int n, m;
int map[101][101];
int d[101][101];
int num;
int dx[] = { 0, 1, 0, -1 };
int dy[] = { 1, 0, -1, 0 };
bool res;

bool valid()
{
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(map[i][j] != 2 && map[i][j] != 3 && map[i][j] != 4) return false;
        }
    }
    return true;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            cin >> map[i][j];
        }
    }

    res = valid();
    if(res == true) {
        int cnt = 0, cnt2 = 0;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                d[i][j] = num;
                if(map[i][j] == 2) num += 2;
                else num++;
            }
        }
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                if((i + j) % 2 == 1) {
                    if(map[i][j] == 2) cnt2 += 2;
                    else if(map[i][j] == 3) cnt2++;
                    continue;
                }

                if(map[i][j] == 2) cnt += 2;
                else if(map[i][j] == 3) cnt++;

                for(int k = 0; k < 4; ++k) {
                    int nx = i + dx[k];
                    int ny = j + dy[k];
                    if(nx < 0 || ny < 0 || nx >= n || ny >= m) continue;

                    if(map[i][j] == 2) {
                        if(map[nx][ny] == 2) {
                            // g[d[i][j]].push_back(d[nx][ny]);
                            // g[d[i][j]].push_back(d[nx][ny] + 1);
                            // g[d[i][j] + 1].push_back(d[nx][ny]);
                            // g[d[i][j] + 1].push_back(d[nx][ny] + 1);
                        } else if(map[nx][ny] == 3) {
                            g[d[i][j]].push_back(d[nx][ny]);
                            g[d[i][j] + 1].push_back(d[nx][ny]);
                        }
                    } else if(map[i][j] == 3) {
                        if(map[nx][ny] == 2) {
                            g[d[i][j]].push_back(d[nx][ny]);
                            g[d[i][j]].push_back(d[nx][ny] + 1);
                        } else if(map[nx][ny] == 3) {
                            g[d[i][j]].push_back(d[nx][ny]);
                        }
                    }
                }
            }
        }

        // ----- 
        for(int i = 0; i < num; ++i) {
            a[i] = -1;
        }
        for(int i = 0; i < num; ++i) {
            b[i] = -1;
        }
        int nn = 0;
        for(int i = 0; i < num; ++i) {
            if(a[i] == -1) {
                for(int j = 0; j < num; ++j) {
                    isComp[j] = false;
                }
                if(bp(i) == true) nn++;
            }
        }
        if(nn != cnt || cnt != cnt2) res = false;
    }

    if(res == true) cout << "HAPPY";
    else cout << "HOMELESS";

    return 0;
}
