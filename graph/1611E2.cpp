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
        int n, k; cin>>n>>k;
        // A : color 0; friend : color 1 to k
        vector<int> color(n, -1);
        queue<int> q;
        int cnt = 0;
        for(int i = 0; i < k; ++i)
        {
            int x; cin>>x;
            color[--x] = i+1;
            q.push(x);
        }

        color[0] = 0;
        q.push(0);
        vector<vector<int>> graph(n);
        for (int i = 0; i < n - 1; ++i)
        {
            int u, v; cin>>u>>v;
            --u; --v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : graph[u]) {
                if (color[v] == -1) {
                    color[v] = color[u];
                    q.push(v);
                } else if (color[v] > 0 && color[u] == 0) cnt++;
            }
        }

        bool flag = false;
        for (int u = 1; u < n; ++u) {
            if (graph[u].size() == 1 && color[u] == 0) {
                flag = true;
                break;
            }
        }
        
        if (flag == true) cout<<-1<<endl;
        else {
            cout<<cnt<<endl;
        }
    }

    return 0;
}