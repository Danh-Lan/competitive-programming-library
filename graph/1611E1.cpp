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
        // learn more graph ...
        int n, k; cin>>n>>k;
        vector<int> color(n, -1);
        deque<int> q;
        for(int i = 0; i < k; ++i)
        {
            int x;
            cin >> x;
            color[--x] = 0;
            q.push_back(x);
        }

        color[0] = 1;
        q.push_back(0);
        vector<vector<int>> graph(n);
        for(int i = 0; i < n - 1; ++i)
        {
            int u, v; cin>>u>>v;
            --u; --v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        while(!q.empty()) {
            int v = q.front();
            q.pop_front();
            for(int u: graph[v]) {
                if(color[u] == -1) {
                    color[u] = color[v];
                    q.push_back(u);
                }
            }
        }

        bool flag = false;
        for(int v = 1; v < n; ++v) {
            if(graph[v].size() == 1 && color[v] == 1) {
                flag = true;
                break;
            }
        }

        if (flag == true) cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
 
    }
    return 0;
}