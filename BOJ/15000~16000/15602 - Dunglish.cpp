#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

using ll = long long int;

int n, m;
vector<string> d;
unordered_map<string, pair<int, int>> mp;
unordered_map<string, string> mp2;

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
    }
    cin >> m;
    for(int i = 0; i < m; ++i) {
        string a, b, c;
        cin >> a >> b >> c;

        auto it = mp.find(a);
        if(it == mp.end()) {
            it = mp.insert({ a, {0, 0 } }).first;
        }

        if(c[0] == 'c') {
            it->second.first++;
        } else {
            it->second.second++;
        }

        auto it2 = mp2.find(a);
        if(it2 == mp2.end()) {
            mp2.insert({ a, b });
        }
    }

    ll cnum = 1, totalnum = 1;
    for(int i = 0; i < n; ++i) {
        auto it = mp.find(d[i]);
        cnum *= it->second.first;
        totalnum *= (it->second.first + it->second.second);
    }

    if(totalnum == 1) {
        for(int i = 0; i < n; ++i) {
            auto it = mp2.find(d[i]);
            cout << it->second << " ";
        }
        cout << "\n";
        if(cnum == 1) cout << "correct";
        else cout << "incorrect";
    } else {
        cout << cnum << " correct\n";
        cout << totalnum - cnum << " incorrect";
    }

    return 0;
}
