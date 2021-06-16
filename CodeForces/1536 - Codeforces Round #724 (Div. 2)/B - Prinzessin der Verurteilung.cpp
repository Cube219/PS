#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

using ll = long long int;

constexpr ll b0 = 3137;
constexpr ll p0 = 1000003;
constexpr ll b1 = 53;
constexpr ll p1 = 1100023;

unordered_set<string> bk;

int tNum;
int n;
string str;
vector<int> idx[30];

string res;

string cs;
bool finish;
void bt(int num)
{
    if(num == 0) {
        if(bk.find(cs) == bk.end()) {
            res = cs;
            finish = true;
        }
        return;
    }

    for(int i = 0; i < 26; ++i) {
        cs.push_back(i + 'a');
        bt(num - 1);
        if(finish == true) return;
        cs.pop_back();
    }
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        bk.clear();
        cs.clear();
        finish = false;

        cin >> n >> str;

        for(int i = 1; i <= 5; ++i) {
            for(int j = 0; j < n - i + 1; ++j) {
                bk.insert(str.substr(j, i));
            }
        }

        for(int i = 1; i <= 5; ++i) {
            bt(i);
            if(finish == true) break;
        }
        cout << res << "\n";
    }

    return 0;
}
