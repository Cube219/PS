#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
using namespace std;

using ll = long long int;

struct AhoCorasick
{
    AhoCorasick* nxt[26];
    AhoCorasick* fail;
    bool has;

    AhoCorasick()
    {
        for(int i = 0; i < 26; ++i) {
            nxt[i] = nullptr;
        }
        fail = nullptr;
        has = false;
    }
    ~AhoCorasick()
    {
        for(int i = 0; i < 26; ++i) {
            if(nxt[i] != nullptr) delete nxt[i];
        }
    }
    void insert(const string& str, int idx)
    {
        if(str.size() == idx) {
            has = true;
            return;
        }
        int ch = str[idx] - 'a';
        if(nxt[ch] == nullptr) nxt[ch] = new AhoCorasick();
        nxt[ch]->insert(str, idx + 1);
    }
    void build()
    {
        fail = this;
        queue<AhoCorasick*> q;
        q.push(this);
        while(q.empty() == false) {
            AhoCorasick* cur = q.front();
            q.pop();
            for(int i = 0; i < 26; ++i) {
                if(cur->nxt[i] == nullptr) continue;
                AhoCorasick* nxt = cur->nxt[i];
                if(cur == this) nxt->fail = this;
                else {
                    AhoCorasick* k = cur->fail;
                    while(k != this && k->nxt[i] == nullptr) k = k->fail;
                    if(k->nxt[i] != nullptr) k = k->nxt[i];
                    nxt->fail = k;
                }
                q.push(nxt);
                if(nxt->fail->has == true) nxt->has = true;
            }
        }
    }
    bool process(const string& str)
    {
        AhoCorasick* cur = this;
        for(int i = 0; i < str.size(); ++i) {
            int ch = str[i] - 'a';
            while(cur != this && cur->nxt[ch] == nullptr) cur = cur->fail;
            if(cur->nxt[ch] != nullptr) cur = cur->nxt[ch];

            if(cur->has == true) return true;
        }
        return false;
    }
};

AhoCorasick* ac;
int n, q;
string str;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ac = new AhoCorasick();

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> str;
        ac->insert(str, 0);
    }
    ac->build();

    cin >> q;
    for(int i = 0; i < q; ++i) {
        cin >> str;
        bool r = ac->process(str);
        if(r == true) cout << "YES\n";
        else cout << "NO\n";
    }
    delete ac;

    return 0;
}
