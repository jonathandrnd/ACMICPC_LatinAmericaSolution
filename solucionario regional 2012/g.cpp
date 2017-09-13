#include <ctime>
#include <numeric>
#include <functional>
#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
#include <string>
#include <cstring>
#include <climits>
#include <cmath>
#include <cctype>
#include <sstream>
#include <map>
#include <set>
#include <cstdio>
#include <queue>
using namespace std;
#define MAXN 5001
#define INF (1<<28)
  
vector <int> adj[MAXN + 1]; // (u, v) <=> (v, u)
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

int win=0;
char grid[51][51];
bool visited[51][51];
int di[4]={-1,1,0,0};
int dj[4]={0,0,1,-1};
int cantdos,cantuno;

void colorear(int i,int j,int val){
    if(val==1)cantuno++;
    if(val==2)cantdos++;
    visited[i][j]=1;
    
    for(int k=0;k<4;k++){
        int X=i+di[k];
        int Y=j+dj[k];
        if(X>=0 && X<R && Y>=0 && Y<C){
            if(!visited[X][Y] && grid[X][Y]=='.'){
                if(val==1){
                    adj[i*C+j].push_back(X*C+Y+m);
                }else{
                    adj[X*C+Y].push_back(i*C+j+m);   
                }
            }    
        }
    }
    
    
    for(int k=0;k<4;k++){
        int X=i+di[k];
        int Y=j+dj[k];
        if(X>=0 && X<R && Y>=0 && Y<C){
            if(!visited[X][Y] && grid[X][Y]=='.'){
                if(val==1){
                    colorear(X,Y,2);    
                }else{
                    colorear(X,Y,1);        
                }
            }    
        }
    }
           
    return ;
}


int main(){
    
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    
    while(cin>>R>>C){
        
        for(int i=0;i<R;i++)
            scanf("%s",grid[i]);
        
        memset(visited,0,sizeof(visited));
        win=2;
        n=R*C;
        m=R*C;
        
        for(int i=0;i<R;i++)
            for(int j=0;j<C;j++){
                if(grid[i][j]=='X')continue;
                if(visited[i][j])continue;
                for(int k=0;k<R*C;k++)
                    if(adj[k].size()!=0)
                        adj[k].clear();
                cantdos=0;
                cantuno=0;
                colorear(i,j,1);  
                
                
                if( !(cantuno==cantdos && hopcroft_karp()==cantuno)){
                    win=1;
                    goto next;
                }
                
                
            }
            
        next:
        cout<<win<<endl;
    }
    
    return 0;    
}
