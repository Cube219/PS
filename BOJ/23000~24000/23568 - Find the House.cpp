#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <unordered_map>
using namespace std;

using ll = long long int;

struct Node
{
    char dir;
    ll k;
};

int n;
ll pos;
unordered_map<int, Node> mp;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        int pos, k;
        char dir;
        cin >> pos >> dir >> k;
        mp[pos] = { dir, k };
    }

    cin >> pos;
    while(1) {
        auto it = mp.find(pos);
        if(it == mp.end()) break;

        if(it->second.dir == 'L') pos -= it->second.k;
        else pos += it->second.k;
    }
    cout << pos;

    return 0;
}
