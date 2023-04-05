// https://codeforces.com/contest/1492/problem/C

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
	while (t--) {
		int n, m;
		cin>>n>>m;
		
		string s, t;
		cin>>s>>t;

		int left[t.length()], right[t.length()];
		int lastL = -1, lastR = s.length();
		for (int i = 0; i < t.length(); ++i)
		{
			lastL = find(s.begin()+lastL+1,s.end(), t[i])-s.begin();
			left[i] = lastL;
		}
		
		for (int i = t.length()-1; i >= 0; --i)
		{
			for (int j = lastR-1; j >= 0; --j) {
				if (s[j] == t[i])
				{
					right[i] = j;
					lastR = j;
					break;
				}
			}
		}

		int res = 0;
		for (int i = 0; i < t.length()-1; ++i)
		{
			res = max(res, right[i+1]-left[i]);			
		}
		cout<<res<<endl;
	}


	return 0;
}