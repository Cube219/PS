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
    vector<char> ja = { 'q', 'w', 'e', 'r', 't', 'a', 's', 'd', 'f', 'g', 'z', 'x', 'c', 'v' };
    auto isJa = [&](char ch) {
        for(char j : ja) if(j == ch) return true;
        return false;
    };

    int n;
    cin >> n;
    string str;
    cin >> str;

    // 0: 기본 / 1: 자음 / 2: 모음 / 3: 자음+모음 / 4: 자음+모음+자음
    int mode = 0;
    for(char ch : str) {
        bool j = isJa(ch);

        if(j) {
            switch(mode) {
                case 0:
                    mode = 1; break;
                case 1:
                    mode = 1; break;
                case 2:
                    mode = 1; break;
                case 3:
                    mode = 4; break;
                case 4:
                    mode = 1; break;
            }
        } else {
            switch(mode) {
                case 0:
                    mode = 2; break;
                case 1:
                    mode = 3; break;
                case 2:
                    mode = 2; break;
                case 3:
                    mode = 2; break;
                case 4: 
                    mode = 3; break;
            }
        }
    }

    if(mode == 4) cout << "1";
    else cout << "0";
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tNum = 1;
    // cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
