#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <queue>
#include <vector>
#include <string>
using namespace std;

using ll = long long int;

int n;
vector<string> d;
vector<int> g[200001];
int indeg[200001], wnum[200001], lnum[200001];
int res[200001];

int getchnum(char ch)
{
    if(ch <= 'Z') return ch - 'A';
    return (ch - 'a') + 26;
}

int getnum(char a, char b, char c)
{
    int anum = getchnum(a);
    anum *= 52;
    anum *= 52;
    int bnum = getchnum(b);
    bnum *= 52;
    int cnum = getchnum(c);
    return anum + bnum + cnum;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    d.resize(n);
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
        int len = d[i].size();
        int from = getnum(d[i][0], d[i][1], d[i][2]);
        int to = getnum(d[i][len - 3], d[i][len - 2], d[i][len - 1]);
        g[to].push_back(from);
        indeg[from]++;
    }
    // 0 - draw / 1 - win / -1 - lose
    queue<int> q;
    for(int i = 0; i < 200000; ++i) {
        if(indeg[i] == 0) {
            res[i] = 1;
            q.push(i);
        }
    }

    while(q.empty() == false) {
        int cur = q.front();
        q.pop();

        for(int nxt : g[cur]) {
            if(res[nxt] != 0) continue;

            indeg[nxt]--;
            if(res[cur] == 1) {
                res[nxt] = -1;
                q.push(nxt);
            } else if(indeg[nxt] == 0) {
                res[nxt] = 1;
                q.push(nxt);
            }
        }
    }

    for(int i = 0; i < n; ++i) {
        int len = d[i].size();
        int to = getnum(d[i][len - 3], d[i][len - 2], d[i][len - 1]);

        if(res[to] == 0) cout << "Draw\n";
        else if(res[to] == 1) cout << "Takahashi\n";
        else cout << "Aoki\n";
    }

    return 0;
}
