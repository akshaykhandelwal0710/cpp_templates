// matrix exponentiation
vector<vector<$type$>> matexp(vector<vector<$type$>> &mat, long long k){
    int n = (int)mat.size();
    if (k == 0){
        vector<vector<$type$>> id(n, vector<$type$>());
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                id[i].push_back(0);
            }
            id[i][i] = 1;
        }
        return id;
    }
    else if (k%2){
        vector<vector<$type$>> w = matexp(mat, k - 1);
        return matmul(w, mat);
    }
    else{
        vector<vector<$type$>> w = matexp(mat, k/2);
        return matmul(w, w);
    }
}

// matrix multiplication
vector<vector<$type$>> matmul(vector<vector<$type$>> &a, vector<vector<$type$>> &b){
    int n = (int)a.size(), m = (int)a[0].size(), l = (int)b[0].size();
    vector<vector<$type$>> ret(n, vector<$type$>());
    for (int i = 0; i < n; i++){
        for (int j = 0; j < l; j++){
            $type$ ths = 0;
            for (int k = 0; k < m; k++){
                ths += a[i][k] * b[k][j];
            }
            ret[i].push_back(ths);
        }
    }
 
    return ret;
}

// gaussian elimination to solve a system of linear equations
vector<$type$> solve(vector<vector<$type$>> &v){
    int n = (int)v.size();
    for (int i = 0; i < n; i++){
        for (int j = i; j < n; j++){
            if (v[j][i].vl){
                if (j != i){
                    swap(v[j], v[i]);
                }
                break;
            }
        }
        for (int j = 0; j <= n; j++){
            if (j != i){
                v[i][j] /= v[i][i];
            }
        }
        v[i][i] = 1;
        for (int j = 0; j < n; j++){
            if (i != j){
                $type$ w = v[j][i];
                for (int k = 0; k <= n; k++){
                    v[j][k] -= v[i][k]*w;
                }
            }
        }
    }

    vector<$type$> ret;
    for (int i = 0; i < n; i++){
        ret.push_back(v[i][n]);
    }

    return ret;
}