#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

using ll = long long int;

struct Node
{
    int a, b, c;
};

int n, m, h;
int m1[105][105], m2[105][105];
int d1[105][105], d2[105][105];
bool has[105][105][105];
vector<Node> r1, r2;

void print(vector<Node>& r)
{
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            for(int k = 0; k < h; ++k) {
                if(has[i][j][k] == true) {
                    r.push_back({ i, j, k });
                }
            }
        }
    }
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> h;
    for(int i = 0; i < n; ++i) {
        string str;
        cin >> str;
        for(int j = 0; j < m; ++j) {
            m1[i][j] = str[j] - '0';
        }
    }
    for(int i = 0; i < n; ++i) {
        string str;
        cin >> str;
        for(int j = 0; j < h; ++j) {
            m2[i][j] = str[j] - '0';
        }
    }

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(m1[i][j] == 0) continue;
            for(int k = 0; k < h; ++k) {
                if(has[i][j][k] == true) continue;
                if(m2[i][k] == 1) {
                    has[i][j][k] = true;
                    d1[i][j]++;
                    d2[i][k]++;
                }
            }
        }
    }

    for(int i = 0; i < n; ++i) {
        for(int k = 0; k < h; ++k) {
            if(m2[i][k] == 0) continue;
            for(int j = 0; j < m; ++j) {
                if(has[i][j][k] == true) continue;
                if(m1[i][j] == 1) {
                    has[i][j][k] = true;
                    d1[i][j]++;
                    d2[i][k]++;
                }
            }
        }
    }

    print(r1);

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            for(int k = 0; k < h; ++k) {
                has[i][j][k] = false;
            }
        }
    }

    bool pos = true;
    for(int i = 0; i < n; ++i) {
        vector<int> js, ks;
        for(int j = m - 1; j >= 0; --j) {
            if(m1[i][j] == 1) js.push_back(j);
        }
        for(int k = h - 1; k >= 0; --k) {
            if(m2[i][k] == 1) ks.push_back(k);
        }

        if((js.size() > 0 && ks.size() == 0) || (js.size() == 0 && ks.size() > 0)) {
            pos = false;
            break;
        }

        if(js.size() > ks.size()) {
            while(js.size() != ks.size()) {
                has[i][js.back()][ks.back()] = true;
                js.pop_back();
            }
        } else if(js.size() < ks.size()) {
            while(js.size() != ks.size()) {
                has[i][js.back()][ks.back()] = true;
                ks.pop_back();
            }
        }
        while(js.size() > 0) {
            has[i][js.back()][ks.back()] = true;
            js.pop_back();
            ks.pop_back();
        }
    }

    print(r2);

    if(pos == false) {
        cout << "-1\n";
    } else {
        cout << r1.size() << "\n";
        int sz = r1.size();
        for(int i = 0; i < sz; ++i) {
            cout << r1[i].a << " " << r1[i].b << " " << r1[i].c << "\n";
        }
        cout << r2.size() << "\n";
        sz = r2.size();
        for(int i = 0; i < sz; ++i) {
            cout << r2[i].a << " " << r2[i].b << " " << r2[i].c << "\n";
        }
    }

    return 0;
}
