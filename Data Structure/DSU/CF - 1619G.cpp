#include <bits/stdc++.h>

using namespace std;

struct DSU {
    vector<int> par, ranks, time;
    DSU(int n, vector<int>& ti) : par(n + 1), ranks(n + 1, 0), time(n + 1) {
        for (int i = 1; i <= n; ++i) par[i] = i;
        for (int i = 1; i <= n; ++i) time[i] = ti[i];
    }
    int find(int i) {
        return (par[i] == i ? i : (par[i] = find(par[i])));
    }
    int get_time(int i) {
        return time[i];
    }
    int merge(int i, int j) {
        if ((i = find(i)) == (j = find(j))) return -1;
        if (ranks[i] > ranks[j]) swap(i, j);
        par[i] = j;
        time[j] = min(time[i], time[j]);
        if (ranks[i] == ranks[j]) ranks[j]++;
        return j;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif 
    
    int tt = 1; 
    cin>>tt;
    for (int test = 1; test <= tt; test++) {
        int n, k; cin>>n>>k;
        tuple<int,int,int,int> a[n];
        for (int i = 0; i < n; ++i)
        {
            cin>>get<0>(a[i])>>get<1>(a[i])>>get<2>(a[i]);
            get<3>(a[i]) = i+1;
        }
        vector<int> time(n+1);
        for (int i = 1; i <= n; ++i)
        {
            time[i] = get<2>(a[i-1]);
        }

        DSU dsu(n, time);
        sort(a, a+n);
        for (int i = 1; i < n; ++i)
        {
            if (get<0>(a[i]) == get<0>(a[i-1]) && get<1>(a[i])-get<1>(a[i-1]) <= k) {
                dsu.merge(get<3>(a[i]), get<3>(a[i-1]));
            }
        }

        sort(a, a+n, [&] (tuple<int,int,int,int> tx, tuple<int,int,int,int> ty) {
            if (get<1>(tx) == get<1>(ty)) return (get<0>(tx) < get<0>(ty));
            return (get<1>(tx) < get<1>(ty));
        });
        for (int i = 1; i < n; ++i)
        {
            if (get<1>(a[i]) == get<1>(a[i-1]) && get<0>(a[i])-get<0>(a[i-1]) <= k) {
                dsu.merge(get<3>(a[i]), get<3>(a[i-1]));
            }
        }

        vector<int> con; // time to detonate each connected component
        for (int i = 0; i < n; ++i)
        {
            if (dsu.find(get<3>(a[i])) == get<3>(a[i])) {
                con.push_back(dsu.get_time(get<3>(a[i])));
            }
        }

        sort(con.begin(), con.end());
        if (con[0] >= con.size()) {
            cout<<con.size()-1<<'\n';
            continue;
        }

        int sz = con.size();
        int l = 0, r = min(sz-1, con[sz-1]);
        int ans = r;
        while (l < r) {
            int m = (l+r)/2;
            int idx = upper_bound(con.begin(), con.end(), m) - con.begin();
            idx--;
            if (m+1 >= con.size()-1-idx) {
                r = m;
                ans = min(ans, m);
            } else {
                l = m+1;
            }
        }

        cout<<ans<<'\n';
    }

    return 0;
}