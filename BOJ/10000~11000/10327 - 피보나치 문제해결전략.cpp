#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;
#define k(a) memset(a, 0, sizeof(a))
using namespace std;
const int INF = 2e9;
const int SIZE = 1e5 + 1;

int n, m;
int arr[SIZE], tree[SIZE * 4];
int sum[SIZE];

int init(int left, int right, int node)
{
    if(left == right) return tree[node] = sum[left];

    int mid = (left + right) / 2;
    return tree[node] = min(init(left, mid, node * 2), init(mid + 1, right, node * 2 + 1));
}

int getmin(int left, int right, int x, int y, int node)
{
    if(right < x || y < left) return INF;
    if(x <= left && right <= y) return tree[node];

    int mid = (left + right) / 2;
    return min(getmin(left, mid, x, y, node * 2), getmin(mid + 1, right, x, y, node * 2 + 1));
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    //freopen("input.txt", "r", stdin);

    k(arr), k(tree), k(sum);

    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        cin >> arr[i];
        sum[i] = sum[i - 1] + arr[i];
    }
    init(0, n, 1);

    int answer = 0;
    for(int i = m; i <= n; i++)
        answer = max(answer, sum[i] - getmin(0, n, 0, i - m, 1));

    cout << answer;

    return 0;
}
