#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

using ll = long long int;

int n, m;
vector<int> a, b;
vector<int> aa;

vector<int> fail;
vector<int> smaller, bigger, hassame;

bool isSame(int posa, int posb, const vector<int>& b)
{
    if(hassame[posa] == 1) {
        if(b[posb - posa + smaller[posa]] != b[posb]) return false;
        return true;
    } else {
        if(smaller[posa] != -1 && b[posb - posa + smaller[posa]] >= b[posb]) return false;
        if(bigger[posa] != -1 && b[posb - posa + bigger[posa]] <= b[posb]) return false;
        return true;
    }
}

void init_fail()
{
    fail.clear();
    fail.resize(n, 0);

    int asz = aa.size();
    vector<int> nxt(asz), pre(asz), pos(asz, n), cnt(asz);
    for(int i = 0; i < asz; ++i) {
        nxt[i] = i + 1;
        pre[i] = i - 1;
    }
    for(int i = 0; i < n; ++i) {
        cnt[a[i]]++;
        pos[a[i]] = min(pos[a[i]], i);
    }
    bigger.resize(n); smaller.resize(n); hassame.resize(n, 0);
    for(int i = n - 1; i >= 0; --i) {
        int v = a[i];
        if(cnt[v] == 1) {
            if(nxt[v] == asz) bigger[i] = -1;
            else bigger[i] = pos[nxt[v]];
            if(pre[v] == -1) smaller[i] = -1;
            else smaller[i] = pos[pre[v]];
        } else {
            hassame[i] = 1;
            smaller[i] = pos[v];
        }

        cnt[v]--;
        if(cnt[v] == 0) {
            if(pre[v] != -1) nxt[pre[v]] = nxt[v];
            if(nxt[v] != asz) pre[nxt[v]] = pre[v];
        }
    }

    int j = 0;
    for(int i = 1; i < n; ++i) {
        while(j > 0 && isSame(j, i, a) == false) {
            j = fail[j - 1];
        }
        if(isSame(j, i, a) == true) {
            fail[i] = j + 1;
            j++;
        }
    }
}

void get(vector<int>& res)
{
    init_fail();
    res.clear();

    int j = 0;
    for(int i = 0; i < m; ++i) {
        while(j > 0 && isSame(j, i, b) == false) {
            j = fail[j - 1];
        }
        if(isSame(j, i, b) == true) {
            j++;
        }
        if(j == n) {
            res.push_back(i - n + 1);
            j = fail[j - 1];
        }
    }
}

int geta(int v)
{
    return lower_bound(aa.begin(), aa.end(), v) - aa.begin();
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    a.resize(n); b.resize(m);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
        aa.push_back(a[i]);
    }
    for(int i = 0; i < m; ++i) {
        cin >> b[i];
    }
    sort(aa.begin(), aa.end());
    aa.erase(unique(aa.begin(), aa.end()), aa.end());
    for(int i = 0; i < n; ++i) {
        a[i] = geta(a[i]);
    }

    vector<int> res;
    get(res);

    if(res.size() == 0) cout << "0";
    else {
        for(int v : res) cout << v + 1 << " ";
    }

    return 0;
}
