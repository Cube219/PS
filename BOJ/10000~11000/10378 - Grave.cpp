#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

struct Box
{
    int x1, y1, x2, y2;
};
Box yard, chapel, grave;
int width, height;
bool res = true;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> yard.x1 >> yard.y1 >> yard.x2 >> yard.y2;
    cin >> chapel.x1 >> chapel.y1 >> chapel.x2 >> chapel.y2;
    cin >> width >> height;

    if(yard.x2 - yard.x1 < width || yard.y2 - yard.y1 < height) res = false;
    else {
        res = false;
        // bot
        if(chapel.y1 - yard.y1 >= height) {
            res = true;
        }
        // top
        if(yard.y2 - chapel.y2 >= height) {
            res = true;
        }
        // left
        if(chapel.x1 - yard.x1 >= width) {
            res = true;
        }
        // right
        if(yard.x2 - chapel.x2 >= width) {
            res = true;
        }
    }
    if(res == true) cout << "Yes";
    else cout << "No";
    return 0;
}
