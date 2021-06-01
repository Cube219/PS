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

string str;

void printtab(int num)
{
    for(int i = 0; i < num; ++i) {
        cout << "  ";
    }
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> str;

    int num = 0;
    string buf;
    for(int i = 0; i < str.size(); ++i) {
        switch(str[i]) {
            case '{':
                printtab(num);
                cout << "{\n";
                num++;
                if(i + 1 < str.size() && str[i + 1] == '}') {
                    num--;
                    printtab(num);
                    cout << "}";
                    i++;
                }
                break;
            case '}':
                if(buf.size() > 0) {
                    printtab(num);
                    cout << buf;
                    buf.clear();
                }
                cout << "\n";
                num--;
                printtab(num);
                cout << "}";
                break;
            case ',':
                if(buf.size() > 0) {
                    printtab(num);
                    cout << buf;
                    buf.clear();
                }
                cout << ",\n";
                break;
            default:
                buf.push_back(str[i]);
                break;

        }
    }

    return 0;
}
