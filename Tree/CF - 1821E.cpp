#include<bits/stdc++.h>
 
using namespace std;

long long dfs(map<int, vector<int>>& trees, vector<long long>& val, int u, int p = -1) {
    long long res = (long long)trees[u].size();
    for (int v : trees[u]) {
        if (v == p) continue;

        res += dfs(trees, val, v, u);
    }

    val[u] = res;
    return res;
}

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
        int k;
        cin >> k;

        string s;
        cin >> s;

        map<int, vector<int>> trees;
        vector<int> sources;
        
        stack<int> st;
        int n = s.length();
        int cur = 0;
        for (int i = 0; i < n; ++i) {
            if (s[i] == '(') {
                if (cur == 0) {
                    sources.push_back(i);
                }
                if (!st.empty()) {
                    trees[st.top()].push_back(i);
                }
                st.push(i);
                cur++;
            } else {
                st.pop();
                cur--;
            }
        }

        vector<long long> val(n, 0);
        for (int src : sources) {
            dfs(trees, val, src);
        }

        long long cnt = accumulate(val.begin(), val.end(), 0LL);
        sort(val.begin(), val.end(), greater<int>());
        for (int i = 0; i < min(n/2, k); ++i) {
            cnt -= val[i];
        }

        cout << cnt << '\n';
    }

    return 0;
}