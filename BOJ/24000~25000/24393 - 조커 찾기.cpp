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

void solve()
{
    auto geta = [](const string& buf) {
        vector<int> res;
        int cur = 0;
        for(char ch : buf) {
            if(ch == ' ') {
                res.push_back(cur);
                cur = 0;
                continue;
            }
            if(ch == '\n') {
               // break;
            }
            cur *= 10;
            cur += ch - '0';
        }
        res.push_back(cur);

        return res;
    };

    int n;
    cin >> n;
    string buf;
    getline(cin, buf);
    int pos = 1;
    for(int i = 0; i < n; ++i) {
        getline(cin, buf);
        auto a = geta(buf);

        bool isRight = false;
        if(pos > 13) {
            isRight = true;
            pos -= 13;
        }

        int newpos = 0;
        for(int j = 0; j < a.size(); ++j) {
            if(j & 1) {
                // 왼쪽
                if(isRight == false) {
                    if(pos - a[j] <= 0) {
                        pos = newpos + pos;
                        break;
                    }
                    pos -= a[j];
                }
                newpos += a[j];
            } else {
                // 오른쪽
                if(isRight == true) {
                    if(pos - a[j] <= 0) {
                        pos = newpos + pos;
                        break;
                    }
                    pos -= a[j];
                }
                newpos += a[j];
            }
        }
    }
    cout << pos;
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
