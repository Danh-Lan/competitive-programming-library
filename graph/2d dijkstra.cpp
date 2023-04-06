#include <bits/stdc++.h>

using namespace std;

vector<int> dx = {-1, 0, 1, 0};
vector<int> dy = {0, 1, 0, -1};

const int INF = 1000000;

int dijkstra(vector<vector<pair<int,int>>>& adj, int begin, int goal, int n) {
    int ans = INF;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, begin});
    vector<int> dist(n, INF);
    dist[begin] = 0;
    vector<int> par(n);
    while(!pq.empty()) {
        auto f = pq.top();
        pq.pop();
        int to = f.second;
        if (to == goal) {
            ans = dist[goal];
            break;
        }
        int d = f.first;
        if(d != dist[to]) continue;
        for (auto i : adj[to]) {
            if(d + i.second < dist[i.first]) {
                dist[i.first] = d + i.second;
                pq.push({d + i.second, i.first});
                par[i.first] = to;
            }
        }
    }
    
    return ans;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n; cin >> n;
    string s[n];
    pair<int,int> key = {-1, -1};
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
    }
    
    bool found = false;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (s[i][j] == 'O') {
                key.first = i;
                key.second = j;
                found = true;
                break;
            }
        }
        if (found) break;
    }

    vector<vector<pair<int,int>>> adj(n*n, vector<pair<int,int>>());
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < 4; ++k) {
                int xx = i + dx[k];
                int yy = j + dy[k];

                int w1 = 0, w2 = 0;
                if (s[xx][yy] == 'X') w1 = 1;
                if (s[i][j] == 'X') w2 = 1;

                if (xx >= 0 && yy >= 0 && xx < n && yy < n) {
                    adj[i*n + j].push_back(make_pair(xx*n + yy, w1));
                    adj[xx*n + yy].push_back(make_pair(i*n + j, w2));
                }
            }
        }
        
        cout << i << endl;
    }
    
    int toKey = dijkstra(adj, 0, key.first*n+key.second, n*n);
    int toGoal = dijkstra(adj, key.first*n+key.second, n*n-1, n*n);
    int ans = toKey + toGoal;
    
    cout << ans << '\n';

    return 0;
}