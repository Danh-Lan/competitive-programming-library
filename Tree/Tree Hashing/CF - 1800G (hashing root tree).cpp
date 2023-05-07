// learn hashing tree
// blog : https://codeforces.com/blog/entry/113465
// blog : https://rng-58.blogspot.com/2017/02/hashing-and-probability-of-collision.html

#include<bits/stdc++.h>

using namespace std;

int last = 0;
map<vector<int>, int> eq;
map<int, bool> symmetrical;

int dfs(int v, int p, vector<vector<int>>& graph) {
    vector<int> children;
    for (auto u : graph[v]) {
        if (u == p) continue;

        children.push_back(dfs(u, v, graph));
    }

    sort(children.begin(), children.end());
    if (!eq.count(children)) {
        map<int, int> cnt;
        for (int e : children) {
            cnt[e]++;
        }

        int odd = 0, bad = 0;
        for (auto it : cnt) {
            if (it.second & 1) {
                odd++;
                bad += !symmetrical[it.first];
            }
        }

        eq[children] = last;
        symmetrical[last] = (odd < 2 && bad == 0);
        last++;
    }

    return eq[children];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    int tt = 1;
    cin >> tt;
    for (int test = 1; test <= tt; test++) {
        eq.clear();
        symmetrical.clear();

        int n; cin >> n;
        vector<vector<int>> graph(n);
        for (int i = 0; i < n-1; ++i) {
            int u, v; cin >> u >> v;
            --u; --v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        cout << (symmetrical[dfs(0, 0, graph)] ? "YES\n" : "NO\n");
    }

    return 0;
}