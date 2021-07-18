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

int tNum;
int num[30];
vector<pair<int, int>> d;

int p(int idx)
{
    int remain = 0;
    for(int i = 0; i < d.size(); ++i) {
        if(i == idx) continue;
        remain += d[i].second;
    }

    int res = 0;

    if(d[idx].second == 1) {
        res = 1;
    } else {
        for(int i = 2; i <= d[idx].second; ++i) {
            int cnt = d[idx].second - i;
            int req = (cnt - 1) / (i - 1) + 1;
            if(remain >= req) {
                res = i;
                break;
            }
        }
    }

    return res;
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
        string str;
        cin >> str;

        for(int i = 0; i < 30; ++i) {
            num[i] = 0;
        }
        for(int i = 0; i < str.size(); ++i) {
            num[str[i] - 'a']++;
        }

        d.clear();
        for(int i = 0; i < 26; ++i) {
            if(num[i] > 0) {
                d.push_back({ i, num[i] });
            }
        }

        int res = 987654321, residx = 0;
        for(int i = 0; i < d.size(); ++i) {
            int r = p(i);
            if(res > r) {
                res = r;
                residx = i;
            }
        }

        for(int i = 0; i < res; ++i) {
            cout << (char)(d[residx].first + 'a');
        }
        int ridx = 0;
        if(residx == 0) ridx = 1;
        for(int i = res; i < d[residx].second; ++i) {
            if(ridx < d.size()) {
                cout << (char)(d[ridx].first + 'a');
                d[ridx].second--;
                if(d[ridx].second == 0) {
                    ridx++;
                    if(ridx == residx) ridx++;
                }
            }
            cout << (char)(d[residx].first + 'a');
        }
        while(ridx < d.size()) {
            cout << (char)(d[ridx].first + 'a');
            d[ridx].second--;
            if(d[ridx].second == 0) {
                ridx++;
                if(ridx == residx) ridx++;
            }
        }
        cout << "\n";
    }

    return 0;
}
