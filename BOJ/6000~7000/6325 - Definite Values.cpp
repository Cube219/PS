#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

using ll = long long int;

int n;
unordered_map<string, int> mp;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tt = 0;
    while(1) {
        tt++;
        cin >> n;
        if(n == 0) break;

        mp.clear();
        mp.insert({ "a", 0 });

        for(int i = 0; i < n; ++i) {
            string s1, s2, eq;
            cin >> s1 >> eq >> s2;

            auto it1 = mp.find(s1);
            if(it1 == mp.end()) it1 = mp.insert({ s1, -1 }).first;
            auto it2 = mp.find(s2);
            if(it2 == mp.end()) it2 = mp.insert({ s2, -1 }).first;
            it1->second = it2->second;
        }

        cout << "Program #" << tt << "\n";
        vector<string> res;
        for(auto& it : mp) {
            if(it.second == 0) res.push_back(it.first);
        }
        sort(res.begin(), res.end());
        for(int i = 0; i < res.size(); ++i) {
            cout << res[i] << " ";
        }
        if(res.size() == 0) cout << "none";

        cout << "\n\n";
    }

    return 0;
}
