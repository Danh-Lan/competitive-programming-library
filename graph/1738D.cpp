#include <bits/stdc++.h>

using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    
    ios::sync_with_stdio(false);
    cin.tie(0);

    int tt = 1;
    cin >> tt;
    for (int test = 1; test <= tt; ++test) {
        int n; cin >> n;
        int b[n];
        int suf[n+1] = {0};
        vector<vector<int>> graph(n+2, vector<int>());
        for (int i = 0; i < n; ++i) {
            cin >> b[i];
            if (b[i] > 0) suf[b[i]-1]++;
            graph[b[i]].push_back(i+1);
        }

        int k = n;
        for (int i = n-1; i >= 0; --i) {
            suf[i] += suf[i+1];
            if (suf[i] == i) {
                k = i;
                break;
            }
        }

        int root = (graph[0].empty()) ? n+1 : 0;
        vector<int> ans;
        queue<int> q;
        q.push(root);
        while (!q.empty()) {
            int top = q.front();
            q.pop();
            ans.push_back(top);
            for (auto v : graph[top]) {
                if (graph[v].size() == 0) {
                    ans.push_back(v);
                } else {
                    q.push(v);
                }
            }
        }

        cout << k << '\n';
        for (int i = 1; i < ans.size(); ++i) {
            cout << ans[i] << ' ';
        } cout << '\n';
    }

    return 0;
}