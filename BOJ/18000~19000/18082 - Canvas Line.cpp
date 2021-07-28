#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

using ll = long long int;

struct Node
{
    int l, r;
    int cnt;
};

int n, p;
Node d[1002];
bool pos = true;
set<int> pin;
vector<int> res;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> d[i].l >> d[i].r;
    }
    cin >> p;
    for(int i = 0; i < p; ++i) {
        int x;
        cin >> x;
        for(int j = 0; j < n; ++j) {
            if(d[j].l <= x && x <= d[j].r) {
                d[j].cnt++;
            }
        }
        pin.insert(x);
    }

    for(int i = 0; i < n; ++i) {
        if(d[i].cnt > 2) {
            pos = false;
            break;
        }
    }
    if(pos == false) {
        cout << "impossible";
        return 0;
    }

    for(int i = 0; i < n - 1; ++i) {
        if(d[i].r == d[i + 1].l) {
            if(d[i].cnt < 2 && d[i + 1].cnt < 2) {
                if(pin.find(d[i].r) == pin.end()) {
                    pin.insert(d[i].r);
                    res.push_back(d[i].r);

                    d[i].cnt++;
                    d[i + 1].cnt++;
                }
            }
        }
    }
    for(int i = 0; i < n; ++i) {
        if(d[i].cnt >= 2) continue;

        int x = d[i].l + 1;
        for(int j = 0; j < 2 - d[i].cnt; ++j) {
            if(pin.find(x) != pin.end()) {
                j--;
                x++;
                continue;
            }
            res.push_back(x);
            pin.insert(x);
            x++;
        }
    }

    cout << res.size() << "\n";
    for(int i = 0; i < res.size(); ++i) {
        cout << res[i] << " ";
    }

    return 0;
}
