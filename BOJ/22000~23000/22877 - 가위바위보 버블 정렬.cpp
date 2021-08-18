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
    char ch;
    int num;
};

int n, t;
vector<Node> d;
string str;
char ck[][2] = { { 'R', 'S' }, { 'S', 'P' }, { 'P', 'R' } };

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> t >> str;
    d.push_back({ str[0], 1 });
    for(int i = 1; i < n; ++i) {
        if(d.back().ch != str[i]) {
            d.push_back({ str[i], 0 });
        }
        d.back().num++;
    }
    for(int i = 0; i < d.size(); ++i) {
        Node& cur = d[i];
        if(i == d.size() - 1) {
            for(int j = 0; j < cur.num; ++j) {
                cout << cur.ch;
            }
            break;
        }
        Node& nxt = d[i + 1];
        bool f = false;
        for(int j = 0; j < 3; ++j) {
            if(cur.ch == ck[j][0] && nxt.ch == ck[j][1]) {
                int lnum = max(0, cur.num - t);
                for(int z = 0; z < lnum; ++z) {
                    cout << cur.ch;
                }
                if(i + 2 >= d.size() || cur.ch != d[i + 2].ch) {
                    for(int z = 0; z < nxt.num; ++z) {
                        cout << nxt.ch;
                    }
                    for(int z = 0; z < cur.num - lnum; ++z) {
                        cout << cur.ch;
                    }
                    i++;
                } else {
                    d[i + 2].num += cur.num - lnum;
                }
                f = true;
                break;
            }
        }
        if(f == false) {
            for(int j = 0; j < cur.num; ++j) {
                cout << cur.ch;
            }
        }
    }

    return 0;
}
