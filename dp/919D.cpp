#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif 

    int tt = 1; 
    //cin>>tt;
    for (int test = 1; test <= tt; test++) {
        int n, m; cin>>n>>m;
        string s; cin>>s;
        vector<vector<int>> graph(n, vector<int>());
        vector<int> in(n, 0);
        for (int i = 0; i < m; ++i) {
            int u, v; cin>>u>>v;
            --u; --v;
            graph[u].push_back(v);
            in[v]++;
        }
        
        // dp[i][j] : some path end at i, count the number of j-th char
        vector<vector<int>> dp(n, vector<int>(26, 0));
        for (int i = 0; i < n; ++i) {
            int c = s[i] - 'a';
            dp[i][c] = 1;
        }
        int cnt = 0;
        queue<int> q;
        for (int u = 0; u < n; ++u) {
            if (in[u] == 0) q.push(u);
        }

        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : graph[u]) {
                int c = s[v] - 'a';
                for (int i = 0; i < 26; ++i) {
                    if (i != c) {
                        dp[v][i] = max(dp[v][i], dp[u][i]);
                    } else {
                        dp[v][i] = max(dp[v][i], dp[u][i]+1);
                    }
                }

                --in[v];
                if (in[v] == 0) q.push(v);
            }

            ++cnt;
        }

        if (cnt != n) cout<<-1<<endl;
        else {
            int ans = 0;
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < 26; ++j) {
                    ans = max(ans, dp[i][j]);
                }
            }

            cout<<ans<<endl;
        }

    }

    return 0;
}