#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
using namespace std;

using lli = long long int;

int tNum;
int n, k;
char s[300002];
int num0, num1, numq;
int numq0, numq1;

void ff()
{
    int remain0 = k / 2 - (num0);
    int remain1 = k / 2 - (num1);

    numq0 += remain0;
    numq1 += remain1;

    num0 = k / 2;
    num1 = k / 2;
    numq = 0;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
     for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> k >> s;

        num0 = 0;
        num1 = 0;
        numq = 0;
        numq0 = 0;
        numq1 = 0;

        for(int i = 0; i < k; i++) {
            if(s[i] == '0') num0++;
            else if(s[i] == '1') num1++;
            else numq++;
        }

        bool ck = true;

        if(num0 > k / 2 || num1 > k / 2) {
            cout << "NO\n";
            continue;
        }

        ff();

        for(int i = k; i < n; i++) {
            int st = i - k;
            int ed = i;
            if(s[st] == '0' && s[ed] == '0') continue;
            if(s[st] == '1' && s[ed] == '1') continue;
            if(s[st] == '0' && s[ed] == '1') {
                ck = false;
                break;
            }
            if(s[st] == '1' && s[ed] == '0') {
                ck = false;
                break;
            }
            if(s[st] == '1' && s[ed] == '?') {
                s[ed] = '1';
                continue;
            }
            if(s[st] == '0' && s[ed] == '?') {
                s[ed] = '0';
                continue;
            }
            if(s[ed] == '0'){
                if(numq0 == 0) {
                    ck = false;
                    break;
                } else {
                    numq0--;
                }
            } else if(s[ed] == '1') {
                if(numq1 == 0) {
                    ck = false;
                    break;
                } else {
                    numq1--;
                }
            }
        }

        if(ck == false) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
        }
    }

    return 0;
}
