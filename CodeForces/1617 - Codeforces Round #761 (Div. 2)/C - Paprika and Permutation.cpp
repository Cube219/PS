#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tNum;
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        int n;
        cin >> n;
        vector<int> d(n);
        for(auto& v : d) cin >> v;
        sort(d.begin(), d.end());

        vector<int> ck(n + 1, 0);
        vector<int> remain;
        for(int i = 0; i < n; ++i) {
            if(d[i] > n) {
                remain.push_back(d[i]);
            } else if(ck[d[i]] == 1) {
                remain.push_back(d[i]);
            } else {
                ck[d[i]] = 1;
            }
        }
        reverse(remain.begin(), remain.end());

        int res = 0;
        for(int i = 1; i <= n; ++i) {
            if(ck[i] == 1) continue;

            if(remain.size() == 0) break;

            int rng = (remain.back() + 1) / 2 - 1;
            if(rng < i) {
                res = -1;
                break;
            }
            res++;
            remain.pop_back();
        }

        cout << res << "\n";
    }

    return 0;
}
