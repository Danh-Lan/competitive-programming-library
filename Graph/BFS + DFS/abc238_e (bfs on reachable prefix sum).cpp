#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    
    ios::sync_with_stdio(false);
    cin.tie(0);

    int tt = 1;
    //cin >> tt;
    for (int test = 1; test <= tt; test++) {
        int n, qq; cin >> n >> qq;
        vector<vector<int>> graph(n+1, vector<int>());
        for (int i = 0; i < qq; ++i) {
            int l, r; cin >> l >> r;
            graph[l-1].push_back(r);
            graph[r].push_back(l-1);
        }

        queue<int> q;
        vector<bool> visit(n+1, false);
        visit[0] = true;
        for (int v : graph[0]) {
            visit[v] = true;
            q.push(v);
        }
        while (!q.empty()) {
            int top = q.front();
            q.pop();
            for (int v : graph[top]) {
                if (!visit[v]) {
                    visit[v] = true;
                    q.push(v);
                }
            }
        }

        if (visit[n]) cout << "Yes\n";
        else cout << "No\n";
    }

    return 0;
}