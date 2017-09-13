#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string.h>
#include <stdio.h>
#define all(v) (v).begin(),(v).end()
#define rall(v) (v).rbegin(),(v).rend()
using namespace std;  // H A M L E T
#define MAXN 10001
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

int main(){
    
    int tam;
    while(cin>>tam){
        for(int i=0;i<MAXN;i++)
            if(adj[i].size()>0)
                adj[i].clear();
        
        char c[tam][tam];
        
        for(int i=0;i<tam;i++)
            for(int j=0;j<tam;j++)
                cin>>c[i][j];
        
        n=0;m=0;
        int Filas[tam][tam];
        int Columnas[tam][tam];
        memset(Filas,-1,sizeof(Filas));
        memset(Columnas,-1,sizeof(Columnas));
        
        for(int i=0;i<tam;i++)
            for(int j=0;j<tam;j++)
                if(c[i][j]=='.'){
                    while(j<tam && c[i][j]=='.'){
                        Filas[i][j]=n;
                        j++;    
                    }
                    n++;
                }
        
        bool visited[tam][tam];
        memset(visited,0,sizeof(visited));
        
        for(int i=0;i<tam;i++)
            for(int j=0;j<tam;j++)
                if(c[i][j]=='.' && !visited[i][j]){
                    int id=i;
                    while(id<tam && c[id][j]=='.'){
                        Columnas[id][j]=m;
                        visited[id][j]=1;
                        id++;    
                    }
                    m++;
                }
        
        for(int i=0;i<tam;i++)
            for(int j=0;j<tam;j++){
                if(c[i][j]=='.'){
                    adj[Filas[i][j]].push_back(n+Columnas[i][j]);
                }    
            }
        
        cout<<hopcroft_karp()<<endl;
    }
    
    
    return 0;
}
