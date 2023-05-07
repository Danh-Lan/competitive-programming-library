#include <bits/stdc++.h>
 
using namespace std;

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
        int n, k; cin>>n>>k;
        int x, y; cin>>x>>y;
        --x; --y;

        vector<vector<int>> g(n);
        int chore[k];
        for (int i = 0; i < k; ++i)
        {
            cin>>chore[i];
            --chore[i];
        }
        for (int i = 0; i < n-1; ++i)
        {
            int u, v; cin>>u>>v;
            --u; --v;
            g[u].push_back(v);
            g[v].push_back(u);
        }

        vector<int> par(n);
        vector<bool> treated(n, false);
        queue<int> nodes;
        par[x] = x; nodes.push(x); treated[x] = true;
        int root = x;
        while (!nodes.empty()) {
            int u = nodes.front(); nodes.pop();
            treated[u] = true;
            for (auto v : g[u]) {
                if (treated[v] == false) {
                    treated[v] = true;
                    par[v] = u;
                    nodes.push(v);
                }
            }
        }

        vector<int> used(n, -1);
        int dest = y;
        if (dest != x) {
            while (dest != x) {
                used[dest] = 1;
                dest = par[dest];
            }
        }

        for (int i = 0; i < k; ++i)
        {
            nodes.push(chore[i]);
        }
        while (!nodes.empty()) {
            int u = nodes.front(); nodes.pop();
            if (used[u] == -1 && u != root) {
                used[u] = 2;
                nodes.push(par[u]);
            }
        }

        int ans = 0;
        for (int i = 0; i < n; ++i)
        {
            if (used[i] != -1) ans += used[i];
        }
        cout<<ans<<endl;

    }

    return 0;
}