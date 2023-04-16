#include<bits/stdc++.h>
 
using namespace std;

#define x first
#define y second

vector<vector<int>> calDist(vector<string>& s, int n, int m, pair<int,int>& start) {
    vector<vector<int>> dist(n, vector<int>(m, -1));
    dist[start.x][start.y] = 0;
    vector<vector<bool>> vis(n, vector<bool>(m, false));
    
    pair<int,int> d[4] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
    queue<pair<int,int>> q;
    q.push(start);
    vis[start.x][start.y] = true;
    while (!q.empty()) {
        auto top = q.front();
        q.pop();

        for (int k = 0; k < 4; ++k) {
            int dx = top.x + d[k].x;
            int dy = top.y + d[k].y;
            if (dx >= 0 && dx < n && dy >= 0 && dy < m) {
                if ((s[dx][dy] == '.' || s[dx][dy] == 'B') && !vis[dx][dy]) {
                    vis[dx][dy] = true;
                    q.push({dx, dy});
                    dist[dx][dy] = dist[top.x][top.y] + 1;
                }
            }
        }
    }

    return dist;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<string> s(n);
    pair<int,int> start, end;
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
        for (int j = 0; j < m; ++j) {
            if (s[i][j] == 'A') start = {i, j};
            else if (s[i][j] == 'B') end = {i, j};
        }
    }

    vector<vector<int>> dist = calDist(s, n, m, start);
    
    if (dist[end.x][end.y] == -1) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        cout << dist[end.x][end.y] << '\n';

        string ans = "";
        char dir[4] = {'D', 'U', 'L', 'R'};
        pair<int,int> d[4] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
        pair<int,int> cur = end;
        int curDist = dist[end.x][end.y];

        while (curDist > 0) {
            for (int k = 0; k < 4; ++k) {
                int dx = cur.x + d[k].x;
                int dy = cur.y + d[k].y;
                if (dx >= 0 && dx < n && dy >= 0 && dy < m) {
                    if ((s[dx][dy] == '.' || s[dx][dy] == 'A') && dist[dx][dy] == curDist-1) {
                        if (curDist == 1 && s[dx][dy] != 'A') continue;
                        cur = {dx, dy};
                        ans += dir[k];
                        curDist--;
                        break;
                    }
                }
            }
        }

        reverse(ans.begin(), ans.end());
        cout << ans << '\n';

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
    //cin >> tt;
    for (int test = 1; test <= tt; test++) {
        solve();
    }
 
    return 0;
}
