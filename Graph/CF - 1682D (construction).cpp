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
    cin>>t;
    for (int tt = 0; tt < t; ++tt)
    {
        int n; cin>>n;
        string s; cin >> s;
        int cntodd = 0;
        for (int i = 0; i < n; ++i)
        {
            cntodd += (s[i] == '1');
        }

        if (cntodd % 2 == 1 || cntodd == 0) cout<<"NO"<<endl;
        else {
            cout<<"YES"<<endl;

            int root = -1;
            for (int i = 1; i < n; ++i)
            {
                if (s[i-1] == '1') {
                    root = i;
                    break;
                }
            }

            vector<vector<int>> graph;
            int index = (root+1)%n;
            vector<int> subseg;
            while (true) {
                subseg.push_back(index);
                if (s[index] == '1') {
                    graph.push_back(subseg);
                    subseg.clear();
                }
                index = (index+1)%n;
                if (index == root) break;
            }

            for (int i = 0; i < graph.size(); ++i)
            {
                cout<<root+1<<" "<<graph[i][0]+1<<endl;
            }
            
            for (int i = 0; i < graph.size(); ++i)
            {
                for (int j = 0; j < graph[i].size()-1; ++j)
                {
                    cout<<graph[i][j]+1<<" "<<graph[i][j+1]+1<<endl;
                }
            }

        }
    }
    
    return 0;
}