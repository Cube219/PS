#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <vector>
using namespace std;

using lli = long long int;

int tNum;
int n;
char a[200001];
int p[200001];
bool isNot[2000001];
vector<int> nums;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 0; tt < tNum; tt++) {
        cin >> n >> a;

        for(int i = 0; i < n; i++) {
            p[i] = 0;
            isNot[i] = false;
        }

        if(a[0] == 'L') {
            p[n - 1]++;
            if(a[n - 1] == 'R') {
                isNot[0] = true;
                isNot[n - 1] = true;
            }
        } else {
            p[1]++;
        }
        for(int i = 1; i < n - 1; i++) {
            if(a[i] == 'L') {
                p[i - 1]++;
                if(a[i - 1] == 'R') {
                    isNot[i - 1] = true;
                    isNot[i] = true;
                }
            } else {
                p[i + 1]++;
            }
        }
        if(a[n - 1] == 'L') {
            p[n - 2]++;
            if(a[n - 2] == 'R') {
                isNot[n - 2] = true;
                isNot[n - 1] = true;
            }
        } else {
            p[0]++;
        }

        int res = 0;
        int i;
        int cnt = 0;
        nums.clear();
        for(i = 0; i < n; i++) {
            if(p[i] != 1 || isNot[i] == true) {
                if(cnt > 0) nums.push_back(cnt);
                cnt = 0;
            } else {
                cnt++;
            }
        }
        if(cnt > 0) {
            if(p[0] == 1) {
                if(nums.size() == 0) nums.push_back(0);
                nums[0] += cnt;
            } else {
                nums.push_back(cnt);
            }
        }
        for(int i = 0; i < nums.size(); i++) {
            res += (nums[i] - 1) / 3 + 1;
        }

        cout << res << endl;
    }

    return 0;
}
