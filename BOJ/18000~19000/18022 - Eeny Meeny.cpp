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

int n;
vector<string> res[2];
int cnt;
vector<string> d;
bool isend[101];

int nxt(int cur)
{
    while(1) {
        cur++;
        cur %= n;
        if(isend[cur] == false) break;
    }
    return cur;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string str;
    getline(cin, str);
    cnt = 1;
    for(int i = 0; i < str.size(); ++i) {
        if(str[i] == ' ') cnt++;
    }
    cin >> n;
    d.resize(n);
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
    }
    int cur = -1;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < cnt; ++j) {
            cur = nxt(cur);
        }
        res[i % 2].push_back(d[cur]);
        isend[cur] = true;
    }
    cout << res[0].size() << "\n";
    for(int i = 0; i < res[0].size(); ++i) {
        cout << res[0][i] << "\n";
    }
    cout << res[1].size() << "\n";
    for(int i = 0; i < res[1].size(); ++i) {
        cout << res[1][i] << "\n";
    }

    return 0;
}
