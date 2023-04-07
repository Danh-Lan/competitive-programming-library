/*
We have a bunch of interval [l, r]. 
We want to calculate the number of apperance of each number in
these intervals
The trick is for each [l, r], we add 1 to a[l] and substract 1 to a[r+1],
then calculate the prefix sum 
*/

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
        int n, m; cin>>n>>m;
        string s[n];
        vector<vector<int>> hor(n, vector<int>()), ver(m, vector<int>());
        for (int i = 0; i < n; ++i) {
            hor[i].push_back(-1);
        }
        for (int i = 0; i < m; ++i) {
            ver[i].push_back(-1);
        }
        for (int i = 0; i < n; ++i) {
            cin>>s[i];
            for (int j = 0; j < m; ++j) {
                if (s[i][j] == '.') {
                    hor[i].push_back(j);
                    ver[j].push_back(i);
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            hor[i].push_back(m);
        }
        for (int i = 0; i < m; ++i) {
            ver[i].push_back(n);
        }

        vector<tuple<int,int,int>> ans;
        vector<vector<int>> cntHor(n, vector<int>(m, 0)), cntVer(n, vector<int>(m, 0));
        for (int i = 1; i < n-1; ++i) {
            for (int j = 1; j < m-1; ++j) {
                if (s[i][j] == '*') {
                    int hL = *prev(lower_bound(hor[i].begin(), hor[i].end(), j)) + 1;
                    int hR = *upper_bound(hor[i].begin(), hor[i].end(), j) - 1;
                    int vU = *prev(lower_bound(ver[j].begin(), ver[j].end(), i)) + 1;
                    int vD = *upper_bound(ver[j].begin(), ver[j].end(), i) - 1;
                    int leng = min(min(i-vU, vD-i), min(j-hL, hR-j));
                    
                    if (leng > 0) {
                        ans.push_back({i, j, leng});
                        cntHor[i][j-leng]++;
                        if (j+leng+1 < m) cntHor[i][j+leng+1]--;
                        cntVer[i-leng][j]++;
                        if (i+leng+1 < n) cntVer[i+leng+1][j]--;
                    }
                }
            }
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (j >= 1 && cntHor[i][j-1] > 0) cntHor[i][j] += cntHor[i][j-1];
                if (i >= 1 && cntVer[i-1][j] > 0) cntVer[i][j] += cntVer[i-1][j];
            }
        }

        bool flag = true;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if ((s[i][j] == '*' && cntHor[i][j] <= 0 && cntVer[i][j] <= 0) || (s[i][j] == '.' && (cntHor[i][j] > 0 || cntVer[i][j] > 0))) {
                    flag = false;
                    break;
                }
            }
            if (!flag) break;
        }

        if (!flag) cout<<-1<<"\n";
        else {
            cout<<ans.size()<<"\n";
            for (int i = 0; i < ans.size(); ++i) {
                cout<<get<0>(ans[i])+1<<" "<<get<1>(ans[i])+1<<" "<<get<2>(ans[i])<<"\n";
            }
        }
    }

    return 0;
}