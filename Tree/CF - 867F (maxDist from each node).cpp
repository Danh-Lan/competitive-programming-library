#include<bits/stdc++.h>
 
using namespace std;

void dfs(vector<vector<int>>& graph, int v, int par, int h, vector<int> &d) {
    d[v] = h;
    for (int i : graph[v]) {
        if (i != par) {
            dfs(graph, i, v, h + 1, d);
        }
    }
}

void solve() {
    int n, k, c;
    cin >> n >> k >> c;

    vector<vector<int>> graph(n);
    for (int i = 0; i < n-1; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;

        graph[u].push_back(v);
        graph[v].push_back(u); 
    }

    vector<int> dRoot(n), d1(n), d2(n);
    dfs(graph, 0, -1, 0, dRoot);
    int a = max_element(dRoot.begin(), dRoot.end()) - dRoot.begin();
    dfs(graph, a, -1, 0, d1);
    int b = max_element(d1.begin(), d1.end()) - d1.begin();
    dfs(graph, b, -1, 0, d2);

    long long ans = 0LL;
    for (int i = 0; i < n; ++i) {
        int mxDist = max(d1[i], d2[i]);
        
        ans = max(ans, 1LL*k*mxDist - 1LL*c*dRoot[i]);
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
 
    int tt = 1; 
    cin >> tt;
    for (int test = 1; test <= tt; test++) {
        solve();
    }
 
    return 0;
}
