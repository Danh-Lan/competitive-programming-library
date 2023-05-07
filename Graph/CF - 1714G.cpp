#include <bits/stdc++.h>

using namespace std;

void dfs(vector<vector<int>>& child, vector<long long>& cost, vector<long long>& pref, vector<int>& a, vector<int>& b, vector<int>& ans, vector<long long>& curPath, int u = 0) {
    for (int v : child[u]) {
        cost[v] = cost[u] + a[v];
        pref[v] = pref[u] + b[v];
        curPath.push_back(pref[v]);
        ans[v] = upper_bound(curPath.begin(), curPath.end(), cost[v]) - curPath.begin();
        dfs(child, cost, pref, a, b, ans, curPath, v);
        curPath.pop_back();
    }
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
        int n; cin>>n;
        int par[n];
        vector<int> a(n), b(n);
        vector<vector<int>> child(n, vector<int>());
        for (int i = 1; i < n; ++i) {
            cin>>par[i]>>a[i]>>b[i];
            par[i]--;
            child[par[i]].push_back(i);
        }

        vector<long long> cost(n, 0), pref(n, 0);
        vector<int> ans(n, 0);
        vector<long long> curPath;
        dfs(child, cost, pref, a, b, ans, curPath);

        for (int i = 1; i < n; ++i) {
            cout<<ans[i]<<" ";
        } cout<<endl;
    }

    return 0;
}