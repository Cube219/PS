#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <queue>
#include <functional>
using namespace std;

using ll = long long int;

int tNum;
int n, k;
char str[100005];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        while(pq.empty() == false) pq.pop();

        cin >> n >> k >> str;

        int idx = 0, cnt = -1;
        for(int i = 0; i < n; i++) {
            if(str[i] == 'W') {
                if(cnt != -1 && idx != 0) {
                    pq.push({cnt, idx});
                }
                cnt = -1;
            } else {
                if(cnt == -1) {
                    idx = i;
                    cnt = 0;
                }
                cnt++;
            }
        }
        /*
        if(cnt != -1) {
            pq.push({ cnt, idx });
        }*/

        while(pq.empty() == false && k > 0) {
            auto p = pq.top();
            pq.pop();
            for(int i = 0; i < p.first; i++) {
                str[p.second + i] = 'W';
                k--;
                if(k <= 0) break;
            }
        }
        if(k > 0) {
            int st = 0;
            for(; st < n; st++) {
                if(str[st] == 'W') break;
            }
            for(int i = st - 1; i >= 0; i--) {
                str[i] = 'W';
                k--;
                if(k <= 0) break;
            }

            if(k > 0) {
                int ed = n - 1;
                for(; ed >= 0; ed--) {
                    if(str[ed] == 'W') break;
                }
                for(int i = ed + 1; i < n; i++) {
                    str[i] = 'W';
                    k--;
                    if(k <= 0) break;
                }
            }
        }

        int res = 0;
        bool preWin = false;
        for(int i = 0; i < n; i++) {
            if(str[i] == 'W') {
                if(preWin == true) {
                    res += 2;
                } else {
                    res++;
                }
                preWin = true;
            } else {
                preWin = false;
            }
        }
        cout << res << "\n";
    }

    return 0;
}
