#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 9, LG = 18;

vector<int> g[N];
int par[N][LG + 1], dep[N], sz[N];

void dfs(int u, int p = 0) {
    par[u][0] = p;
    dep[u] = dep[p] + 1;
    sz[u] = 1;
    for (int i = 1; i <= LG; i++) par[u][i] = par[par[u][i - 1]][i - 1];
    for (auto v: g[u]) if (v != p) {
        dfs(v, u);
        sz[u] += sz[v];
    }
}
int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int k = LG; k >= 0; k--) if (dep[par[u][k]] >= dep[v]) u = par[u][k];
    if (u == v) return u;
    for (int k = LG; k >= 0; k--) if (par[u][k] != par[v][k]) u = par[u][k], v = par[v][k];
    return par[u][0];
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    
    ios::sync_with_stdio(false);
    cin.tie(0);

    int tt = 1;
    //cin >> tt;
    for (int test = 1; test <= tt; test++) {
        int n; cin >> n;
        for (int i = 0; i < n-1; ++i) {
            int u, v; cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        dfs(1);
        int q; cin >> q;
        for (int i = 0; i < q; ++i) {
            int k; cin >> k;
            int node[k];
            for (int j = 0; j < k; ++j) {
                cin >> node[j];
            }
            sort(node, node + k, [&] (int x, int y) {
                return (dep[x] > dep[y]);
            });

            bool flag = true;
            int idx = -1;
            vector<bool> visit(k, false);
            for (int j = 0; j < k; ++j) {
                if (lca(node[0], node[j]) == node[j]) visit[j] = true;
            }

            for (int j = 0; j < k; ++j) {
                if (lca(node[0], node[j]) != node[j]) {
                    idx = j;
                    break;
                }
            }

            if (idx != -1) {
                for (int j = idx; j < k; ++j) {
                    if (lca(node[idx], node[j]) == node[j]) visit[j] = true;
                }

                if (dep[lca(node[idx], node[0])] > dep[node[k-1]]) {
                    flag = false;
                }
            }

            for (int j = 0; j < k; ++j) {
                if (!visit[j]) {
                    flag = false;
                    break;
                }
            }

            if (flag) cout << "YES\n";
            else cout << "NO\n";
        }
    }

    return 0;
}