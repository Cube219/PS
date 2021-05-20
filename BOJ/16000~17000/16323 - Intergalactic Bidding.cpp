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

struct BigInt
{
    short d[1010];
    int sz;
    BigInt()
    {
        for(int i = 0; i < 1010; ++i) {
            d[i] = 0;
        }
        sz = 0;
    }
    void add(const BigInt& rhs)
    {
        sz = max(sz, rhs.sz);
        for(int i = 0; i < sz; ++i) {
            d[i] += rhs.d[i];
            if(d[i] > 9) {
                d[i + 1]++;
                d[i] -= 10;
                if(i + 2 > sz) sz = i + 2;
            }
        }
    }
    int comp(const BigInt& rhs) const
    {
        if(sz < rhs.sz) return -1;
        if(sz > rhs.sz) return 1;
        for(int i = sz - 1; i >= 0; --i) {
            if(d[i] < rhs.d[i]) return -1;
            if(d[i] > rhs.d[i]) return 1;
        }
        return 0;
    }
};

int n;
BigInt l;

struct Node
{
    string name;
    BigInt num;
};
vector<Node> d;
BigInt cur;
BigInt ncur;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string str;
    getline(cin, str);
    for(int i = 0; i < str.size(); ++i) {
        if(str[i] == ' ') break;
        n *= 10;
        n += str[i] - '0';
    }
    for(int i = str.size() - 1; i >= 0; --i) {
        if(str[i] == ' ') break;
        l.d[l.sz++] = str[i] - '0';
    }

    d.resize(n);
    for(int i = 0; i < n; ++i) {
        getline(cin, str);
        for(int j = 0; j < str.size(); ++j) {
            if(str[j] == ' ') break;
            d[i].name.push_back(str[j]);
        }
        for(int j = str.size() - 1; j >= 0; --j) {
            if(str[j] == ' ') break;
            d[i].num.d[d[i].num.sz++] = str[j] - '0';
        }
    }
    sort(d.begin(), d.end(), [](const Node& l, const Node& r) {
        int res = l.num.comp(r.num);
        if(res == -1) return false;
        return true;
    });

    vector<string> res;
    bool comp = false;
    for(int i = 0; i < n; ++i) {
        ncur = cur;
        ncur.add(d[i].num);

        int r = ncur.comp(l);
        if(r == 1) {
            continue;
        }
        cur = ncur;
        res.push_back(d[i].name);
        if(r == 0) {
            comp = true;
            break;
        }
    }
    if(comp == false) res.clear();
    cout << res.size() << "\n";
    for(int i = 0; i < res.size(); ++i) {
        cout << res[i] << "\n";
    }

    return 0;
}
