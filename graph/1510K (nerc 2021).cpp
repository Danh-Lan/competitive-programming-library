/*
idea : 
- if n even : 
	(a1, a2, a_n+1, a_n+2) form a cycle so the value has to be 1,2,n+1,n+2
	there are 4 types : 1 2 n+1 n+2, 2 1 n+2, n+1, n+1 n+2 1 2, n+2 n+1 2 1
	all cycle has to be of the same type, else --> -1
	if type1 : 0 , type2 or 3 : 1, type 4 : 2
- if n odd :
	there is a cycle in the whole graph : 1 2 n+2 n+3 3 4 n+4 n+5 5 6... n n+1
	for each a[i] count the number of operation need to be in the right place 
	all number has to be equal, else --> -1
	(intuitive : use the same operation 2 times change nothing, so we have to use alternatively 1 and 2
				if some a[i] need more operation, we can see it affect other elemnt as well)
	if equal, print that number
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
    
	int t = 1;
	//cin>>t;
	for (int tt = 1; tt <= t; tt++) {
		int n; cin>>n;
		int a[2*n+1];
		for (int i = 1; i <= 2*n; ++i)
		{
			cin>>a[i];
		}

		if (n % 2 == 0) {
			int case1 = 0, case2 = 0, case3 = 0, case4 = 0;
			for (int i = 1; i <= n; i += 2)
			{
				if (a[i] == i && a[i+1] == i+1) ++case1;
				else if (a[i] == i+1 && a[i+1] == i) ++case2;
				else if (a[i] == i+n && a[i+1] == i+1+n) ++case3;
				else if (a[i] == i+1+n && a[i+1] == i+n) ++case4;
				else break;
			}
			for (int i = n+1; i <= 2*n; i += 2)
			{
				if (a[i] == i && a[i+1] == i+1) ++case1;
				else if (a[i] == i+1 && a[i+1] == i) ++case2;
				else if (a[i] == i-n && a[i+1] == i+1-n) ++case3;
				else if (a[i] == i+1-n && a[i+1] == i-n) ++case4;
				else break;
			}
			
			if (case1 == n) cout<<0<<endl;
			else if (case2 == n || case3 == n) cout<<1<<endl;
			else if (case4 == n) cout<<2<<endl;
			else cout<<-1<<endl;

		} else {
			map<int, int> cycle;
			int cur = 1;
			bool back = false;
			int cnt = 0;
			//int breakloop = 0;
			// 1 2 5 6 3 4 1 2
			while (cnt < 2*n) {
				//++breakloop; if (breakloop > 1200) break;
				cycle[cur] = cnt;
				cycle[cur+1] = cnt+1;
				if (back == false) cur = cur+1+n;
				else cur = cur+1-n;
				cnt += 2;
				back = !back;
			}

			int distance[2*n+1];
			for (int i = 1; i <= 2*n; ++i)
			{
				int dist = abs(cycle[a[i]]-cycle[i]);
				if (dist > n) dist = 2*n-dist;
				distance[i] = dist;
			}

			bool flag = true;
			for (int i = 1; i < 2*n; ++i)
			{
				if (distance[i] != distance[i+1]) {
					flag = false;
					break;
				}
			}

			if (flag == false) cout<<-1<<endl;
			else cout<<distance[1]<<endl;
		}
	}

	return 0;
}