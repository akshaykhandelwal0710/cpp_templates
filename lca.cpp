const int mxp = 20;

void create_par(int p, int c, vector<vector<int>> &adj, vector<vector<int>> &par, vector<int> &dpth) {
    for (auto &ele: adj[c]) {
        if (ele != p) {
            dpth[ele] = dpth[c] + 1;
            par[ele][0] = c;
            for (int i = 1; i < mxp; i++) par[ele][i] = par[par[ele][i - 1]][i - 1];
            create_par(c, ele, adj, par, dpth);
        }
    }
}

int get_par(int u, int k, vector<vector<int>> &par) {
    for (int i = 0; i < mxp; i++) {
        if (k & (1 << i)) u = par[u][i];
    }

    return u;
}

int lca(int u, int v, vector<vector<int>> &par, vector<int> &dpth) {
    if (dpth[u] > dpth[v]) swap(u, v);
    v = get_par(v, dpth[v] - dpth[u], par);

    if (u == v) return u;
    for (int k = mxp - 1; k >= 0; k--) {
        if (par[u][k] != par[v][k]) {
            u = par[u][k], v = par[v][k];
        }
    }
    u = par[u][0];

    return u;
}