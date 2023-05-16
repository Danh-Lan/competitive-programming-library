#include<bits/stdc++.h>
 
using namespace std;

const int INF = 1e7;

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

        int a[m+1], b[m+1];
        vector<vector<int>> graph(n+1);
        for (int i = 0; i < m; ++i) {
            cin >> a[i] >> b[i];
            if (a[i] != 1) {
                graph[b[i]].push_back(a[i]);
            }
        }

        vector<bool> vis(n+1, false);
        queue<int> q;
        vector<int> cnt(n+1, INF);
        cnt[0] = 0; cnt[1] = 1;
        q.push(1);
        vis[1] = true;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : graph[u]) {
                if (!vis[v]) {
                    vis[v] = true;
                    cnt[v] = min(cnt[v], cnt[u]+1);
                    q.push(v);
                }
            }
        }

        bool flag = false;
        for (int i = 2; i <= n; ++i) {
            if (!vis[i]) {
                flag = true;
                break;
            }
        }

        if (flag) {
            cout << "INFINITE\n";
            continue;
        }

        int mxCnt = *max_element(cnt.begin(), cnt.end());

        vector<vector<int>> ans(mxCnt+1);
        for (int i = 1; i <= n; ++i) {
            ans[cnt[i]].push_back(i);
        }

        cout << "FINITE\n";
        cout << accumulate(cnt.begin(), cnt.end(), 0) << '\n';
        for (int i = 1; i <= mxCnt; ++i) {
            for (int j = mxCnt; j >= i; --j) {
                for (int k = 0; k < ans[j].size(); ++k) {
                    cout << ans[j][k] << ' ';
                }
            }
        } cout << '\n';
    }

    return 0;
}
