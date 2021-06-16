#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <map>
#include <string>
using namespace std;

using ll = long long int;

int tNum;
int n;
string str;
map<pair<int, int>, int> mp;

int gcd(int a, int b)
{
    if(a < b) swap(a, b);
    if(b == 0) return a;
    return gcd(b, a % b);
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        mp.clear();

        cin >> n >> str;

        int dnum = 0, knum = 0;
        for(int i = 0; i < n; ++i) {
            if(str[i] == 'D') dnum++;
            else knum++;
            int g = gcd(dnum, knum);

            pair<int, int> tmp = { dnum / g, knum / g };

            auto it = mp.find(tmp);
            if(it == mp.end()) {
                it = mp.insert({ tmp, 0 }).first;
            }
            it->second++;
            cout << it->second << " ";
        }
        cout << "\n";
    }

    return 0;
}
