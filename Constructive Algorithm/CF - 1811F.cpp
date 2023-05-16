#include<bits/stdc++.h>
 
using namespace std;

bool connected(vector<vector<int>>& graph, int goal, int src = 0) {
    int cnt = 0;
    int n = graph.size();
    vector<int> vis(n, false);
    queue<int> q;
    q.push(src);
    vis[src] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cnt++;

        for (int v : graph[u]) {
            if (!vis[v]) {
                vis[v] = true;
                q.push(v);
            }
        }
    }

    return (cnt == goal);
}

bool smallCycle(vector<vector<int>>& graph, int goal, int src) {
    int cnt = 0;
    int n = graph.size();
    vector<int> vis(n, false);
    queue<int> q;
    vis[src] = true;
    
    for (int v : graph[src]) {
        if (graph[v].size() == 2) {
            q.push(v);
            vis[v] = true;
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cnt++;

        for (int v : graph[u]) {
            if (!vis[v]) {
                vis[v] = true;
                q.push(v);
            }
        }
    }
    return (cnt == goal);
}

bool bigCycle(vector<vector<int>>& graph, int goal, int src) {
    if (src == -1) return false;
    
    int cnt = 0;
    int n = graph.size();
    vector<int> vis(n, false);
    queue<int> q;
    vis[src] = true;
    q.push(src);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cnt++;

        for (int v : graph[u]) {
            if (!vis[v] && graph[v].size() == 4) {
                vis[v] = true;
                q.push(v);
            }
        }
    }

    return (cnt == goal);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout); 
    #endif

    int tt = 1; 
    cin >> tt;
    for (int test = 1; test <= tt; test++) {
        int n, m;
        cin >> n >> m;

        vector<vector<int>> graph(n);
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            --u; --v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        int k = sqrt(n);
        bool bad = false;
        if (n != k * k || m != n + k) {
            bad = true;
        }

        int node4 = -1;
        int cnt4 = 0;
        for (int i = 0; i < n; ++i) {
            if (graph[i].size() != 2 && graph[i].size() != 4) {
                bad = true;
                break;
            } else if (graph[i].size() == 4) {
                node4 = i;
                cnt4++;
            }
        }

        if (cnt4 != k) bad = true;

        if (!connected(graph, n)) bad = true;


        for (int i = 0; i < n; ++i) {
            if (graph[i].size() == 4) {
                if (!smallCycle(graph, k-1, i)) {
                    bad = true;
                    break;
                }
            }
        }

        if (!bigCycle(graph, k, node4)) bad = true;

        if (bad) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
        }
    }

    return 0;
}
