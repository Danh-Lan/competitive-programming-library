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
    //cin>>test;
    for (int tt = 0; tt < test; ++tt)
    {
        int n, w, h; cin>>n>>w>>h;
        vector<pair<int, int>> env;
        map<pair<int,int>, int> pos;
        for (int i = 0; i < n; ++i)
        {
            int width, height; cin>>width>>height;
            if (width > w && height > h) {
                env.push_back({width, height});
                pos.insert({{width, height}, i+1});
            }
        }

        if (env.empty()) cout<<0<<endl;
        else {
            sort(env.begin(), env.end(), 
                [&] (pair<int,int> p1, pair<int,int> p2) {
                    if (p1.first == p2.first) return (p1.second < p2.second);
                    return (p1.first < p2.first);
                }
            );

            vector<int> dp(env.size(), 1);
            for (int i = 0; i < env.size()-1; ++i)
            {
                for (int j = i+1; j < env.size(); ++j)
                {
                    if (env[j].first > env[i].first && env[j].second > env[i].second) {
                        dp[j] = max(dp[j], dp[i]+1);
                    }
                }
            }

            vector<int> ans;
            pair<int, int> curPair;
            int mx = *max_element(dp.begin(), dp.end()); 
            for (int i = env.size()-1; i >= 0 ; --i)
            {
                if (dp[i] == mx) {
                    if (!ans.empty()) {
                        if (env[i].first < curPair.first && env[i].second < curPair.second) {
                            ans.push_back(pos[{env[i].first, env[i].second}]);
                            mx--;
                            curPair = {env[i].first, env[i].second};
                        }
                    } else {
                        curPair = {env[i].first, env[i].second};
                        ans.push_back(pos[{env[i].first, env[i].second}]);
                        mx--;
                    }
                }
            }

            reverse(ans.begin(), ans.end());
            cout<<ans.size()<<endl;
            for (int i = 0; i < ans.size(); ++i)
            {
                cout<<ans[i]<<" ";
            } cout<<endl;
        }
    }

    return 0;
}