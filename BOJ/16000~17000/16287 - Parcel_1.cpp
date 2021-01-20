#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

using lli = long long int;

int w, n;
int a[5001];
bool res;
struct Node
{
    int sum;
    int idx1;
    int idx2;
};
bool operator<(const Node& l, const Node& r)
{
    return l.sum < r.sum;
}
vector<Node> d;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> w >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(a[i] + a[j] >= w) continue;
            d.push_back({ a[i] + a[j], i, j });
        }
    }
    sort(d.begin(), d.end());

    for(int i = 0; i < d.size(); i++) {
        int remain = w - d[i].sum;

        auto it = lower_bound(d.begin(), d.end(), Node{ remain, 0, 0 });
        while(it != d.end()) {
            Node node = *it;
            if(node.sum != remain) break;

            if(d[i].idx1 != node.idx1 && d[i].idx1 != node.idx2
                && d[i].idx2 != node.idx1 && d[i].idx2 != node.idx2) {
                res = true;
                break;
            }
            it++;
        }

        if(res == true) break;
    }

    if(res == false) cout << "NO";
    else cout << "YES";

    return 0;
}
