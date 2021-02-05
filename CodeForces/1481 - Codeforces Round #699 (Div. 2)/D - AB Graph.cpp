#define _CRT_SECURE_NO_WARNINGS 1
 
#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;
 
using ll = long long int;
 
int tNum;
int n, m;
char g[1005][1005];
bool hasLoop;
int l1, l2;
 
int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        hasLoop = false;
 
        cin >> n >> m;
        for(int i = 0; i < n; ++i) {
            cin >> g[i];
        }
 
        for(int i = 0; i < n - 1; ++i) {
            for(int j = i + 1; j < n; ++j) {
                if(g[i][j] == g[j][i]) {
                    hasLoop = true;
                    l1 = i + 1;
                    l2 = j + 1;
                    break;
                }
            }
            if(hasLoop == true) break;
        }
 
        if(m % 2 == 1) {
            hasLoop = true;
            l1 = 1;
            l2 = 2;
        }
 
        if(hasLoop == true) {
            cout << "YES\n";
            for(int i = 0; i <= m; ++i) {
                if(i % 2 == 0) cout << l1 << " ";
                else cout << l2 << " ";
            }
            cout << "\n";
            continue;
        }
 
        bool pos = false;
        int a, b, c;
        for(int i = 0; i < n; ++i) {
            int ina = -1, inb = -1, outa = -1, outb = -1;
 
            for(int j = 0; j < n; ++j) {
                if(g[i][j] == 'a' && outa == -1) {
                    outa = j;
                } else if(g[i][j] == 'b' && outb == -1) {
                    outb = j;
                }
 
                if(g[j][i] == 'a' && ina == -1) {
                    ina = j;
                } else if(g[j][i] == 'b' && inb == -1) {
                    inb = j;
                }
            }
 
            if(ina != -1 && outa != -1) {
                pos = true;
                a = ina + 1;
                b = i + 1;
                c = outa + 1;
                break;
            } else if(inb != -1 && outb != -1) {
                pos = true;
                a = inb + 1;
                b = i + 1;
                c = outb + 1;
                break;
            }
        }
 
        if(pos == false) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
            if((m / 2) % 2 == 0) {
                cout << b << " ";
                for(int i = 0; i < m / 2; ++i) {
                    if(i % 2 == 0) cout << c << " ";
                    else cout << b << " ";
                }
                for(int i = 0; i < m / 2; ++i) {
                    if(i % 2 == 0) cout << a << " ";
                    else cout << b << " ";
                }
            } else {
                cout << a << " ";
                for(int i = 0; i < m / 2; ++i) {
                    if(i % 2 == 0) cout << b << " ";
                    else cout << a << " ";
                }
                for(int i = 0; i < m / 2; ++i) {
                    if(i % 2 == 0) cout << c << " ";
                    else cout << b << " ";
                }
            }
            cout << "\n";
        }
    }
 
    return 0;
}
