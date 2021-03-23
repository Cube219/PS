#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int tNum;
int n, m;
pair<int, int> d[1001];
int res;
bool isSet[1001];

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        res = 0;
        cin >> n >> m;
        for(int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            d[i] = { a, b };
        }
        for(int i = 1; i <= n; ++i) {
            isSet[i] = false;
        }
        sort(d, d + m, [](const auto& l, const auto& r) {
            if(l.second == r.second) return l.first < r.first;
            return l.second < r.second;
        });

        int curIdx = 1;
        for(int i = 0; i < m; ++i) {
            if(d[i].second < curIdx) continue;

            int st = max(curIdx, d[i].first);
            for(int j = st; j <= d[i].second; ++j) {
                if(isSet[j] == false) {
                    res++;
                    isSet[j] = true;
                    break;
                }
            }
            while(curIdx <= n && isSet[curIdx] == true) curIdx++;
            if(curIdx > n) break;
        }

        cout << res << "\n";
    }

    return 0;
}
