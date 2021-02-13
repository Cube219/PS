#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;

using ll = long long int;

int n;
char str[101][20];
int strl[101];

bool has[30];
int cnt;
bool ck[30][30];

vector<int> g[30];
int in[30];
queue<int> q;

vector<int> res;
bool many = false;
bool imp = false;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> str[i];
        strl[i] = strlen(str[i]);

        for(int j = 0; j < strl[i]; ++j) {
            int a = str[i][j] - 'a';
            if(has[a] == false) {
                has[a] = true;
                cnt++;
            }
        }
    }

    for(int i = 0; i < n - 1; ++i) {
        for(int j = i + 1; j < n; ++j) {
            int l = min(strl[i], strl[j]);
            for(int k = 0; k <= l; ++k) {
                int a = str[i][k] - 'a';
                int b = str[j][k] - 'a';

                if(k == l && strl[i] > strl[j]) {
                    imp = true;
                    break;
                } else if(k == l) {
                    break;
                }

                if(a == b) continue;
                if(ck[a][b] == true) break;

                g[a].push_back(b);
                in[b]++;
                ck[a][b] = true;
                break;
            }
        }
    }

    for(int i = 0; i < 30; ++i) {
        if(has[i] == true && in[i] == 0) {
            q.push(i);
        }
    }

    while(q.empty() == false) {
        if(q.size() > 1) {
            many = true;
            break;
        }

        int cur = q.front();
        q.pop();

        res.push_back(cur);

        for(auto nxt : g[cur]) {
            in[nxt]--;
            if(in[nxt] == 0) {
                q.push(nxt);
            }
        }
    }

    if(many == true && imp == false) {
        cout << "?";
        return 0;
    }
    if(imp == true || res.size() != cnt) {
        cout << "!";
        return 0;
    }
    for(int i = 0; i < cnt; ++i) {
        cout << (char)('a' + res[i]);
    }

    return 0;
}
