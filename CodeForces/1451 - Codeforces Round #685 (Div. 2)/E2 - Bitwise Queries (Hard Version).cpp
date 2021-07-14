#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;

using ll = long long int;

int n;
int a[70001];
int axor[70001];

void print()
{
    cout << "! ";
    for(int i = 1; i <= n; ++i) {
        cout << a[i] << " ";
    }
    cout << endl;
}

bool check1()
{
    a[1] = -1;
    // a[1]이랑 같은게 있나
    for(int i = 2; i <= n; ++i) {
        if(axor[i] == 0) {
            cout << "AND 1 " << i << endl;
            cin >> a[1];
            break;
        }
    }
    if(a[1] == -1) return false;

    for(int i = 2; i <= n; ++i) {
        a[i] = axor[i] ^ a[1];
    }
    return true;
}

bool check2()
{
    a[1] = -1;
    // a[2]~a[n]중에 같은게 있나
    map<int, int> mp;
    for(int i = 2; i <= n; ++i) {
        auto it = mp.find(axor[i]);
        if(it != mp.end()) {
            int res;
            cout << "AND " << it->second << " " << i << endl;
            cin >> res;

            a[1] = axor[i] ^ res;
            break;
        }
        mp.insert({ axor[i], i });
    }

    if(a[1] == -1) return false;

    for(int i = 2; i <= n; ++i) {
        a[i] = axor[i] ^ a[1];
    }
    return true;
}

void check3()
{
    a[1] = -1;
    // 전부 다 다른 경우
    int mask = n - 1;
    for(int i = 3; i <= n; ++i) {
        if((axor[2] ^ axor[i]) == mask) {
            int r1, r2;
            cout << "AND 1 2" << endl;
            cin >> r1;
            cout << "AND 1 " << i << endl;
            cin >> r2;
            a[1] = r1 | r2;
            break;
        }
    }

    if(a[1] == -1) {
        for(int i = 4; i <= n; ++i) {
            if((axor[3] ^ axor[i]) == mask) {
                int r1, r2;
                cout << "AND 1 3" << endl;
                cin >> r1;
                cout << "AND 1 " << i << endl;
                cin >> r2;
                a[1] = r1 | r2;
                break;
            }
        }
    }

    for(int i = 2; i <= n; ++i) {
        a[i] = axor[i] ^ a[1];
    }
}

int main(void)
{
    cin >> n;
    for(int i = 2; i <= n; ++i) {
        cout << "XOR 1 " << i << endl;
        cin >> axor[i];
    }

    if(check1() == true) {
        print();
        return 0;
    }

    if(check2() == true) {
        print();
        return 0;
    }

    check3();
    print();

    return 0;
}
