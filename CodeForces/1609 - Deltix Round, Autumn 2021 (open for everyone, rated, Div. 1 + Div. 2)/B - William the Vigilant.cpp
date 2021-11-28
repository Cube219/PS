#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;


int cvt(char ch)
{
    if(ch == 'a') return 1;
    else if(ch == 'b') return 2;
    else return 3;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    string str;
    cin >> n >> q >> str;
    vector<int> sum(n, 0);
    for(int i = 0; i < n - 2; ++i) {
        sum[i] += cvt(str[i]) * 100;
        sum[i] += cvt(str[i + 1]) * 10;
        sum[i] += cvt(str[i + 2]) * 1;
    }
    int cnt = 0;
    for(int i = 0; i < n; ++i) {
        if(sum[i] == 123) cnt++;
    }

    for(int i = 0; i < q; ++i) {
        int pos;
        char ch;
        cin >> pos >> ch;
        pos--;
        int gap = cvt(ch) - cvt(str[pos]);
        if(gap != 0) {
            if(pos - 2 >= 0) {
                if(sum[pos - 2] == 123) cnt--;
                sum[pos - 2] += gap * 1;
                if(sum[pos - 2] == 123) cnt++;
            }
            if(pos - 1 >= 0) {
                if(sum[pos - 1] == 123) cnt--;
                sum[pos - 1] += gap * 10;
                if(sum[pos - 1] == 123) cnt++;
            }
            if(sum[pos] == 123) cnt--;
            sum[pos] += gap * 100;
            if(sum[pos] == 123) cnt++;
        }
        cout << cnt << "\n";
        str[pos] = ch;
    }

    return 0;
}
