#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

using ll = long long int;

struct Node
{
    int gt, lt;
};

int tNum;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        int n;
        cin >> n;
        vector<Node> d(n);
        for(auto& v : d) cin >> v.gt >> v.lt;

        auto ck = [&](int k) {
            int cnt = 0;
            for(auto& v : d) {
                if(v.lt < cnt) continue;
                int gt = k - cnt - 1;
                if(v.gt < gt) continue;
                cnt++;
            }
            return cnt >= k;
        };

        int lo = 1, hi = n + 1;
        while(lo + 1 < hi) {
            int m = (lo + hi) / 2;
            if(ck(m)) lo = m;
            else hi = m;
        }
        cout << lo << "\n";
    }

    return 0;
}
