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

struct ZFunc
{
    vector<int> z;
    void build(const string& s)
    {
        int n = (int)s.size();
        z.clear();
        z.resize(s.size());
        for(int i = 1, l = 0, r = 0; i < n; ++i) {
            if(i <= r) z[i] = min(r - i + 1, z[i - l]);
            while(i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
            if(i + z[i] - 1 > r) {
                l = i;
                r = i + z[i] - 1;
            }
        }
    }
};

ZFunc zf;
string str;
int cnt[100005];
bool pos[100005];
int n;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> str;
    n = str.size();
    zf.build(str);
    zf.z[0] = n;

    for(int i = 0; i < n; ++i) {
        cnt[zf.z[i]]++;
        if(zf.z[i] == n - i) pos[n - i] = true;
    }
    vector<pair<int, int>> res;
    int sum = 0;
    for(int i = n; i >= 1; --i) {
        if(pos[i] == true) {
            res.push_back({ i, cnt[i] + sum });
        }

        sum += cnt[i];
    }

    cout << res.size() << "\n";
    for(int i = res.size() - 1; i >= 0; --i) {
        cout << res[i].first << " " << res[i].second << "\n";
    }

    return 0;
}
