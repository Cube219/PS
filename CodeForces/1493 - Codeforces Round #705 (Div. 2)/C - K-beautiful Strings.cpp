#define _CRT_SECURE_NO_WARNINGS 1
 
#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;
 
using ll = long long int;
 
int tNum;
int n, k;
int num[30];
char str[100009], str2[100009];
bool pos;
int reqNum[30];
 
constexpr int sz = 'z' - 'a' + 1;
 
bool ck(int remain, int idx)
{
    for(int i = 0; i < sz; ++i) {
        reqNum[i] = 0;
    }
 
    for(int i = 0; i < sz; ++i) {
        if(num[i] != 0 && num[i] % k != 0) {
            int req = num[i] % k;
            req = k - req;
            // if(req == k) req = 0;
 
            if(req > 0) {
                remain -= req;
                if(remain < 0) return false;
 
                reqNum[i] = req;
 
                /*
                for(int j = 0; j < req; ++j) {
                    str2[idx++] = (char)('a' + i);
                    if(idx > n) return false;
                }*/
            }
        }
    }
 
    if(remain > 0) {
        if(remain % k != 0) return false;
        reqNum[0] += remain;
    }
    for(int i = 0; i < sz; ++i) {
        while(reqNum[i] > 0) {
            str2[idx++] = (char)('a' + i);
            reqNum[i]--;
        }
    }
 
    return true;
}
 
int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        pos = false;
        for(int i = 0; i < sz; ++i) {
            num[i] = 0;
        }
 
        cin >> n >> k;
        cin >> str;
 
        for(int i = 0; i < n; ++i) {
            num[str[i] - 'a']++;
            str2[i] = str[i];
        }
 
        if(ck(0, 0) == true) {
            pos = true;
        }
 
        if(pos == false) {
            for(int i = n - 1; i >= 0; --i) {
                int ch = str[i] - 'a';
                num[ch]--;
 
                for(int j = ch + 1; j < sz; ++j) {
                    num[j]++;
                    str2[i] = (char)('a' + j);
 
                    if(ck(n - 1 - i, i + 1) == true) {
                        pos = true;
                        break;
                    }
                    num[j]--;
                }
                if(pos == true) break;
            }
        }
 
        str2[n] = '\0';
 
        if(pos == false) cout << "-1\n";
        else cout << str2 << "\n";
    }
 
    return 0;
}
