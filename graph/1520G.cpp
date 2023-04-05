#include <bits/stdc++.h>

using namespace std;

const long long INF = 1e18;

const pair<int,int> offXY[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

long long portal[2] = {INF, INF};
int n, m, w;
long long ans = INF;

bool bfs(pair<int,int>& root, vector<vector<int>>& city, int portalIndex) {
    vector<vector<long long>> dist(n, vector<long long>(m, -1));
    queue<pair<int,int>> q;
    q.push({root.first, root.second});
    dist[root.first][root.second] = 0;

    while (!q.empty()) {
        int topX = q.front().first;
        int topY = q.front().second;
        q.pop();
        if (city[topX][topY] > 0) portal[portalIndex] = min(portal[portalIndex], 1LL*(dist[topX][topY] + 1LL*city[topX][topY]));

        for (int i = 0; i < 4; ++i) {
            int x = topX + offXY[i].first, y = topY + offXY[i].second; 
            if (x >= 0 && x < n && y >= 0 && y < m) {
                if (dist[x][y] == -1 && city[x][y] != -1) {
                    dist[x][y] = dist[topX][topY] + w;
                    q.push({x, y});
                }
            }
        }
    }

    if (portalIndex == 0) {
        if (dist[n-1][m-1] != -1) ans = min(ans, dist[n-1][m-1]);
        else if (portal[portalIndex] == INF) return false;
    } else {
        if (dist[0][0] != -1) ans = min(ans, dist[0][0]);
        else if (portal[portalIndex] == INF) return false;
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif 
    
    int tt = 1; 
    //cin>>tt;
    for (int test = 1; test <= tt; test++) {
        cin>>n>>m>>w;
        vector<vector<int>> city(n, vector<int>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin>>city[i][j];
            }
        }

        pair<int,int> home = {0, 0}, school = {n-1, m-1};
        bool toSchool = bfs(home, city, 0);
        bool toHome = bfs(school, city, 1);
        if (toSchool == false || toHome == false) cout<<-1<<"\n";
        else {
            if (portal[0] != INF && portal[1] != INF) {
                ans = min(ans, portal[0]+portal[1]);
            }
            cout<<ans<<'\n';
        }
    }

    return 0;
}