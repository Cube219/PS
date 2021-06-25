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

int n, k;
unordered_map<string, pair<int, int>> mp;
struct Node
{
    string str;
    int num;
    int idx;
};
vector<Node> d;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;
    string str;
    getline(cin, str);
    for(int i = 0; i < n * 3; ++i) {
        getline(cin, str);
        auto it = mp.find(str);
        if(it == mp.end()) {
            it = mp.insert({ str, {0, i} }).first;
        }
        it->second.first++;
        it->second.second = i;
    }
    for(auto& it : mp) {
        d.push_back({ it.first, it.second.first, it.second.second });
    }
    sort(d.begin(), d.end(), [](const Node& l, const Node& r) {
        if(l.num == r.num) return l.idx > r.idx;
        return l.num > r.num;
    });

    int rng = min(k, (int)d.size());
    for(int i = 0; i < rng; ++i) {
        cout << d[i].str << "\n";
    }

    return 0;
}
