#include<bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    int tt = 1;
    cin >> tt;
    for (int test = 1; test <= tt; test++) {
        int n, m; cin >> n >> m;

        vector<vector<pair<int, long long>>> graph(n);
        for (int i = 0; i < m; ++i) {
            int a, b; long long w; 
            cin >> a >> b >> w;
            --a; --b;
            graph[a].push_back({b, w});
        }

        vector<vector<long long>> cost(n, vector<long long>(n));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cost[i][j] = INF;
            }
            cost[i][i] = 0;

            priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
            for (int j = 0; j < n; ++j) {
                pq.push({cost[i][j], j});
            }
            
            while (!pq.empty()) {
                auto it = pq.top();
                long long dist = it.first;
                int node = it.second;
                pq.pop();
                if (dist > cost[i][node]) continue;
                for (auto it2 : graph[node]) {
                    int next = it2.first;
                    long long w = it2.second;
                    if (dist + w < cost[i][next]) {
                        cost[i][next] = dist + w;
                        pq.push({dist + w, next});
                    }
                }
            }
        }
    }

    return 0;
}