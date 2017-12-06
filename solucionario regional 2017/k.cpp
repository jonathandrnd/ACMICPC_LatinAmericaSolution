#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<cmath>
#include<sstream>
#include<algorithm>
#include<set>
#include<queue>
#define EPS 1e-8
using namespace std;
int R,C;
char c[21][21];

#define MAXN 1001
#define INF (1<<28)
  
vector <int> adj[MAXN + 1]; // (u, v) <=> (v, u)
int n, m, NIL, match[MAXN + 1], dist[MAXN + 1];
// Izquierda; nodos del 0 al n-1
// Derecha: Nodos del n al n+m-1
// NIL: Nodo n+m

  
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


int node[21][21];
int size[21][21];

int main(){
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	
	while(cin>>R>>C){
		for(int i=0;i<MAXN;i++)adj[i].clear();
		int o=0;
		
		
		for(int i=0;i<R;i++)
			for(int j=0;j<C;j++){
				cin>>c[i][j];
				if(c[i][j]=='o')o++;
			}
		
		if(o%2==1){
			cout<<"N"<<endl;
			continue;
		}
		
		n=0;
		int lasteven=0;
		int lastodd=0;
				
		for(int i=0;i<R;i++)
			for(int j=0;j<C;j++){
				if( (i+j)%2==0 ){
					if(c[i][j]=='o'){
						node[i][j]=lasteven+1;
						size[i][j]=1;
					}else{
						node[i][j]=lasteven+2;
						size[i][j]=2;
					}
					lasteven=node[i][j];
				}else{
					if(c[i][j]=='o'){
						node[i][j]=lastodd+1;
						size[i][j]=1;
					}else{
						node[i][j]=lastodd+2;
						size[i][j]=2;
					}
					lastodd=node[i][j];
				}
				
			}
		
		n=lasteven;
		m=lastodd;
		NIL=n+m;
		
		int di[4]={-1,1,0,0};
		int dj[4]={0,0,1,-1};
		
		for(int i=0;i<R;i++)
			for(int j=0;j<C;j++){
				if( (i+j)%2==1)continue;
				
				//4 directions
				for(int k=0;k<4;k++){
					int x=i+di[k];
					int y=j+dj[k];
					if(x>=0 && x<R &&y>=0 && y<C){
						int start1=node[i][j]-size[i][j];
						int end1=node[i][j];
						
						int start2=node[x][y]-size[x][y];
						int end2=node[x][y];
						
						for(int ii=start1;ii<end1;ii++)
							for(int jj=start2;jj<end2;jj++)
								adj[ii].push_back(n+jj);
					}
				}
				
			}
		
		if(hopcroft_karp()==NIL/2){
			cout<<"Y"<<endl;
		}else{
			cout<<"N"<<endl;
		}
		
	}
	
			
	return 0;
}


