#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

constexpr int MXBIT = 25;

struct Trie
{
    Trie* nxt[2];
    int num;
    Trie()
    {
        nxt[0] = nxt[1] = 0;
        num = 0;
    };
    ~Trie()
    {
        delete nxt[0];
        delete nxt[1];
    }

    void update()
    {
        num = 0;
        for(int i = 0; i < 2; ++i) {
            if(nxt[i]) {
                num += nxt[i]->num;
                if(nxt[i]->num == 0) {
                    delete nxt[i];
                    nxt[i] = nullptr;
                }
            }
        }
    }

    void insert(vector<int>& d, int idx)
    {
        if(idx < 0) {
            num = 1;
            return;
        }

        int v = d[idx];
        if(nxt[v] == nullptr) nxt[v] = new Trie();

        nxt[v]->insert(d, idx - 1);

        update();
    }

    int search(int v, int idx, bool isMax, bool isErase)
    {
        if(idx < 0) {
            if(isErase) num = 0;
            return 0;
        }

        int nx;
        if(nxt[0] == nullptr) nx = 1;
        else if(nxt[1] == nullptr) nx = 0;
        else {
            if(isMax) nx = 1;
            else nx = 0;

            if((1 << idx) & v) nx = 1 - nx;
        }

        int res = nxt[nx]->search(v, idx - 1, isMax, isErase);
        if(nx == 1) res |= (1 << idx);
        update();

        return res;
    }
};

void solve()
{
    int n, q;
    cin >> n >> q;

    Trie* rt = new Trie();
    vector<int> bit(MXBIT);
    auto updateBit = [&](int v) {
        for(int i = 0; i < MXBIT; ++i) {
            if((1 << i) & v) bit[i] = 1;
            else bit[i] = 0;
        }
    };

    for(int i = 0; i < n; ++i) {
        int v;
        cin >> v;
        updateBit(v);
        rt->insert(bit, MXBIT - 1);
    }

    for(int i = 0; i < q; ++i) {
        int t, v;
        cin >> t;
        switch(t) {
        case 1:
            cin >> v;
            cout << (rt->search(v, MXBIT - 1, false, false) ^ v) << "\n";
            break;
        case 2:
            cin >> v;
            cout << (rt->search(v, MXBIT - 1, true, false) ^ v) << "\n";
            break;
        case 3:
            cin >> v;
            updateBit(v);
            rt->insert(bit, MXBIT - 1);
            cout << rt->num << "\n";
            break;
        case 4:
            cout << rt->search(0, MXBIT - 1, false, true) << "\n";
            break;
        case 5:
            cout << rt->search(0, MXBIT - 1, true, true) << "\n";
            break;
        }
    }

    delete rt;
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tNum = 1;
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
