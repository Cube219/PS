#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, m;
vector<vector<int>> d;
int c[250001];
int idx[250001];
bool pos = true;

bool ck()
{
    for(int i = 0; i < n; ++i) {
        int cnt = 0;
        for(int j = 0; j < m; ++j) {
            if(c[j] != d[i][j]) cnt++;
        }
        if(cnt > 2) {
            bool ck = false;
            for(int j = idx[i] + 1; j < m; ++j) {
                if(c[j] != d[i][j]) {
                    c[j] = d[i][j];
                    idx[i] = j;
                    ck = true;
                    break;
                }
            }
            if(ck == false) pos = false;
            return false;
        }
    }
    return true;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    d.resize(n);
    for(int i = 0; i < n; ++i) {
        d[i].resize(m);
        idx[i] = -1;
        for(int j = 0; j < m; ++j) {
            cin >> d[i][j];
        }
    }

    for(int i = 0; i < m; ++i) {
        c[i] = d[0][i];
    }

    while(1) {
        bool r = ck();
        if(r == true || pos == false) break;
    }

    if(pos == false) {
        cout << "No";
    } else {
        cout << "Yes\n";
        for(int i = 0; i < m; ++i) {
            cout << c[i] << " ";
        }
    }

    return 0;
}
