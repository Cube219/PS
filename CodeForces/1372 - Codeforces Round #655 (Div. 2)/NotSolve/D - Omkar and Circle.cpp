#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <queue>
#include <utility>
#include <functional>
using namespace std;

using lli = long long int;

int n;

priority_queue<pair<lli, int>, vector<pair<lli, int>>, greater<pair<lli, int>>> pq;

struct Node
{
    lli value;
    int prev;
    int next;
    bool isAv;
};
Node d[200001];

int main(void)
{
    // freopen("input.txt", "r", stdin);

    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        int a;
        scanf("%d", &a);
        d[i].value = a;
        d[i].isAv = true;

        pq.push({a, i});
    }
    for(int i = 0; i < n-1; i++) {
        d[i].next = i + 1;
    }
    d[n - 1].next = 0;
    for(int i = 1; i < n; i++) {
        d[i].prev = i - 1;
    }
    d[0].prev = n - 1;

    while(n > 1) {
        auto m = pq.top();
        pq.pop();

        Node current = d[m.second];
        int currentIdx = m.second;
        if(current.isAv == false) continue;

        int prev = current.prev;
        int next = current.next;

        current.value = d[prev].value + d[next].value;
        current.prev = d[prev].prev;
        current.next = d[next].next;
        d[current.prev].next = currentIdx;
        d[current.next].prev = currentIdx;
        d[prev].isAv = false;
        d[next].isAv = false;

        pq.push({ current.value, currentIdx });

        d[currentIdx] = current;

        n -= 2;
    }

    int resIndex;
    while(pq.size() > 0) {
        auto m = pq.top();
        pq.pop();

        Node node = d[m.second];
        if(node.isAv == true) {
            resIndex = m.second;
            break;
        }
    }
    printf("%lld", d[resIndex].value);

    return 0;
}
