// idea is to connect every member of a group to a phantom vertex
// the vertex must be unique for each group

#include<bits/stdc++.h>
using namespace std;

const int N = 1000043;
vector<int> g[N];

int color[N];
int siz[N];
int n, m;
int cc = 0;

int dfs(int x)
{
	if(color[x])
		return 0;
	color[x] = cc;
	int ans = (x < n ? 1 : 0);
	for(auto y : g[x])
		ans += dfs(y);
	return ans; 
}

int main()
{
	scanf("%d %d", &n, &m);
	for(int i = 0; i < m; i++)
	{
		int k;
		scanf("%d", &k);
		for(int j = 0; j < k; j++)
		{
			int x;
			scanf("%d", &x);
			--x;
			g[x].push_back(i + n);
			g[i + n].push_back(x);
		}
	}
	for(int i = 0; i < n; i++)
	{
		if(!color[i])
		{
			cc++;
			siz[cc] = dfs(i);
		}
		printf("%d ", siz[color[i]]);
	}
}