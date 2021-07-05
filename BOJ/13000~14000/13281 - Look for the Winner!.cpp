#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n;
vector<pair<char, int>> d;
char l[101];

char ck(int remain)
{
    char winner = -1;
    for(int i = 0; i < d.size(); ++i) {
        d[i].second += remain;

        auto d2 = d;
        sort(d2.begin(), d2.end(), [](const auto& l, const auto& r) {
            return l.second > r.second;
        });
        d[i].second -= remain;

        if(d2[0].second == d2[1].second) return -1;
        if(winner == -1) winner = d2[0].first;
        else if(winner != d2[0].first) return -1;
    }
    return winner;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while(1) {
        cin >> n;
        if(n == 0) break;

        for(int i = 0; i < n; ++i) {
            cin >> l[i];
        }

        d.clear();
        d.push_back({ '?', 0 });

        int remain = n;
        char winner = -1;
        int rtime = 0;
        for(int i = 0; i < n; ++i) {
            char ch = l[i];
            for(int j = 0; j < d.size(); ++j) {
                if(d[j].first == ch) {
                    d[j].second++;
                    ch = 0;
                    break;
                }
            }
            if(ch != 0) {
                d.push_back({ ch, 1 });
            }

            remain--;
            char r = ck(remain);
            if(r != -1) {
                winner = r;
                rtime = i + 1;
                break;
            }
            
        }
        if(winner != -1) {
            cout << winner << " " << rtime << "\n";
        } else {
            cout << "TIE\n";
        }
    }

    return 0;
}
