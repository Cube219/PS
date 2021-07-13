#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll INF = 2000000000000000000;

struct Node
{
    ll len;
    int idx;
};

int n, q;
ll d[200001];
ll res[200001];
vector<Node> line;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> q;
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
    }
    line.push_back({ INF, -1 });
    for(int i = 0; i < n - 1; ++i) {
        line.push_back({ d[i + 1] - d[i], i });
    }
    line.push_back({ INF, n - 1 });
    sort(line.begin(), line.end(), [](const Node& l, const Node& r) {
        return l.len < r.len;
    });

    ll curl = 0, curr = 0;
    ll sum = 0;
    int lineidx = 0;
    for(int i = 0; i < q; ++i) {
        ll wind;
        cin >> wind;
        sum += wind;

        if(sum < 0) {
            curr = max(curr, -sum);
        } else if(sum > 0) {
            curl = max(curl, sum);
        }
        while(curl + curr >= line[lineidx].len) {
            auto& curline = line[lineidx];
            if(sum > 0) {
                // r¿ª ¥ı ∏‘¿Ω
                res[curline.idx + 1] += curr;
                res[curline.idx] += curline.len - curr;
            } else {
                // l¿ª ¥ı ∏‘¿Ω
                res[curline.idx] += curl;
                res[curline.idx + 1] += curline.len - curl;
            }
            lineidx++;
        }
    }
    while(line[lineidx].len != INF) {
        auto& curline = line[lineidx];
        res[curline.idx] += curl;
        res[curline.idx + 1] += curr;
        lineidx++;
    }

    res[0] += curr;
    res[n - 1] += curl;

    for(int i = 0; i < n; ++i) {
        cout << res[i] << "\n";
    }

    return 0;
}
