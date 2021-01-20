#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <queue>
#include <set>
using namespace std;

using lli = long long int;

int n, q;
int l, r, a[100001];
int gapLeft, gapRight, gapMax;
struct Gap
{
    int st;
    int ed;
};
bool operator<(const Gap& l, const Gap& r)
{
    return (l.ed - l.st) < (r.ed - r.st);
}
priority_queue<Gap> pq;
set<int> s;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    l = 987654321, r = -1;

    cin >> n >> q;
    for(int i = 0; i < n; i++) {
        cin >> a[i];

        s.insert(a[i]);

        if(l > a[i]) l = a[i];
        if(r < a[i]) r = a[i];
    }
    for(auto it = s.begin(); it != s.end(); it++) {
        auto it2 = it;
        it2++;
        if(it2 == s.end()) break;

        pq.push({ *it, *it2 });
    }

    if(n == 1) {
        cout << "0\n";
    } else {
        Gap g = pq.top();
        cout << (g.st - l) + (r - g.ed) << "\n";
    }
    
    for(int i = 0; i < q; i++) {
        int t1, t2;
        cin >> t1 >> t2;

        if(t1 == 0) {
            auto it = s.find(t2);
            auto tit = it;
            if(it == s.begin()) {
                it++;
                if(it == s.end()) {
                    l = 987654321;
                    r = -1;
                } else {
                    l = *it;
                }
            } else if(++tit == s.end()) {
                it--;
                r = *it;
            } else {
                auto bit = it;
                bit--;
                auto ait = it;
                ait++;

                pq.push({*bit, *ait});
            }
            s.erase(t2);
        } else {
            if(s.size() != 0) {
                auto it2 = s.lower_bound(t2);
                if(it2 == s.begin()) {
                    pq.push({ t2, *it2 });
                } else if(it2 == s.end()) {
                    it2--;
                    pq.push({ *it2, t2 });
                } else {
                    auto it = it2;
                    it--;
                    pq.push({ *it, t2 });
                    pq.push({ t2, *it2 });
                }
            }

            s.insert(t2);

            if(l > t2) l = t2;
            if(r < t2) r = t2;
        }

        Gap g;
        while(pq.empty() == false) {
            g = pq.top();
            auto it = s.find(g.st);
            
            if(it == s.end()) {
                pq.pop();
                continue;
            }
            auto it2 = it;
            it2++;
            if(it2 == s.end() || g.ed != *it2) {
                pq.pop();
                continue;
            } else {
                break;
            }
        }

        if(s.size() <= 2 || pq.empty() == true) {
            cout << "0\n";
        } else {
            cout << (g.st - l) + (r - g.ed) << "\n";
        }
    }

    return 0;
}
