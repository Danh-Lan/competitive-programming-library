#include<bits/stdc++.h>
 
using namespace std;

int farthest_node(vector<vector<int>>& graph, int u, int& diameter) {
    int ans = -1;
    int n = graph.size();
    vector<bool> vis(n, false);
    vector<int> dist(n, 0);
    vis[u] = true;
    queue<int> q;
    q.push(u);

    while (!q.empty()) {
        int top = q.front();
        q.pop();
        vis[top] = true;

        for (int v : graph[top]) {
            if (!vis[v]) {
                vis[v] = true;
                dist[v] = dist[top]+1;
                diameter = max(diameter, dist[v]);
                q.push(v);
            }
        }
    }

    int far = u;
    for (int i = 0; i < n; ++i) {
        if (dist[i] == diameter) {
            ans = i;
            break;
        }
    }

    assert(ans >= 0);
    return ans;
}

vector<int> get_dist(vector<vector<int>>& graph, int u) {
    int n = graph.size();
    vector<bool> vis(n, false);
    vector<int> dist(n, 0);
    vis[u] = true;
    queue<int> q;
    q.push(u);

    while (!q.empty()) {
        int top = q.front();
        q.pop();
        vis[top] = true;

        for (int v : graph[top]) {
            if (!vis[v]) {
                vis[v] = true;
                dist[v] = dist[top]+1;
                q.push(v);
            }
        }
    }

    return dist;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
 
    int tt = 1; 
    //cin >> tt;
    for (int test = 1; test <= tt; test++) {
        int n; cin >> n;
        vector<vector<int>> graph(n);
        for (int i = 0; i < n-1; ++i) {
            int u, v; cin >> u >> v;
            --u; --v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        int diameter = 0;
        int leaf1 = farthest_node(graph, 0, diameter);
        int leaf2 = farthest_node(graph, leaf1, diameter);

        vector<int> dist_leaf1 = get_dist(graph, leaf1);
        vector<int> dist_leaf2 = get_dist(graph, leaf2);
        vector<int> dist(n, 0);
        vector<int> cntDist(n+1, 0);
        for (int i = 0; i < n; ++i) {
            if (i == leaf1 || i == leaf2) {
                dist[i] = diameter;
            } else {
                dist[i] = max(dist_leaf1[i], dist_leaf2[i]);
            }

            cntDist[dist[i]]++;
        }

        int cur = 0;
        vector<int> ans(n+1, 0);
        for (int i = n; i >= 1; --i) {
            cur += cntDist[i];
            if (cur == 0) ans[i] = n;
            else {
                ans[i] = 1 + (n-cur);
            }
        }

        for (int i = 1; i <= n; ++i) {
            cout << ans[i] << ' ';
        } cout << '\n';
    }
 
    return 0;
}