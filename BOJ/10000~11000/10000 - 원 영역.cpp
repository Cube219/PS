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
    int x;
    int r;
    bool isend;
    int idx;
};

int n;
Node d[600001];
vector<int> st;
int last[300001];
bool istwo[300001];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        d[i * 2] = { a - b, b, false, i };
        d[i * 2 + 1] = { a + b, b, true, i };
        istwo[i] = true;
    }
    sort(d, d + n * 2, [](const Node& l, const Node& r) {
        if(l.x == r.x) {
            if(l.isend != r.isend) {
                if(l.isend == true) return true;
                else return false;
            }
            if(l.isend == true) {
                return l.r < r.r;
            } else {
                return l.r > r.r;
            }
        }
        return l.x < r.x;
    });

    for(int i = 0; i < n * 2; ++i) {
        if(d[i].isend == false) {
            if(st.size() > 0) {
                if(last[st.back()] != d[i].x) {
                    istwo[st.back()] = false;
                }
            }
            st.push_back(d[i].idx);
        } else {
            if(last[st.back()] != d[i].x) {
                istwo[st.back()] = false;
            }
            st.pop_back();
        }
        if(st.size() > 0) {
            last[st.back()] = d[i].x;
        }
    }

    int res = 1;
    for(int i = 0; i < n; ++i) {
        if(istwo[i] == true) {
            res += 2;
        } else {
            res += 1;
        }
    }
    cout << res;

    return 0;
}
