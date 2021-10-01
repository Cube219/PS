#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

using ll = long long int;

constexpr double leps = 1e-9;
void gauss(vector<vector<double>>& mat, vector<vector<double>>& res)
{
    int n = mat.size();
    int m = mat[0].size();
    int rm = res[0].size();

    vector<int> pivot(n, -1);
    int row = 0;
    for(int col = 0; col < m; ++col) {
        int mxrow = row;
        for(int i = row; i < n; ++i) {
            if(abs(mat[i][col]) > abs(mat[mxrow][col])) mxrow = i;
        }
        if(abs(mat[mxrow][col]) < leps) continue;

        swap(mat[mxrow], mat[row]);
        swap(res[mxrow], res[row]);
        pivot[col] = row;

        for(int i = 0; i < n; ++i) {
            if(i == row) continue;
            double c = mat[i][col] / mat[row][col];
            for(int j = 0; j < m; ++j) {
                mat[i][j] -= mat[row][j] * c;
            }
            for(int j = 0; j < rm; ++j) {
                res[i][j] -= res[row][j] * c;
            }
        }

        row++;
    }

    for(int i = 0; i < n; ++i) {
        double v = 0;
        for(int j = 0; j < m; ++j) {
            if(abs(mat[i][j]) >= leps) {
                v = mat[i][j];
                mat[i][j] = 1;
                break;
            }
        }
        for(int j = 0; j < rm; ++j) {
            res[i][j] /= v;
        }
    }
}

struct Node
{
    double x, y, z;
    void norm()
    {
        double v = sqrt(x * x + y * y + z * z);
        x /= v; y /= v; z /= v;
    }
};

Node operator-(Node l, Node r)
{
    return { l.x - r.x, l.y - r.y, l.z - r.z };
}

Node cross(Node a, Node b)
{
    return { a.y * b.z - b.y * a.z, b.x * a.z - a.x * b.z, a.x * b.y - b.x * a.y };
}

int tNum;

bool isinter(vector<Node>& tri, Node p1, Node p2)
{
    if((p1.z < 0 && p2.z < 0) || (p1.z > 0 && p2.z > 0)) return false;
    if(p1.z > 0) swap(p1, p2);

    double c = p2.z / (p2.z - p1.z);
    if(abs(p2.z - p1.z) < leps) return false;
    Node n = p1 - p2;
    p2.x += n.x * c;
    p2.y += n.y * c;
    p2.z += n.z * c;

    bool isneg[3] = { false, false, false };
    for(int i = 0; i < 3; ++i) {
        Node v1 = tri[(i + 1) % 3] - tri[i];
        Node v2 = p2 - tri[i];
        if(cross(v1, v2).z < 0) isneg[i] = true;
    }
    if(isneg[0] != isneg[1] || isneg[0] != isneg[2]) return false;
    return true;
}

int process(vector<Node> p1, vector<Node> p2)
{
    vector<vector<double>> mat, imat;
    Node b1 = p1[1] - p1[0];
    Node b2 = cross(b1, p1[2] - p1[0]);
    Node b3 = cross(b2, b1);
    b1.norm(); b2.norm(); b3.norm();
    mat.resize(3);
    for(int i = 0; i < 3; ++i) {
        mat[i].resize(3);
    }
    mat[0][0] = b1.x;
    mat[1][0] = b1.y;
    mat[2][0] = b1.z;
    mat[0][1] = b3.x;
    mat[1][1] = b3.y;
    mat[2][1] = b3.z;
    mat[0][2] = b2.x;
    mat[1][2] = b2.y;
    mat[2][2] = b2.z;

    imat.resize(3);
    for(int i = 0; i < 3; ++i) {
        imat[i].resize(3, 0);
        imat[i][i] = 1;
    }

    gauss(mat, imat);

    for(int i = 0; i < 3; ++i) {
        Node tmp;
        tmp.x = imat[0][0] * p2[i].x + imat[0][1] * p2[i].y + imat[0][2] * p2[i].z;
        tmp.y = imat[1][0] * p2[i].x + imat[1][1] * p2[i].y + imat[1][2] * p2[i].z;
        tmp.z = imat[2][0] * p2[i].x + imat[2][1] * p2[i].y + imat[2][2] * p2[i].z;
        p2[i] = tmp;

        tmp.x = imat[0][0] * p1[i].x + imat[0][1] * p1[i].y + imat[0][2] * p1[i].z;
        tmp.y = imat[1][0] * p1[i].x + imat[1][1] * p1[i].y + imat[1][2] * p1[i].z;
        tmp.z = imat[2][0] * p1[i].x + imat[2][1] * p1[i].y + imat[2][2] * p1[i].z;
        p1[i] = tmp;
    }
    double zz = p1[0].z;
    for(int i = 0; i < 3; ++i) {
        p1[i].z -= zz;
        p2[i].z -= zz;
    }

    int res = 0;
    for(int i = 0; i < 3; ++i) {
        if(isinter(p1, p2[i], p2[(i + 1) % 3]) == true) res++;
    }

    return res;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<Node> p1, p2;
    p1.resize(3); p2.resize(3);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; ++tt) {
        for(int i = 0; i < 3; ++i) {
            cin >> p1[i].x >> p1[i].y >> p1[i].z;
        }
        for(int i = 0; i < 3; ++i) {
            cin >> p2[i].x >> p2[i].y >> p2[i].z;
        }

        int r1 = process(p1, p2);
        int r2 = process(p2, p1);
        bool res = false;
        if(r1 == 1 || r2 == 1) res = true;
        else if(r1 == 2 && r2 == 2) res = true;
        // cout << r1 << " " << r2 << "\n";
        if(res == true) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
