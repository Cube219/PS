#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cassert>
#include <vector>
#include <string>
#include <map>

using namespace std;

using ll = long long int;

int s, l, n, d[100001];
vector<string> strs;
map<string, int> mp;
bool pairs[201][201];
bool use[100001], comp[201];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> s >> l >> n;
    strs.resize(s);
    for(int i = 0; i < s; ++i) {
        cin >> strs[i];
    }
    sort(strs.begin(), strs.end());
    for(int i = 0; i < s; ++i) {
        mp.insert({ strs[i], i });
    }
    for(int i = 0; i < l; ++i) {
        string s1, s2;
        cin >> s1 >> s2;
        int i1 = mp.find(s1)->second;
        int i2 = mp.find(s2)->second;

        pairs[i1][i2] = true;
        pairs[i2][i1] = true;
    }
    for(int i = 0; i < n; ++i) {
        string str;
        cin >> str;
        d[i] = mp.find(str)->second;
    }

    vector<int> res;
    vector<int> cur(s, -1);
    int num = n;
    while(num > 0){
        int mn = 201;
        for(int i = 0; i < s; ++i) {
            if(comp[i] == true) continue;
            while(1) {
                int nxt = cur[i] + 1;
                if(nxt == n) {
                    comp[i] = true;
                    break;
                }
                if(use[nxt] == true) {
                    cur[i]++;
                    continue;
                }
                if(d[nxt] == i) {
                    mn = min(mn, i);
                    break;
                }

                int h1 = i * 201 + d[nxt];
                if(pairs[i][d[nxt]] == false){
                    break;
                }
                cur[i]++;
            }
        }
        assert(mn != 201);
        res.push_back(mn);
        num--;
        use[cur[mn] + 1] = true;
    }

    for(int i = 0; i < n; ++i) {
        cout << strs[res[i]] << " ";
    }

    return 0;
}
