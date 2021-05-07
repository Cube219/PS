#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <queue>
using namespace std;

using ll = long long int;

struct Dot
{
    int x;
    int isend;
    int idx;
};
struct Line
{
    int st, ed;
};

int n;
ll l;
Line d[100001];
Dot p[200001];
int tb[100001][30];
ll len[100001][30];

void processList(vector<int>& stlist, vector<int>& edlist, set<int>& alive)
{
    // 들어가는 선 지우기
    for(int j = 0; j < stlist.size(); ++j) {
        alive.erase(stlist[j]);
    }
    // 나가는 선 처리
    for(int j = 0; j < edlist.size(); ++j) {
        int curidx = edlist[j];
        auto it = alive.upper_bound(curidx);
        if(it == alive.end()) {
            if(alive.size() == 0) {
                tb[curidx][0] = curidx;
                len[curidx][0] = l * 2;
                continue;
            }
            it = alive.begin();
        }
        tb[curidx][0] = *it;
        len[curidx][0] = d[*it].ed - d[curidx].ed;
        if(len[curidx][0] < 0) {
            len[curidx][0] += l;
        }
    }
    // 나가는 선 추가
    for(int j = 0; j < edlist.size(); ++j) {
        alive.insert(edlist[j]);
    }
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> l;
    for(int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        if(a > b) swap(a, b);
        if(b - a > l / 2) {
            swap(a, b);
        }
        d[i] = { a, b };
    }

    sort(d, d + n, [](const Line& l, const Line& r) {
        return l.ed < r.ed;
    });
    for(int i = 0; i < n; ++i) {
        p[i * 2] = { d[i].st, 0, i };
        p[i * 2 + 1] = { d[i].ed, 1, i };
    }
    sort(p, p + n * 2, [](const Dot& l, const Dot& r) {
        if(l.x == r.x) {
            return l.isend > r.isend;
        }
        return l.x < r.x;
    });
    set<int> alive;
    int initx = 0;
    for(int i = 0; i < n * 2; ++i) {
        if(p[i].isend == 1) {
            initx = p[i].x;
            break;
        }
    }
    for(int i = 0; i < n; ++i) {
        if(d[i].st < d[i].ed) {
            if(initx < d[i].st || d[i].ed < initx) alive.insert(i);
        } else {
            if(d[i].ed < initx && initx < d[i].st) alive.insert(i);
        }
    }
    vector<int> stlist, edlist;
    int lastx = -1;
    for(int i = 0; i < n * 2; ++i) {
        if(lastx != p[i].x) {
            processList(stlist, edlist, alive);
            stlist.clear();
            edlist.clear();

            lastx = p[i].x;
        }
        if(p[i].isend == 0) stlist.push_back(p[i].idx);
        else edlist.push_back(p[i].idx);
    }
    processList(stlist, edlist, alive);

    for(int j = 1; j < 30; ++j) {
        for(int i = 0; i < n; ++i) {
            int tmp = tb[i][j - 1];
            tb[i][j] = tb[tmp][j - 1];
            len[i][j] = len[i][j - 1] + len[tmp][j - 1];
            if(len[i][j] > l * 2) len[i][j] = l * 2;
        }
    }

    ll res = 987654321;
    for(int i = 0; i < n; ++i) {
        int cur = i;
        ll curlen = 0;
        ll cnt = 1;
        while(curlen < l) {
            bool updated = false;
            for(int j = 30 - 1; j >= 0; --j) {
                if(len[cur][j] + curlen >= l) {
                    res = min(res, cnt + (1LL << j) - 1);
                    continue;
                }
                curlen += len[cur][j];
                cur = tb[cur][j];
                cnt += 1LL << j;
                updated = true;
                break;
            }
            if(updated == false) break;
        }
    }
    cout << res;

    return 0;
}
