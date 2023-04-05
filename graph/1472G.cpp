#include <bits/stdc++.h>
 
using namespace std;

void dfs(int u, vector<vector<int>> const &g, vector<int> const &dist, vector<int> &dp, vector<bool> &vis) {
    vis[u] = true;
    dp[u] = dist[u];
    for (int v : g[u]) {
        if (vis[v] == false && dist[u] < dist[v]) {
            dfs(v, g, dist, dp, vis);
        }

        if (dist[u] < dist[v]) {
            dp[u] = min(dp[u], dp[v]);
        } else {
            dp[u] = min(dp[u], dist[v]);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif 

    int test = 1;
    cin>>test;
    for (int tt = 0; tt < test; ++tt)
    {
        int n, m; cin>>n>>m;
        vector<vector<int>> g(n);
        for (int i = 0; i < m; ++i)
        {
            int u, v; cin>>u>>v;
            --u; --v;
            g[u].push_back(v);
        }

        vector<int> dist(g.size(), -1);
        dist[0] = 0;
        queue<int> pq;
        pq.push(0);
        while (!pq.empty()) {
            int u = pq.front(); pq.pop();
            for (int v : g[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    pq.push(v);
                }
            }
        }

        vector<int> dp(n);
        vector<bool> vis(n);
        dfs(0, g, dist, dp, vis);
        for (int i = 0; i < n; i++) {
            cout << dp[i] << " ";
        }
        cout << endl;

    }

    return 0;
}