#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

struct Node;
int curnum;
int nodemaxdep[100001];
int res;
struct Node
{
    Node* nxt[26];
    int num, depth;
    void init(int dep)
    {
        for(int i = 0; i < 26; ++i) {
            nxt[i] = nullptr;
        }
        num = 0;
        depth = dep;
    }
    void insert(const string& str, int curidx)
    {
        if(num == 0) {
            num = curnum;
            nodemaxdep[num] = depth;
        }

        if(curidx == str.size()) return;

        char ch = str[curidx] - 'a';
        if(nxt[ch] == nullptr) {
            nxt[ch] = new Node();
            nxt[ch]->init(depth + 1);
        }
        nxt[ch]->insert(str, curidx + 1);
    }

    pair<int, int> process(const string& str, int curidx)
    {
        if(curidx == str.size()) return { num, 1 };

        char ch = str[curidx] - 'a';

        if(nxt[ch] == nullptr) {
            res = str.size() - curidx;
            return { num, 1 };
        }

        auto prenum = nxt[ch]->process(str, curidx + 1);    
        if(prenum.first == -1) prenum.first = num;
        if(prenum.first == num) {
            prenum.second++;
            return prenum;
        }

        int r1 = prenum.second;
        int r2 = nodemaxdep[prenum.first] - depth - prenum.second + 2;
        res += min(r1, r2);
        return { num, 1 };
    }

    void clear()
    {
        for(int i = 0; i < 26; ++i) {
            if(nxt[i] != nullptr) {
                nxt[i]->clear();
                delete nxt[i];
            }
        }
    }
};

int n, m;
Node* root;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    root = new Node();
    root->init(0);

    cin >> n >> m;
    for(int i = 0; i < n; ++i) {
        string str;
        cin >> str;
        curnum++;
        root->insert(str, 0);
    }
    root->num = 0;

    for(int i = 0; i < m; ++i) {
        string str;
        cin >> str;

        res = 0;
        root->process(str, 0);
        cout << res << "\n";
    }

    root->clear();
    delete root;

    return 0;
}
