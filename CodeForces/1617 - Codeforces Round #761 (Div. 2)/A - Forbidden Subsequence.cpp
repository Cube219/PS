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
        string s, t;
        cin >> s >> t;
        sort(s.begin(), s.end());
        if(t == "abc") {
            int anum = 0;
            int bnum = 0, cnum = 0;
            for(int i = 0; i < s.size(); ++i) {
                if(s[i] == 'a') anum++;
                if(s[i] == 'b') bnum++;
                if(s[i] == 'c') cnum++;
            }

            if(anum == 0 || bnum == 0 || cnum == 0) {
                cout << s << "\n";
            } else {
                int i = 0;
                while(s[i] < 'b' && i < s.size()) {
                    cout << s[i];
                    i++;
                }
                while(cnum > 0 && i < s.size()) {
                    cout << 'c';
                    i++;
                    cnum--;
                }
                while(bnum > 0 && i < s.size()) {
                    cout << 'b';
                    i++;
                    bnum--;
                }
                while(i < s.size()) {
                    cout << s[i];
                    i++;
                }
                cout << "\n";
            }
        } else {
            cout << s << "\n";
        }
    }

    return 0;
}
