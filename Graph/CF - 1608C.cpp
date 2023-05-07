// dfs on transpose graph from the biggest node, if any node wasn't visited 
// that player can't win

#include <bits/stdc++.h>
 
using namespace std;

void dfs(vector<bool>& vis, vector<vector<int>>& g, int u) {
    if (vis[u] == true) return;
    vis[u] = true;
    for (auto v : g[u]) {
        dfs(vis, g, v);
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
        int n; cin>>n;
        pair<int, int> a[n], b[n];
        for (int i = 0; i < n; ++i)
        {
            cin>>a[i].first;
            a[i].second = i;
        }
        for (int i = 0; i < n; ++i)
        {
            cin>>b[i].first;
            b[i].second = i;
        }
        sort(a, a+n); sort(b, b+n);
        vector<vector<int>> g(n);
        for (int i = n-1; i > 0; --i)
        {
            g[a[i-1].second].push_back(a[i].second);
            if (a[i].second != b[i].second || a[i-1].second != b[i-1].second) {
                g[b[i-1].second].push_back(b[i].second);
            }
        }

        string ans = string(n, '0');
        vector<bool> vis(n, false);
        dfs(vis, g, a[n-1].second);
        for (int i = 0; i < n; ++i)
        {
            if (vis[a[i].second] == true) {
                ans[a[i].second] = '1';
            }
        }

        cout<<ans<<endl;
    }

    return 0;
}
