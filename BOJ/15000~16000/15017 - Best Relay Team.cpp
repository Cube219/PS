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
    float t0, t1;
};

int n;
vector<Node> d;
float res = 99999999;
string r2[4];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    d.resize(n);
    for(int i = 0; i < n; ++i) {
        cin >> d[i].name >> d[i].t0 >> d[i].t1;
    }

    for(int i = 0; i < n; ++i) {
        vector<Node> tmp;
        for(int j = 0; j < n; ++j) {
            if(i == j) continue;
            tmp.push_back(d[j]);
        }
        sort(tmp.begin(), tmp.end(), [](const Node& l, const Node& r) {
            return l.t1 < r.t1;
        });
        float sum = d[i].t0 + tmp[0].t1 + tmp[1].t1 + tmp[2].t1;
        if(sum < res) {
            res = sum;
            r2[0] = d[i].name;
            r2[1] = tmp[0].name;
            r2[2] = tmp[1].name;
            r2[3] = tmp[2].name;
        }
    }

    cout << res << "\n";
    for(int i = 0; i < 4; ++i) {
        cout << r2[i] << "\n";
    }

    return 0;
}
