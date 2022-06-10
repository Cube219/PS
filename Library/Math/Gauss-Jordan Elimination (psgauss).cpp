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
