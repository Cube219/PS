#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

ll p, a, b;
vector<vector<ll>> map;
int n, m;
vector<ll> row, col;
vector<ll> res;
bool has[100001];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> p >> a >> b;

    row.push_back(1);
    while(1) {
        ll nxt = row.back();
        nxt = (nxt * a) % p;
        if(nxt == 1) break;
        row.push_back(nxt);
    }
    col.push_back(1);
    while(1) {
        ll nxt = col.back();
        nxt = (nxt * b) % p;
        if(nxt == 1) break;
        col.push_back(nxt);
    }
    bool iscan = false;
    if((p - 1) % row.size() == 0) {
        n = row.size();
        m = (p - 1) / row.size();
        if(m <= col.size()) iscan = true;
    }
    if(iscan == false && (p - 1) % col.size() == 0) {
        n = col.size();
        m = (p - 1) / col.size();
        if(m <= row.size()) {
            iscan = true;
            row = col;
            b = a;
        }
    }
    if(iscan == false) {
        cout << "No";
        return 0;
    }

    map.resize(n);
    for(int i = 0; i < n; ++i) {
        map[i].resize(m);
        map[i][0] = row[i];
        if(has[map[i][0]] == true) {
            cout << "No";
            return 0;
        }
        has[map[i][0]] = true;
        for(int j = 1; j < m; ++j) {
            map[i][j] = (map[i][j - 1] * b) % p;
            if(has[map[i][j]] == true) {
                cout << "No";
                return 0;
            }
            has[map[i][j]] = true;
        }
    }

    for(int j = 0; j < m; ++j) {
        res.push_back(map[0][j]);
    }
    for(int j = m - 1; j >= 0; --j) {
        if((m % 2 == 0 && j % 2 == 1) || (m % 2 == 1 && j % 2 == 0)) {
            for(int i = 1; i < n; ++i) {
                res.push_back(map[i][j]);
            }
        } else {
            for(int i = n - 1; i >= 1; --i) {
                res.push_back(map[i][j]);
            }
        }
    }
    res.push_back(1);

    cout << "Yes\n";
    for(int i = 0; i < res.size(); ++i) {
        cout << res[i] << " ";
    }

    return 0;
}
