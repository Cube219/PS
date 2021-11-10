#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

struct Node
{
    Node()
    {
        nxt[0] = nxt[1] = nullptr;
        cnt = has = 0;
    }
    ~Node()
    {
        if(nxt[0] != nullptr) delete nxt[0];
        if(nxt[1] != nullptr) delete nxt[1];
    }

    Node* nxt[2];
    int cnt;
    int has;

    void insert(vector<int>& d, int idx)
    {
        cnt++;
        if(idx == d.size()) {
            has++;
            return;
        }

        int nx = d[idx];
        if(nxt[nx] == nullptr) {
            nxt[nx] = new Node();
        }

        nxt[nx]->insert(d, idx + 1);
    }

    void erase(vector<int>& d, int idx)
    {
        if(idx == d.size()) {
            has--;
            return;
        }
        int nx = d[idx];
        nxt[nx]->erase(d, idx + 1);

        nxt[nx]->cnt--;
        if(nxt[nx]->cnt == 0) {
            delete nxt[nx];
            nxt[nx] = nullptr;
        }
    }

    void find(vector<int>& d, int idx, vector<int>& res)
    {
        if(idx == d.size()) {
            return;
        }

        int nx = d[idx];
        if(nxt[1 - nx] == nullptr) {
            res.push_back(nx);
            nxt[nx]->find(d, idx + 1, res);
        } else {
            res.push_back(1 - nx);
            nxt[1 - nx]->find(d, idx + 1, res);
        }
    }
};

int m;
Node* rt;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    rt = new Node();

    {
        vector<int> tmp(32, 0);
        rt->insert(tmp, 0);
    }

    cin >> m;
    for(int i = 0; i < m; ++i) {
        int a, b, bb;
        cin >> a >> b;
        bb = b;
        vector<int> d(32, 0);
        for(int j = 32 - 1; j >= 0; --j) {
            if(b == 0) break;
            d[j] = b & 1;
            b >>= 1;
        }

        if(a == 1) rt->insert(d, 0);
        else if(a == 2) rt->erase(d, 0);
        else {
            vector<int> res;
            rt->find(d, 0, res);
            int v = 0;
            for(int j = 0; j < 32; ++j) {
                v <<= 1;
                v += res[j];
            }

            cout << (bb ^ v) << "\n";
        }
    }

    delete rt;

    return 0;
}
