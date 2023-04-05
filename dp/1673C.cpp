// https://codeforces.com/contest/1673/problem/C
// idea : since the number of palindrome within condition is small, we do dp on palindrome

#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9+7;
const int N = 40000;
vector<int> palin; // 498 palindrome up to 40000
int dp[N+2][500];

void setPalin() {
	for (int i = 1; i <= N; i++) {
    	string s = to_string(i);
    	bool flag = 1;
    	for (int i = 0; i < s.length(); ++i)
    	{
    		if (s[i] != s[s.length()-1-i]) {
    			flag = 0;
    			break;
    		}
    	}
    	if (flag == 1) palin.push_back(i);
    }
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif 

    setPalin();
    int sz = palin.size();
    for (int i = 0; i < sz; ++i)
    {
    	dp[0][i] = 1;
    	dp[1][i] = 1;
    }

    for (int i = 2; i <= N; ++i)
    {
    	for (int j = 0; j < sz; ++j)
    	{
    		if (i < palin[j]) dp[i][j] = dp[i][j-1];
    		else dp[i][j] = (dp[i][j-1] + dp[i-palin[j]][j])%MOD;
    	}
    }
    
	int t = 1;
	cin>>t;
	for (int tt = 1; tt <= t; tt++) {
		int n; cin>>n;
		cout<<dp[n][sz-1]<<endl;

	}

	return 0;
}