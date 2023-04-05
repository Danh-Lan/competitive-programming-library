#include <bits/stdc++.h>
 
using namespace std;

const int INF = 202020;
int n = 200000;
vector<int> dist(n+1, -1);
vector<int> in(n+1, 0), out(n+1, 0);
vector<vector<int>> graph(n+1, vector<int>());

int dp(int i) {
    if (dist[i] != -1) return dist[i];
    if (in[i] > 1 && out[i] > 1) {
        dist[i] = 1;
        for (auto j : graph[i]) {
            dist[i] = max(dist[i], dp(j)+1);
        }
    } else if (in[i] > 1) { 
        dist[i] = 1; // go backward, transpose graph
    } else {
        dist[i] = -INF; // source node
    }
    return dist[i];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif 

    int t = 1;
    //cin>>t;
    for (int tt = 0; tt < t; ++tt)
    {
        int m; cin>>n>>m;
        for (int i = 0; i < m; ++i)
        {
            int u, v; cin>>u>>v;
            graph[u].push_back(v);
            out[u]++;
            in[v]++;
        }

        int ans = 1;
        for (int i = 1; i <= n; ++i)
        {
            if (out[i] > 1) {
                for (int j : graph[i]){
                    ans = max(ans, dp(j)+1);
                }
            }
        }

        cout<<ans<<endl;
    }

    return 0;
}