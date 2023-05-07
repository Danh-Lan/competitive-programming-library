#include <bits/stdc++.h>

using namespace std;

int cur;

void dfs(int v, vector<bool>& vis, vector<vector<pair<int,int>>>& g) {
    vis[v] = true;
    for (auto e : g[v]) {
        int u = e.first, w = e.second;
        if (!vis[u] && (cur | w) == cur) {
            dfs(u, vis, g);
        }
    }
}

void cnt(int pw, vector<vector<pair<int,int>>>& g){
    if (pw < 0) return;
    int d = (long long) 1 << pw;
    cur -= d;
    vector<bool> vis(g.size());
    dfs(0, vis, g);
    for (bool b : vis) {
        if (!b) {
            cur += d;
            break;
        }
    }
    cnt(pw - 1, g);
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
        int n, m; cin>>n>>m;
        vector<vector<pair<int,int>>> g(n);
        for (int i = 0; i < m; ++i)
        {
            int u, v, w; cin>>u>>v>>w;
            --u; --v;
            g[u].push_back({v, w});
            g[v].push_back({u, w});
        }

        cur = 1;
        int bit = 0;
        for(; cur <= 1e9; bit++){
            cur = 2 * cur + 1;
        }
        cnt(bit, g);
        cout<<cur<<'\n';
    }

    return 0;
}