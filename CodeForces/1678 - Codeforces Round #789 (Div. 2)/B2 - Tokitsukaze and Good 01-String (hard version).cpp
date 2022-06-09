#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n;
    string str;
    cin >> n >> str;

    vector<char> isFlip(n, false);
    string str2 = str;
    str2[0] = str[0];
    int cnt = 1;
    int res1 = 0;
    for(int i = 1; i < n; ++i) {
        if(str[i - 1] != str[i]) {
            if(cnt & 1) {
                isFlip[i] = true;
                cnt = -1;
                res1++;
            }
        }
        cnt++;
        str2[i] = str[i];
        if(isFlip[i]) {
            if(str2[i] == '0') str2[i] = '1';
            else str2[i] = '0';
        }
    }

    struct Seg
    {
        char bit;
        int cnt;
        int fNum;
    };
    vector<Seg> seg;
    int num = 1, fNum = 0;
    for(int i = 1; i < n; ++i) {
        if(str2[i - 1] != str2[i]) {
            seg.push_back({ str2[i - 1], num, fNum });
            num = 0;
            fNum = 0;
        }
        num++;
        if(isFlip[i]) fNum++;
    }
    seg.push_back({ str2[n - 1], num, fNum });

    int r2 = 1;
    char lastBit = 0;
    for(auto& s : seg) {
        if(s.cnt / 2 == s.fNum) continue;

        if(lastBit != 0 && lastBit != s.bit) {
            r2++;
        }
        lastBit = s.bit;

    }

    cout << res1 << " " << r2 << "\n";
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tNum = 1;
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
