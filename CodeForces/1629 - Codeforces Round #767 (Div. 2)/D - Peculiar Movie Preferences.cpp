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
    int n;
    cin >> n;
    vector<string> d(n);
    for(auto& v : d) cin >> v;

    bool res = false;
    vector<string> two, three;
    for(auto& v : d) {
        if(v.size() == 1) {
            res = true;
            break;
        } else if(v.size() == 2) {
            if(v[0] == v[1]) {
                res = true;
                break;
            }
            two.push_back(v);
        } else if(v.size() == 3) {
            if(v[0] == v[2]) {
                res = true;
                break;
            }
            three.push_back(v);
        }
    }

    if(res == false) {
        vector<char> has2(1001, false);
        vector<char> has23(1001, false);
        vector<char> has3(26 * 26 * 26, false);

        for(auto& v : d) {
            if(v.size() == 2) {
                int key = (v[1] - 'a') * 26 + (v[0] - 'a');
                // 2-2
                if(has2[key]) {
                    res = true;
                    break;
                }
                // 3-2
                if(has23[key]) {
                    res = true;
                    break;
                }

                key = (v[0] - 'a') * 26 + (v[1] - 'a');
                has2[key] = true;
            } else if(v.size() == 3) {
                int key = (v[2] - 'a') * 676 + (v[1] - 'a') * 26 + (v[0] - 'a');
                // 3-3
                if(has3[key]) {
                    res = true;
                    break;
                }

                // 2-3
                key = (v[2] - 'a') * 26 + (v[1] - 'a');
                if(has2[key]) {
                    res = true;
                    break;
                }

                key = (v[0] - 'a') * 676 + (v[1] - 'a') * 26 + (v[2] - 'a');
                has3[key] = true;
                key = (v[0] - 'a') * 26 + (v[1] - 'a');
                has23[key] = true;
            }
        }
    }

    if(res) cout << "YES\n";
    else cout << "NO\n";
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
