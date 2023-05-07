#include <bits/stdc++.h>
 
using namespace std;

int n, day[200001];
vector<int> visit;
vector<vector<int>> v;

bool dfs(int i) {
	visit[i] = 1;
	day[i] = 1;
	for (auto j : v[i]) {
		if (visit[j] == 0) dfs(j);
		if (visit[j] == 1) return false;
		if (j < i) day[i] = max(day[i], day[j]);
		else day[i] = max(day[i], day[j]+1);
	}
	visit[i] = 2;
	return true;
}

void solve() {
	visit.assign(n+1,0);
	for (int i = 1; i <= n; ++i)
	{
		if (visit[i] == 0) {
			bool ok = dfs(i);
			if (!ok) {
				cout<<-1<<endl;
				return;
			}
		}
	}
	cout<<*max_element(day+1, day+n+1)<<endl;
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif 
    
	int t = 1;
	cin>>t;
	for (int tt = 1; tt <= t; tt++) {
		cin>>n;
		v.assign(n+1,{});
		for (int i = 1; i <= n; ++i)
		{
			int k; cin>>k;
			for (int j = 1; j <= k; ++j)
			{
				int l; cin>>l;
				v[i].push_back(l);
			}
		}
		solve();
	}

	return 0;
}