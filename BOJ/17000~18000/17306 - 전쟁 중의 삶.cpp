#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <unordered_set>
#include <set>
using namespace std;

using ll = long long int;

int n;
int minDepth = 101;

struct Node
{
    Node* child[2];
    bool has;
    Node()
    {
        child[0] = nullptr;
        child[1] = nullptr;
        has = false;
    }
    ~Node()
    {
        if(child[0] != nullptr) delete child[0];
        if(child[1] != nullptr) delete child[1];
    }

    void insert(vector<int>& bits, int depth)
    {
        if(bits.size() > 0) {
            int b = bits.back();
            if(child[b] == nullptr) {
                child[b] = new Node();
            }

            bits.pop_back();
            child[b]->insert(bits, depth + 1);
        } else {
            has = true;
        }
        if(child[0] != nullptr && child[1] != nullptr && minDepth > depth) minDepth = depth;
        if(has == true && minDepth > depth) minDepth = depth;
    }
};

Node* tree;

ll d;
ll res;

vector<int> bits;
void add(ll x)
{
    bits.clear();
    while(x > 1) {
        bits.push_back(x % 2);
        x /= 2;
    }
    tree->insert(bits, 0);
}

ll p(Node* node, int depth)
{
    ll r = 0;

    if(node->child[0] != nullptr) r += p(node->child[0], depth + 1);
    if(node->child[1] != nullptr) r += p(node->child[1], depth + 1);

    if(depth >= minDepth && (r > 0 || node->has == true)) r++;

    return r;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    tree = new Node();

    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> d;
        add(d);
    }

    cout << p(tree, 0);

    delete tree;

    return 0;
}
