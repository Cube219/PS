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
constexpr int INF = 987654321;

int tNum;
int num[30];

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

        vector<pair<char, int>> d;
        int oneidx = -1;
        for(int i = 0; i < 26; ++i) {
            if(num[i] > 0) {
                d.push_back({ i + 'a', num[i] });
            }
            if(num[i] == 1 && oneidx == -1) {
                oneidx = d.size() - 1;
            }
        }

        // 1개 있는 경우 (res = 0)
        if(oneidx != -1) {
            cout << d[oneidx].first;
            for(int i = 0; i < d.size(); ++i) {
                if(i == oneidx) continue;
                for(int j = 0; j < d[i].second; ++j) {
                    cout << d[i].first;
                }
            }
            cout << "\n";
            continue;
        }

        int remain = 0;
        for(int i = 1; i < d.size(); ++i) {
            remain += d[i].second;
        }
        // aababababa.. ( na - 2 <= 나머지) (res = 1)
        if(d[0].second - 2 <= remain) {
            for(int i = 0; i < 2; ++i) {
                cout << d[0].first;
            }
            d[0].second -= 2;
            int idx = 1;
            for(int i = 2; i < str.size(); ++i) {
                if(idx < d.size() && d[idx].second == 0) idx++;
                if(idx < d.size()) {
                    cout << d[idx].first;
                    d[idx].second--;
                }
                if(d[0].second > 0) {
                    cout << d[0].first;
                    d[0].second--;
                }
            }
            cout << "\n";
            continue;
        }

        // 3개이상 있는 경우 abaaaacbb... (res = 1)
        if(d.size() >= 3) {
            cout << d[0].first;
            d[0].second--;
            cout << d[1].first;
            d[1].second--;
            while(d[0].second > 0) {
                cout << d[0].first;
                d[0].second--;
            }

            cout << d[2].first;
            d[2].second--;
            for(int i = 1; i < d.size(); ++i) {
                while(d[i].second > 0) {
                    cout << d[i].first;
                    d[i].second--;
                }
            }
            cout << "\n";
            continue;
        }

        // 나머지 abbbbbaaa... (res = 1)
        cout << d[0].first;
        d[0].second--;
        if(d.size() > 1) {
            while(d[1].second > 0) {
                cout << d[1].first;
                d[1].second--;
            }
        }
        for(int i = 0; i < d.size(); ++i) {
            while(d[i].second > 0) {
                cout << d[i].first;
                d[i].second--;
            }
        }
        cout << "\n";
    }

    return 0;
}
