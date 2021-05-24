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

struct Node
{
    string name;
    int price;
    int rate;
    int ctime;
    int rtime;
    double area;
    int idx;
};

int m;
ll l;
Node d[101];

Node parse(const string& str)
{
    Node res;
    string strs[5];
    int stridx = 0;
    for(int i = 0; i < str.size(); ++i) {
        if(str[i] == ',') {
            stridx++;
            continue;
        }
        strs[stridx].push_back(str[i]);
    }

    res.name = strs[0];
    res.price = stoi(strs[1]);
    res.rate = stoi(strs[2]);
    res.ctime = stoi(strs[3]);
    res.rtime = stoi(strs[4]);
    res.area = 0;
    return res;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> l >> m;
    string str;
    getline(cin, str);
    for(int i = 0; i < m; ++i) {
        getline(cin, str);
        d[i] = parse(str);
        d[i].idx = i;
    }

    sort(d, d + m, [](const Node& l, const Node& r) {
        return l.price < r.price;
    });

    for(int i = 0; i < m; ++i) {
        d[i].area = (double)d[i].rate * (double)d[i].ctime / (double)(d[i].ctime + d[i].rtime);
        d[i].area *= 10080.0;
    }

    vector<pair<string, int>> res;
    int curprice = 987654321;
    for(int i = 0; i < m; ++i) {
        if(d[i].price > curprice) break;
        if(d[i].area >= (double)l) {
            res.push_back({ d[i].name, d[i].idx });
            curprice = d[i].price;
        }
    }

    if(res.size() == 0) cout << "no such mower";
    else {
        sort(res.begin(), res.end(), [](const auto& l, const auto& r) {
            return l.second < r.second;
        });
        for(int i = 0; i < res.size(); ++i) {
            cout << res[i].first << "\n";
        }
    }

    return 0;
}
