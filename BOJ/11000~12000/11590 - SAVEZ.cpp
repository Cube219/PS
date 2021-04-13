#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <math.h>
#include <string>
#include <map>
using namespace std;

using ll = long long int;

int ctoi(char c1, char c2)
{
    int a1 = (int)(c1 - 'A') * 26;
    int a2 = c2 - 'A';
    return a1 + a2;
}

struct Node
{
    Node() : v(0) {}
    map<string, Node*> nxt;
    int v;

    int insert(const string& str, int idx, int sz)
    {
        if(idx == sz) {
            v++;
            return v;
        }
        string key;
        key.push_back(str[idx]);
        key.push_back(str[sz - idx - 1]);
        if(nxt.find(key) == nxt.end()) {
            nxt[key] = new Node();
        }
        int ret = nxt[key]->insert(str, idx + 1, sz);
        v = max(v, ret);
        return v;
    }
};

int n;
vector<string> strs;
int sl;
Node* root;
int res = 0;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    root = new Node();

    cin >> n;
    strs.resize(n);
    for(int i = 0; i < n; ++i) {
        cin >> strs[i];
    }

    for(int i = n - 1; i >= 0; --i) {
        res = max(res, root->insert(strs[i], 0, strs[i].size()));
    }

    cout << res;

    return 0;
}
