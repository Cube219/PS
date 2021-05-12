#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <queue>
#include <string>
#include <vector>
using namespace std;

using ll = long long int;

struct AhoCorasick
{
    AhoCorasick* nxt[128];
    AhoCorasick* fail;
    bool has;

    AhoCorasick()
    {
        for(int i = 0; i < 128; ++i) {
            nxt[i] = nullptr;
        }
        fail = nullptr;
        has = false;
    }

    ~AhoCorasick()
    {
        for(int i = 0; i < 128; ++i) {
            if(nxt[i] != nullptr) delete nxt[i];
        }
    }

    void insert(const string& str, int idx)
    {
        if(str.size() == idx) {
            has = true;
            return;
        }
        int ch = str[idx];
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
            for(int i = 0; i < 128; ++i) {
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

    int process(string& str)
    {
        int ret = 0;

        AhoCorasick* cur = this;
        for(int i = 0; i < str.size(); ++i) {
            int ch = str[i];
            while(cur != this && cur->nxt[ch] == nullptr) cur = cur->fail;
            if(cur->nxt[ch] != nullptr) cur = cur->nxt[ch];

            if(cur->has == true) {
                ret++;
                cur = this;
            }
        }
        
        return ret;
    }
};

int n, m;
vector<string> emo;
AhoCorasick* ac;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while(1) {
        cin >> n >> m;
        if(n == 0) break;

        ac = new AhoCorasick();

        for(int i = 0; i < n; ++i) {
            string e;
            cin >> e;
            ac->insert(e, 0);
        }
        ac->build();

        string tmp;
        getline(cin, tmp);
        int res = 0;
        for(int i = 0; i < m; ++i) {
            string str;
            getline(cin, str);
            res += ac->process(str);
        }

        cout << res << "\n";

        delete ac;
    }

    return 0;
}
