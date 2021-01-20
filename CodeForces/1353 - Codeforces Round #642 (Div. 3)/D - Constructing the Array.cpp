#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <queue>
#include <utility>
using namespace std;

int tNum;
int n;

int currentI;
int a[200001];

struct Node
{
    int length;
    int left;
    int right;
};

int main(void)
{
    auto cmp = [](Node l, Node r) {
        if(l.length < r.length) return true;
        else if(l.length == r.length && l.left > r.left) return true;
        else return false;
    };
    priority_queue<Node, vector<Node>, decltype(cmp)> q(cmp);
    scanf("%d", &tNum);

    for(int tt = 0; tt < tNum; tt++) {
        scanf("%d", &n);

        currentI = 1;
        q.push({ n, 1, n });
        while(q.empty() == false) {
            Node n = q.top();
            q.pop();

            if(n.length <= 0 || n.left > n.right) continue;

            int m = (n.left + n.right) / 2;
            a[m] = currentI++;

            int newLeft = n.left;
            int newRight = m - 1;
            int newLength = m - n.left;
            if(newLength > 0 && n.left <= n.right)
                q.push({ newLength, newLeft, newRight });

            newLeft = m + 1;
            newRight = n.right;
            newLength = n.right - m;
            if(newLength > 0 && n.left <= n.right)
                q.push({ newLength, newLeft, newRight });
        }

        for(int i = 1; i <= n; i++) {
            printf("%d ", a[i]);
        }
        printf("\n");
    }

    return 0;
}
