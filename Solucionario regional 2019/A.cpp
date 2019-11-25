#include <iostream>
#include <cstring>
#include <cmath>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
using namespace std;
#define MAXN 204805
#define INF (1<<28)
vector <int> adj[MAXN + 1]; // (u, v) <=> (v, u)
map<vector<int>,int>encode;
int n, m, NIL, match[MAXN + 1], dist[MAXN + 1];
// Izquierda; nodos del 0 al n-1
// Derecha: Nodos del n al n+m-1
// NIL: Nodo n+m

int R,C;  
  
bool bfs(){
    queue <int> Q;
    for(int i=0; i<n; i++) {
        if(match[i] == NIL) {
            dist[i] = 0;
            Q.push(i);
        }
        else dist[i] = INF;
    }
    dist[NIL] = INF;
      
    while(!Q.empty()) {
        int u = Q.front(); Q.pop();
        for(int i=0; i<adj[u].size(); i++){
            int v = adj[u][i];
            if(dist[match[v]] == INF) {
                dist[match[v]] = dist[u] + 1;
                Q.push(match[v]);
            }
        }
    }
    return dist[NIL] != INF;
}
  
bool dfs(int u) {
    if(u != NIL) {
        for(int i=0; i<adj[u].size(); i++) {
            int v = adj[u][i];
            if(dist[match[v]] == dist[u] + 1) {
                if(dfs(match[v])) {
                    
                    match[v] = u;
                    match[u] = v;
                    return true;
                }
            }
        }
        dist[u] = INF;
        return false;
    }
    return true;
}
  
int hopcroft_karp(){
    NIL = n + m;
    for(int i=0; i<n+m; i++)
        match[i] = NIL;
      
    int matching = 0;
      
    //Greedy Step
    for(int u=0; u<n; u++){
        for(int i=0; i<adj[u].size(); i++){
            int v = adj[u][i];
            if(match[v] == NIL){
                matching++;
                match[u] = v;
                match[v] = u;
                break;
            }
        }
    }
      
    while(bfs())
        for(int u=0; u<n; u++)
            if(match[u] == NIL && dfs(u))
                matching++;
    
    return matching;
}


//Solution
// Direct application of Maximal antichain
// Dilworth's Theorem
// Bipartite matching, hopcroft karp
//read https://codeforces.com/blog/entry/3781

//Practice with https://www.spoj.com/problems/DIVREL/

int main() {
	int N;
	
	while(cin>>N){
		for(int i=0;i<MAXN;i++)
            if(adj[i].size()>0)
                adj[i].clear();
        
		encode.clear();        
		        
		map<string,int>name;
		vector<int>v[N];
		int cnt = 0;
		
		int sum = 0;
		
		for(int i = 0;i < N; i++){
			int t;
			cin>>t;
			for(int j = 0;j < t;j++){
				string aux;
				cin >> aux;
				if(name.find(aux) == name.end())
					name[aux] = cnt++;
				v[i].push_back(name[aux]);
			}
			
			sum += (1<<t);
			sort(v[i].begin(),v[i].end());
		}
		
		cnt = 0;
		n = sum;
		
		for(int i = 0; i < N;i++){
			int t = v[i].size();
			//cout<<"i "<<i<<" "<<t<<endl;
			for(int mask = 1; mask < (1<<t);mask++){
				int ones = __builtin_popcount(mask);
				vector<int>aux;
				for(int j =0;j < t;j++)
					if( (mask&(1<<j)) != 0)
						aux.push_back(v[i][j]);
				
				if(encode.find(aux)==encode.end())
					encode[aux] = cnt++;			
				
				int t2 = aux.size();
				
				for(int mask2 = 1; mask2<(1<<t2);mask2++){
					int ones2 = __builtin_popcount(mask2);
					if(ones2+1 == ones){
						vector<int>aux2;
						for(int j =0;j < t2;j++)
							if( (mask2&(1<<j)) != 0)
								aux2.push_back(aux[j]);
						if(encode.find(aux2) == encode.end())
							encode[aux2] = cnt++;
						
						// UNION encode[aux] ->encode[aux2]
						adj[encode[aux]].push_back(n+encode[aux2]);
					}
				}
			}
		}
		
		m= sum;        
		cout<<(int)encode.size()-hopcroft_karp()<<endl;
	}
	
		
	return 0;
}
