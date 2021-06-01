#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

using ll = long long int;

int n;
vector<string> dd, d;
vector<int> nxt[31];
int pnum[31];
bool has[31];
char res[31];
bool pos = true;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    d.resize(n);
    dd.resize(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> dd[i];
    }
    for(int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        d[i] = dd[a];
    }

    for(int i = 0; i < n - 1; ++i) {
        for(int j = i + 1; j < n; ++j) {
            int sz = min(d[i].size(), d[j].size());
            bool f = false;
            for(int k = 0; k < sz; ++k) {
                if(d[i][k] != d[j][k]) {
                    int a = d[i][k] - 'a';
                    int b = d[j][k] - 'a';
                    nxt[a].push_back(b);
                    pnum[b]++;
                    has[a] = true;
                    has[b] = true;
                    f = true;
                    break;
                }
            }
            if(f == false && d[i].size() > d[j].size()) {
                pos = false;
            }
        }
    }

    int anum = 0;
    queue<int> q;
    for(int i = 0; i < 26; ++i) {
        if(has[i] == true) {
            anum++;
            if(pnum[i] == 0) q.push(i);
        }
    }
    int curchar = 'a';
    while(q.empty() == false) {
        int cur = q.front();
        q.pop();
        anum--;
        res[cur] = curchar;
        curchar++;
        for(int nx : nxt[cur]) {
            pnum[nx]--;
            if(pnum[nx] == 0) {
                q.push(nx);
            }
        }
    }
    if(pos == false || anum > 0) {
        cout << "NE";
    } else {
        for(int i = 0; i < 26; ++i) {
            if(has[i] == false) {
                res[i] = curchar;
                curchar++;
            }
        }
        cout << "DA\n";
        for(int i = 0; i < 26; ++i) {
            cout << res[i];
        }
    }

    return 0;
}
