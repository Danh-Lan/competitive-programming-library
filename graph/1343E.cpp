#include <bits/stdc++.h>

using namespace std;

const int INF = 1e8;

void bfs(int start, vector<vector<int>>& graph, vector<int> &d) {
    d[start] = 0;
    queue<int> q;
    q.push(start);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto v : graph[u]) {
            if (d[v] == INF) {
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }
}

void solve() {
    int n, m, a, b, c;
    cin>>n>>m>>a>>b>>c;
    --a; --b; --c;
    int cost[m];
    for (int i = 0; i < m; ++i) {
        cin>>cost[i];
    }

    sort(cost, cost+m);
    vector<long long> pref(m + 1);
    for (int i = 0; i < m; ++i) {
        pref[i + 1] = pref[i] + cost[i];
    }

    vector<vector<int>> graph(n, vector<int>());
    for (int i = 0; i < m; ++i) {
        int u, v; cin>>u>>v;
        --u; --v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    
    vector<int> da(n, INF), db(n, INF), dc(n, INF);
    bfs(a, graph, da);
    bfs(b, graph, db);
    bfs(c, graph, dc);
    
    long long ans = 1e18;
    for (int i = 0; i < n; ++i) {
        if (da[i] + db[i] + dc[i] > m) continue;
        ans = min(ans, pref[db[i]] + pref[da[i] + db[i] + dc[i]]);
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
    cin>>tt;
    for (int test = 1; test <= tt; test++) {
        solve();
    }

    return 0;
}