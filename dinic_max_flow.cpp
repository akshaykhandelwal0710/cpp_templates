struct flow_edge{
    // directed edge u to v
    ll u, v;
    ll cap, flow = 0;
    flow_edge(ll u, ll v, ll cap): u(u), v(v), cap(cap) {}
};

struct Dinic {
    const ll flow_inf = 1e18;
    vector<flow_edge> edges;
    vector<vector<ll>> adj;
    vector<ll> level;
    queue<ll> q;
    ll n, m;

    Dinic(ll n): n(n), m(0) {
        adj.resize(n, vector<ll>());
        level.resize(n, -1);
    }

    void add_edge(ll u, ll v, ll cap) {
        edges.push_back({u, v, cap});
        edges.push_back({v, u, 0});
        adj[u].push_back(m);
        adj[v].push_back(m^1);
        m += 2;
    }

    bool bfs(ll s, ll t) {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            ll u = q.front();
            q.pop();
            for (auto &i: adj[u]) {
                if (edges[i].cap - edges[i].flow < 1) continue;
                if (level[edges[i].v] != -1) continue;
                level[edges[i].v] = level[u] + 1;
                q.push(edges[i].v);
            }
        }

        return (level[t] != -1);
    }

    ll dfs(ll u, ll t, ll pushed) {
        if (!pushed) return 0;
        if (u == t) return pushed;
        for (auto &i: adj[u]) {
            if (edges[i].cap - edges[i].flow < 1) continue;
            if (level[edges[i].v] != level[u]+1) continue;
            ll flo = dfs(edges[i].v, t, min(pushed, edges[i].cap - edges[i].flow));
            if (flo == 0) continue;
            edges[i].flow += flo;
            edges[i^1].flow -= flo;
            return flo;
        }
        return 0;
    }

    // s -> source, t -> sink
    ll max_flow(ll s, ll t) {
        ll flow = 0, nxt;
        while (bfs(s, t)) {
            while ((nxt = dfs(s, t, flow_inf))) flow += nxt;
        }
        return flow;
    }
};