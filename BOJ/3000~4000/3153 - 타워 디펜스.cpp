#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, m;
char map[102][102];
int tMap[102][102], tNum;
vector<int> g[40004];
int lr[40004], ud[40004];

int rev(int v)
{
    if(v % 2 == 0) return v - 1;
    else return v + 1;
}

int fireL(int t)
{
    return t * 4 - 3;
}
int fireR(int t)
{
    return t * 4 - 2;
}
int fireU(int t)
{
    return t * 4 - 1;
}
int fireD(int t)
{
    return t * 4;
}

void process(int x, int y)
{
    int cnt = 0;
    int lt = -1, rt = -1, ut = -1, dt = -1;

    int cx = x;
    int cy = y + 1;
    while(cy < m) {
        if(map[cx][cy] == 'T') {
            cnt++;
            rt = tMap[cx][cy];
            break;
        }
        if(map[cx][cy] == '#') break;
        cy++;
    }
    cy = y - 1;
    while(cy >= 0) {
        if(map[cx][cy] == 'T') {
            cnt++;
            lt = tMap[cx][cy];
            break;
        }
        if(map[cx][cy] == '#') break;
        cy--;
    }
    cx = x + 1;
    cy = y;
    while(cx < n) {
        if(map[cx][cy] == 'T') {
            cnt++;
            dt = tMap[cx][cy];
            break;
        }
        if(map[cx][cy] == '#') break;
        cx++;
    }
    cx = x - 1;
    while(cx >= 0) {
        if(map[cx][cy] == 'T') {
            cnt++;
            ut = tMap[cx][cy];
            break;
        }
        if(map[cx][cy] == '#') break;
        cx--;
    }

    if(cnt == 1) {
        int a;
        if(lt != -1) {
            a = fireR(lt);
        } else if(rt != -1) {
            a = fireL(rt);
        } else if(ut != -1) {
            a = fireD(ut);
        } else { // dt != -1
            a = fireU(dt);
        }
        g[rev(a)].push_back(a);
    } else if(cnt == 2) {
        vector<int> ab;
        if(lt != -1) {
            ab.push_back(fireR(lt));
        }
        if(rt != -1) {
            ab.push_back(fireL(rt));
        }
        if(ut != -1) {
            ab.push_back(fireD(ut));
        }
        if(dt != -1) {
            ab.push_back(fireU(dt));
        }
        int a = ab[0];
        int b = ab[1];
        g[rev(a)].push_back(b);
        g[rev(b)].push_back(a);
    } else { // cnt == 3
        int a, b, c;
        if(lt == -1) {
            a = fireU(ut);
            b = fireD(dt);
            c = fireL(rt);
        } else if(rt == -1) {
            a = fireU(ut);
            b = fireD(dt);
            c = fireR(lt);
        } else if(ut == -1) {
            a = fireL(lt);
            b = fireR(rt);
            c = fireU(dt);
        } else { // dt == -1
            a = fireL(lt);
            b = fireR(rt);
            c = fireD(ut);
        }
        g[rev(a)].push_back(a);
        g[rev(b)].push_back(b);
        g[rev(c)].push_back(c);
    }
}

void processT(int x, int y)
{
    int cx, cy;
    int t1, t2;
    t1 = tMap[x][y];
    cx = x;
    cy = y + 1;
    while(cy < m) {
        if(map[cx][cy] == 'T') {
            t2 = tMap[cx][cy];
            int a = fireL(t1);
            int b = fireR(t2);
            g[rev(a)].push_back(a);
            g[rev(b)].push_back(b);
        }
        if(map[cx][cy] == '#') break;
        cy++;
    }
    cy = y - 1;
    while(cy >= 0) {
        if(map[cx][cy] == 'T') {
            t2 = tMap[cx][cy];
            int a = fireR(t1);
            int b = fireL(t2);
            g[rev(a)].push_back(a);
            g[rev(b)].push_back(b);
        }
        if(map[cx][cy] == '#') break;
        cy--;
    }
    cx = x + 1;
    cy = y;
    while(cx < n) {
        if(map[cx][cy] == 'T') {
            t2 = tMap[cx][cy];
            int a = fireU(t1);
            int b = fireD(t2);
            g[rev(a)].push_back(a);
            g[rev(b)].push_back(b);
        }
        if(map[cx][cy] == '#') break;
        cx++;
    }
    cx = x - 1;
    while(cx >= 0) {
        if(map[cx][cy] == 'T') {
            t2 = tMap[cx][cy];
            int a = fireD(t1);
            int b = fireU(t2);
            g[rev(a)].push_back(a);
            g[rev(b)].push_back(b);
        }
        if(map[cx][cy] == '#') break;
        cx--;
    }
}

int d[40004], dNum = 1;
bool finish[40004];
vector<int> st;
vector<vector<int>> sccs;
int dfs(int cur)
{
    d[cur] = dNum++;
    st.push_back(cur);

    int ret = d[cur];
    for(int nxt : g[cur]) {
        if(d[nxt] == 0) ret = min(ret, dfs(nxt));
        else if(finish[nxt] == false) ret = min(ret, d[nxt]);
    }

    if(ret == d[cur]) {
        sccs.push_back({});
        auto& scc = sccs.back();
        while(1) {
            int top = st.back();
            st.pop_back();

            scc.push_back(top);
            finish[top] = true;

            if(top == cur) break;
        }
    }
    return ret;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < n; ++i) {
        cin >> map[i];
    }

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(map[i][j] == 'T') {
                tMap[i][j] = ++tNum;
            }
        }
    }

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(map[i][j] == 'n') {
                process(i, j);
            } else if(map[i][j] == 'T') {
                processT(i, j);
            }
        }
    }

    for(int i = 1; i <= tNum * 4; ++i) {
        sort(g[i].begin(), g[i].end());
        auto lastIt = unique(g[i].begin(), g[i].end());
        g[i].erase(lastIt, g[i].end());
    }

    for(int i = 1; i <= tNum * 4; ++i) {
        if(d[i] == 0) dfs(i);
    }

    for(int i = sccs.size() - 1; i >= 0; --i) {
        auto& scc = sccs[i];
        for(int j = 0; j < scc.size(); ++j) {
            int curT = (scc[j] - 1) / 4 + 1;
            int dir = (scc[j] - 1) % 4;

            if(dir == 0 || dir == 1) { // LR
                if(lr[curT] == 0) {
                    if(dir == 0) lr[curT] = 1;
                    else lr[curT] = -1;
                }
            } else { // UD
                if(ud[curT] == 0) {
                    if(dir == 2) ud[curT] = 1;
                    else ud[curT] = -1;
                }
            }
        }
    }

    int curT = 1;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(map[i][j] == 'T') {
                if(lr[curT] == -1) {
                    if(ud[curT] == -1) {
                        map[i][j] = '4';
                    } else {
                        map[i][j] = '1';
                    }
                } else {
                    if(ud[curT] == -1) {
                        map[i][j] = '3';
                    } else {
                        map[i][j] = '2';
                    }
                }
                curT++;
            }
        }
    }
    for(int i = 0; i < n; ++i) {
        cout << map[i] << "\n";
    }

    return 0;
}
