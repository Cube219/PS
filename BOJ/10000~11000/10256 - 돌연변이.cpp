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

int convert(char ch)
{
    if(ch == 'A') return 0;
    else if(ch == 'C') return 1;
    else if(ch == 'G') return 2;
    else return 3;
}

struct Aho
{
    Aho* nxt[4];
    Aho* fail;
    bool has;
    Aho()
    {
        for(int i = 0; i < 4; ++i) {
            nxt[i] = nullptr;
        }
        fail = nullptr;
        has = false;
    }
    ~Aho()
    {
        for(int i = 0; i < 4; ++i) {
            if(nxt[i] != nullptr) delete nxt[i];
        }
    }
    void insert(const string& str, int idx)
    {
        if(idx == str.size()) {
            has = true;
            return;
        }
        int ch = convert(str[idx]);
        if(nxt[ch] == nullptr) nxt[ch] = new Aho();
        nxt[ch]->insert(str, idx + 1);
    }
    void build()
    {
        queue<Aho*> q;
        q.push(this);
        fail = this;
        while(q.empty() == false) {
            Aho* cur = q.front();
            q.pop();
            for(int i = 0; i < 4; ++i) {
                Aho* nx = cur->nxt[i];
                if(nx == nullptr) continue;

                if(cur == this) {
                    nx->fail = this;
                } else {
                    Aho* k = cur->fail;
                    while(k != this && k->nxt[i] == nullptr) k = k->fail;
                    if(k->nxt[i] != nullptr) k = k->nxt[i];
                    nx->fail = k;
                }
                if(nx->fail->has == true) nx->has = true;
                q.push(nx);
            }
        }
    }
    int process(const string& str)
    {
        int ret = 0;
        Aho* cur = this;
        for(int i = 0; i < str.size(); ++i) {
            int ch = convert(str[i]);
            while(cur != this && cur->nxt[ch] == nullptr) cur = cur->fail;
            if(cur->nxt[ch] != nullptr) {
                cur = cur->nxt[ch];
            }
            if(cur->has == true) ret++;
        }

        return ret;
    }
};

int tNum;
int n, m;
string mk, str;
Aho* ac;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> m;
        cin >> str >> mk;

        ac = new Aho();
        ac->insert(mk, 0);
        for(int i = 0; i < m - 1; ++i) {
            string mk2 = mk;
            // È¦¼ö
            int l, r;
            if(i > 0) {
                l = i - 1;
                r = i + 1;
                while(l >= 0 && r < m) {
                    swap(mk2[l], mk2[r]);
                    ac->insert(mk2, 0);
                    l--; r++;
                }
            }
            // Â¦¼ö
            mk2 = mk;
            l = i;
            r = i + 1;
            while(l >= 0 && r < m) {
                swap(mk2[l], mk2[r]);
                ac->insert(mk2, 0);
                l--; r++;
            }
        }
        ac->build();

        int res = ac->process(str);
        cout << res << "\n";

        delete ac;
    }

    return 0;
}
