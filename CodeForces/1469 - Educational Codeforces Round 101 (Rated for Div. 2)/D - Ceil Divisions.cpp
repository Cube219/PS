#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <math.h>
#include <vector>
using namespace std;

using ll = long long int;

int tNum;
int n;
vector<pair<int, int>> res;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        res.clear();

        cin >> n;
        while(n > 2) {
            float b = sqrtf(n);
            int bl = ceil(b);

            for(int i = n - 1; i > bl; i--) {
                res.push_back({ i, n });
            }
            res.push_back({ n, bl });
            res.push_back({ n, bl });
            n = bl;
        }

        cout << res.size() << "\n";
        for(int i = 0; i < res.size(); i++) {
            cout << res[i].first << " " << res[i].second << "\n";
        }
    }

    return 0;
}
