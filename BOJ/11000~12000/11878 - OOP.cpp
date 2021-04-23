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

struct Node
{
    vector<size_t> sufhash;
    Node* nxt[26];
    int st, ed;
    void init()
    {
        for(int i = 0; i < 26; ++i) {
            nxt[i] = nullptr;
        }
    }
    void insert(const string& str, int idx)
    {
        if(idx == str.size()) {
            sufhash.push_back(hash<string>{}(""));
            return;
        }
        sufhash.push_back(hash<string>{}(str.substr(idx)));

        char ch = str[idx] - 'a';
        if(nxt[ch] == nullptr) {
            nxt[ch] = new Node();
            nxt[ch]->init();
        }

        nxt[ch]->insert(str, idx + 1);
    }
};

int n, q;
Node* root;
unordered_map<size_t, vector<int>> nodemap;

int num;
void dfs(Node* cur)
{
    cur->st = num;
    for(auto& s : cur->sufhash) {
        nodemap[s].push_back(num);
    }
    cur->sufhash.clear();

    num++;

    for(int i = 0; i < 26; ++i) {
        if(cur->nxt[i] == nullptr) continue;
        dfs(cur->nxt[i]);
    }
    cur->ed = num - 1;
}

pair<int, int> getnoderange(Node* cur, const string& pre, int idx)
{
    if(idx == pre.size()) {
        return { cur->st, cur->ed };
    }
    char ch = pre[idx] - 'a';
    if(cur->nxt[ch] == nullptr) return { -1, -1 };

    return getnoderange(cur->nxt[ch], pre, idx + 1);
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    root = new Node();
    root->init();

    cin >> n >> q;
    for(int i = 0; i < n; ++i) {
        string str;
        cin >> str;
        root->insert(str, 0);
    }
    dfs(root);

    for(int i = 0; i < q; ++i) {
        string str;
        cin >> str;
        int pivot = 0;
        for(; pivot < str.size(); pivot++) {
            if(str[pivot] == '*') {
                break;
            }
        }
        string pre = str.substr(0, pivot);
        string suf = str.substr(pivot + 1);

        auto node = getnoderange(root, pre, 0);
        int res = 0;
        if(node.first >= 0) {
            auto& nodelist = nodemap[hash<string>{}(suf)];
            res = upper_bound(nodelist.begin(), nodelist.end(), node.second) - lower_bound(nodelist.begin(), nodelist.end(), node.first);
        } else {
            res = 0;
        }
        cout << res << "\n";
    }

    return 0;
}
