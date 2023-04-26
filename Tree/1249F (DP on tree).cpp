#include <bits/stdc++.h>

using namespace std;

int N = 201;
int n, k;
vector<int> a;
vector<vector<int>> graph, dp;
// depth is relative wrt to v --> dp[v][j] dep[v] = 0, dep[child[v]] = 1...
void dfs(int v, int p) {
    for (auto to : graph[v]) {
        if (to != p) dfs(to, v);
    }
    
    for (int dep = 0; dep < N; ++dep) {
        if (dep == 0) {
            dp[v][0] = a[v];
            for (auto to : graph[v]) {
                if (to == p) continue;
                dp[v][dep] += dp[to][k-1];
            }
        } else {
            for (auto to : graph[v]) {
                if (to == p) continue;
                int cur = dp[to][dep-1];
                for (auto other : graph[v]) {
                    if (other == to || other == v) continue;
                    cur += dp[other][max(dep-1, k-dep-1)];
                }

                dp[v][dep] = max(dp[v][dep], cur);
            }
        }
    }

    for (int dep = N-1; dep > 0; --dep) {
        dp[v][dep-1] = max(dp[v][dep-1], dp[v][dep]);
    }
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
        cin >> n >> k;
        ++k;
        a = vector<int>(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }

        graph = vector<vector<int>>(n);
        for (int i = 0; i < n-1; ++i) {
            int u, v; cin >> u >> v;
            --u; --v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        dp = vector<vector<int>>(n, vector<int>(N));
        dfs(0, -1);
        cout << dp[0][0] << endl;
    }

    return 0;
}
