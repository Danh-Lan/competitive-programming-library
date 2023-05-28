/* 
    We find all cycle
    For each cycle : we find all the vertex that can lead to the cycle
    Let the size of the cycle be sz,
then there are at most sz robots can be placed in this cycle
    Let a node of the cycle be c, 
    We "color" all the vertex by its distance to c modulo sz
    For each color there can only be 1 robot placed, 
    If there is a black square then we place a robot there
*/

#include<bits/stdc++.h>
 
using namespace std;

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

        map<char, pair<int,int>> dir;
        dir['L'] = {0, -1}; dir['R'] = {0, 1};
        dir['U'] = {-1, 0}; dir['D'] = {1, 0};

        vector<int> child(n*m, -1);
        vector<vector<int>> parent(n*m);
        string color(n*m, ' '), grid[n];
        for (int i = 0; i < n; ++i) {
            string c;
            cin >> c;
            for (int j = 0; j < m; ++j) {
                color[i*m+j] = c[j];
            }
        }
        for (int i = 0; i < n; ++i) {
            cin >> grid[i];
            for (int j = 0; j < m; ++j) {
                int x = i + dir[grid[i][j]].first;
                int y = j + dir[grid[i][j]].second;

                int cur = i*m + j;
                int target = x*m + y;

                child[cur] = target;
                parent[target].push_back(cur);
            }
        }

        int cnt = 0, cntBlack = 0;
        vector<bool> vis(n*m, false), visCycle(n*m, false);
        for (int i = 0; i < n*m; ++i) {
            if (!vis[i]) {
                int cur = i;
                while (!vis[cur]) {
                    vis[cur] = true;
                    cur = child[cur];
                }

                int beg = cur;
                cur = child[cur];
                visCycle[beg] = true;
                vector<int> cycle = {beg};
                while (cur != beg) {
                    visCycle[cur] = true;
                    cycle.push_back(cur);
                    cur = child[cur];
                }

                int sz = cycle.size();
                cnt += sz;

                vector<vector<int>> pos(sz);
                
                for (int j = 0; j < sz; ++j) {
                    int cur2 = cycle[j];
                    pos[j].push_back(cur2);

                    map<int, int> value;
                    value[cur2] = j;
                    queue<int> q;
                    q.push(cur2);

                    while (!q.empty()) {
                        int u = q.front();
                        q.pop();
                        vis[u] = true;

                        for (int par : parent[u]) {
                            if (!visCycle[par]) {
                                vis[par] = true;
                                int val = (value[u] + sz-1) % sz;
                                pos[val].push_back(par);
                                value[par] = val;
                                q.push(par);
                            }
                        }
                    }
                }

                for (int j = 0; j < sz; ++j) {
                    for (int k = 0; k < pos[j].size(); ++k) {
                        if (color[pos[j][k]] == '0') {
                            cntBlack++;
                            break;
                        }
                    }
                }
            }
        }

        cout << cnt << ' ' << cntBlack << '\n';
    }

    return 0;
}