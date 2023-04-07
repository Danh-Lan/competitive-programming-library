#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    int tt = 1; 
    //cin>>tt;
    for (int test = 1; test <= tt; test++) {
        int n, v; cin>>n>>v;
        long long t[n], pos[n];
        for (int i = 0; i < n; ++i) {
            cin>>t[i];
        }
        for (int i = 0; i < n; ++i) {
            cin>>pos[i];
        }

        vector<pair<long long, long long>> kick;
        for (int i = 0; i < n; ++i) {
            if (1LL*t[i]*v >= labs(pos[i])) {
                kick.push_back({1LL*t[i]*v-pos[i], 1LL*t[i]*v+pos[i]});
            }
        }

        sort(kick.begin(), kick.end());

        n = kick.size();
        vector<long long> lis;
        for (int i = 0; i < n; ++i) {
            if (lis.empty() || lis.back() <= kick[i].second) {
                // if strict increasing : replace <= by <
                lis.push_back(kick[i].second);
            } else {
                int idx = upper_bound(lis.begin(), lis.end(), kick[i].second) - lis.begin();
                lis[idx] = kick[i].second;
            }
        }

        cout<<lis.size()<<"\n";
    }

    return 0;
}

// SWERC 2022 L