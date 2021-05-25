#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

using ll = long long int;

int tNum;
int n, m;
map<ll, pair<ll, string>> mp;
string d[12];
int score[12];
ll res;
string resstr;

string cur;

void bt(int idx)
{
    if(idx == m / 2) {
        ll key = 0;
        for(int i = 0; i < n; ++i) {
            int num = 0;
            for(int j = 0; j < idx; ++j) {
                if(cur[j] == d[i][j]) num++;
            }
            key *= 16;
            key += num;
        }
        auto it = mp.find(key);
        if(it == mp.end()) {
            it = mp.insert({ key, { 0, cur } }).first;
        }
        it->second.first++;
        return;
    }
    cur.push_back('0');
    bt(idx + 1);
    cur.pop_back();
    cur.push_back('1');
    bt(idx + 1);
    cur.pop_back();
}

void bt2(int idx)
{
    if(idx == m) {
        ll key = 0;
        for(int i = 0; i < n; ++i) {
            int num = 0;
            for(int j = m / 2; j < idx; ++j) {
                if(cur[j - m/2] == d[i][j]) num++;
            }
            key *= 16;
            key += score[i] - num;
        }
        auto it = mp.find(key);
        if(it != mp.end()) {
            res += it->second.first;
            if(res == 1) {
                resstr = it->second.second;
                resstr.insert(resstr.end(), cur.begin(), cur.end());
            }
        }
        return;
    }
    cur.push_back('0');
    bt2(idx + 1);
    cur.pop_back();
    cur.push_back('1');
    bt2(idx + 1);
    cur.pop_back();
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        mp.clear();
        res = 0;

        cin >> n >> m;
        for(int i = 0; i < n; ++i) {
            cin >> d[i] >> score[i];
        }
        bt(0);
        bt2(m / 2);

        if(res == 1) cout << resstr << "\n";
        else cout << res << " solutions\n";
    }

    return 0;
}
