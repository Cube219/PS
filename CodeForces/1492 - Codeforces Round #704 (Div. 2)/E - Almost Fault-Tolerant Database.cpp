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
bool pos = false;

int ck()
{
    int res = 0;
    for(int i = 0; i < n; ++i) {
        int cnt = 0;
        for(int j = 0; j < m; ++j) {
            if(c[j] != d[i][j]) cnt++;
        }
        if(res < cnt) res = cnt;
    }
    return res;
}

void bt2(int i, int remain)
{
    if(i == n) {
        int res = ck();
        if(res <= 2) {
            pos = true;
        }
        return;
    }

    vector<int> diff;
    for(int j = 0; j < m; ++j) {
        if(c[j] != d[i][j]) {
            diff.push_back(j);
        }
    }

    if(diff.size() <= 2) {
        bt2(i + 1, remain);
    } else if(diff.size() == 3 && remain >= 1) {
        for(int j = 0; j < diff.size(); ++j) {
            int tmp = c[diff[j]];
            c[diff[j]] = d[i][diff[j]];

            bt2(i + 1, remain - 1);
            if(pos == true) break;

            c[diff[j]] = tmp;
        }
    } else if(diff.size() == 4 && remain >= 2) {
        for(int j = 0; j < diff.size() - 1; ++j) {
            for(int k = j + 1; k < diff.size(); ++k) {
                int t1 = c[diff[j]];
                int t2 = c[diff[k]];
                c[diff[j]] = d[i][diff[j]];
                c[diff[k]] = d[i][diff[k]];

                bt2(i + 1, remain - 2);
                if(pos == true) break;

                c[diff[j]] = t1;
                c[diff[k]] = t2;
            }
            if(pos == true) break;
        }
    }
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

    int r = ck();
    if(r >= 5) {
        pos = false;
    } else if(r <= 2) {
        pos = true;
    } else {
        bt2(1, 2);
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
