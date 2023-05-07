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
        vector<vector<int>> g(n);
        vector<int> deg(n, 0);
        for (int i = 0; i < n-1; ++i)
        {
            int u, v; cin>>u>>v;
            --u; --v;
            g[u].push_back(v);
            g[v].push_back(u);
            ++deg[u]; ++deg[v];
        }

        if (k >= n) {
            cout<<0<<endl;
            continue;
        }

        queue<int> leaf;
        for (int u = 0; u < n; ++u)
        {
            if (g[u].size() == 0 || g[u].size() == 1) {
                leaf.push(u);
            }
        }

        while (k--) {
            queue<int> newLeaf;
            while (!leaf.empty()) {
                int u = leaf.front(); leaf.pop();
                deg[u] = -1;
                for (auto v : g[u]) {
                    deg[v]--;
                    if (deg[v] == 0 || deg[v] == 1) {
                        newLeaf.push(v);
                    }
                }
            }

            leaf = newLeaf;
            if (leaf.empty()) break;
        }

        int ans = 0;
        for (int i = 0; i < n; ++i)
        {
            if (deg[i] >= 0) ans++;
        }
        cout<<ans<<endl;
    }

    return 0;
}