// low level solution
// take advantage of the fact that each V in G; deg+(V) <= 1
// the hard part is deal with cycle

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
        int n, m; cin>>n>>m;
        string s[n];
        for (int i = 0; i < n; ++i)
        {
            cin>>s[i];
        }

        vector<int> graph(n*m, -1);
        vector<int> in(n*m, 0), dp(n*m, -1);
        queue<int> nodes;
        vector<vector<int>> tG(n*m); //transpose
        vector<bool> cycle(n * m, true);
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                int coor = i*m+j;
                if (s[i][j] == 'R') {
                    if (j < m-1) {
                        graph[coor] = coor+1;
                        in[coor+1]++;
                    }
                } else if (s[i][j] == 'L') {
                    if (j > 0) {
                        graph[coor] = coor-1;
                        in[coor-1]++;
                    }
                } else if (s[i][j] == 'U') {
                    if (i > 0) {
                        graph[coor] = coor-m;
                        in[coor-m]++;
                    }
                } else {
                    if (i < n-1) {
                        graph[coor] = coor+m;
                        in[coor+m]++;
                    }
                }

                if (graph[coor] == -1) {
                    nodes.push(coor);
                    dp[coor] = 1;
                }
            }
        }

        for (int i = 0; i < n*m; ++i)
        {
            if (graph[i] != -1) tG[graph[i]].push_back(i);
        }
        
        while (!nodes.empty()) {
            int u = nodes.front(); nodes.pop();
            for (int v : tG[u]) {
                dp[v] = dp[u] + 1;
                nodes.push(v);
            }
        }
        for (int i = 0; i < n*m; ++i)
        {
            if (dp[i] != -1) {
                cycle[i] = false;
            } else if (in[i] == 0) {
                nodes.push(i);
            }
        }

        while (!nodes.empty()) {
            int u = nodes.front(); nodes.pop();
            cycle[u] = false;
            in[graph[u]]--;
            if (in[graph[u]] == 0) {
                nodes.push(graph[u]);
            }
        }
        for (int i = 0; i < n*m; ++i)
        {
            if (cycle[i] == true && dp[i] == -1) {
                int u = i;
                int cnt = 0;
                while (true) {
                    u = graph[u];
                    cnt++;
                    if (u == i) {
                        break;
                    }
                }

                while (true) {
                    dp[u] = cnt;
                    nodes.push(u);
                    while (!nodes.empty()) {
                        int u2 = nodes.front(); nodes.pop();
                        for (int v : tG[u2]) {
                            if (!cycle[v]) {
                                dp[v] = dp[u2] + 1;
                                nodes.push(v);
                            }
                        }
                    }
                    u = graph[u];
                    if (u == i) {
                        break;
                    }
                }
            } 
        }

        int r, c, d = 0;
        for (int j = 0; j < n * m; j++) {
            if (dp[j] > d) {
                r = j / m;
                c = j % m;
                d = dp[j];
            }
        }
        cout<<r+1<<" "<<c+1<<" "<<d<<endl;
    }

    return 0;
}