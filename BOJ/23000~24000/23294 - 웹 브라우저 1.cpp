#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <deque>
#include <vector>
using namespace std;

using ll = long long int;

int n, q, cache;
int c[2001];
int totalsize, cur, presize, sufsize;
vector<int> suf;
deque<int> pre;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> q >> cache;
    for(int i = 1; i <= n; ++i) {
        cin >> c[i];
    }
    for(int i = 0; i < q; ++i) {
        char ch;
        cin >> ch;
        if(ch == 'B') {
            if(pre.size() == 0) continue;
            suf.push_back(cur);
            sufsize += c[cur];

            cur = pre.back();
            pre.pop_back();
            presize -= c[cur];
        } else if(ch == 'F') {
            if(suf.size() == 0) continue;
            pre.push_back(cur);
            presize += c[cur];

            cur = suf.back();
            suf.pop_back();
            sufsize -= c[cur];
        } else if(ch == 'A') {
            totalsize -= sufsize;
            sufsize = 0;
            suf.clear();

            if(cur > 0) {
                presize += c[cur];
                pre.push_back(cur);
            }

            int v;
            cin >> v;
            cur = v;
            totalsize += c[v];
            while(totalsize > cache) {
                int prei = pre.front();
                totalsize -= c[prei];
                presize -= c[prei];
                pre.pop_front();
            }

        } else { // C
            deque<int> newpre;
            int newsize = 0;
            while(pre.size() > 0) {
                int v = pre.front();
                pre.pop_front();
                if(newpre.size() == 0 || newpre.back() != v) {
                    newpre.push_back(v);
                    newsize += c[v];
                }
            }
            pre = std::move(newpre);
            presize = newsize;
            totalsize = presize + sufsize + c[cur];
        }
    }
    cout << cur << "\n";
    if(pre.size() == 0) cout << "-1\n";
    else {
        while(pre.size() > 0) {
            cout << pre.back() << " ";
            pre.pop_back();
        }
        cout << "\n";
    }
    if(suf.size() == 0) cout << "-1\n";
    else {
        for(int i = suf.size() - 1; i >= 0; --i) {
            cout << suf[i] << " ";
        }
        cout << "\n";
    }

    return 0;
}
