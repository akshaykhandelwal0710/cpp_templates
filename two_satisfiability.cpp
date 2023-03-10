struct two_sat{
    vector<vector<int>> adj, rev_adj, comp_adj;
    vector<int> comp, topo, topo_loc;
    vector<bool> visited, val;
    int io, jo, sz, cur;

    two_sat(int n){
        comp.resize(2 * n, 0);
        visited.resize(2 * n, false);
        adj.resize(2 * n, vector<int>());
        rev_adj.resize(2 * n, vector<int>());
        val.resize(n, false);
        sz = n;
    }

    void add_disjunction(int i, bool ii, int j, bool jj){
        io = ii, jo = jj;
        adj[i * 2 + (io ^ 1)].push_back(j * 2 + jo);
        adj[j * 2 + (jo ^ 1)].push_back(i * 2 + io);

        rev_adj[j * 2 + jo].push_back(i * 2 + (io ^ 1));
        rev_adj[i * 2 + io].push_back(j * 2 + (jo ^ 1));
    }

    void dfs(int c){
        visited[c] = true;
        for (auto &ele: adj[c]){
            if (!visited[ele]){
                dfs(ele);
            }
        }
        topo.push_back(c);
    }

    void dfs2(int c){
        visited[c] = true;
        comp[c] = cur;
        for (auto &ele: rev_adj[c]){
            if (!visited[ele]){
                dfs2(ele);
            }
        }
    }

    bool solve(){
        cur = 0;
        for (int i = 0; i < 2 * sz; i++){
            if (!visited[i]){
                dfs(i);
            }
        }

        reverse(topo.begin(), topo.end());
        for (int i = 0; i < 2 * sz; i++){
            visited[i] = false;
        }
        for (auto &i: topo){
            if (!visited[i]){
                comp_adj.push_back({});
                dfs2(i);
                ++cur;
            }
        }

        for (int i = 0; i < 2 * sz; i++){
            for (auto &ele: adj[i]){
                if (comp[ele] != comp[i]){
                    comp_adj[comp[i]].push_back(comp[ele]);
                }
            }
        }
        swap(comp_adj, adj);

        topo.clear();
        for (int i = 0; i < cur; i++){
            visited[i] = false;
        }
        for (int i = 0; i < cur; i++){
            if (!visited[i]){
                dfs(i);
            }
        }
        reverse(topo.begin(), topo.end());

        topo_loc.resize(cur, 0);
        for (int i = 0; i < cur; i++){
            topo_loc[topo[i]] = i;
        }
        for (int i = 0; i < 2 * sz; i++){
            comp[i] = topo_loc[comp[i]];
        }

        for (int i = 0; i < sz; i++){
            if (comp[i * 2] == comp[i * 2 + 1]){
                return false;
            }
            val[i] = (comp[i * 2 + 1] > comp[i * 2]);
        }

        return true;
    }
};