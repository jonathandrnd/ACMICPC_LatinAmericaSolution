#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<sstream>
#include<set>
#include<cstring>
#include<vector>
#include<map>
#include<cassert>
#include<cmath>
#include<queue>
#define N 201
using namespace std;
int n;
int match[ N + 5 ];
bool vis[ N + 5 ];
vector<int> G[ N + 5 ];
vector<int>v[N+5];

int dfs( int u ){
	if( vis[ u ] ) return 0;
	vis[ u ] = 1;
	for(int i=0;i<G[u].size();i++  /*auto v : G[ u ]*/ ){
        int v=G[u][i];
        if( match[v] == -1 || dfs(match[v] ) ){
			match[v] = u;
			return 1;
		}
	}
	return 0;
}


int main(){

//freopen("in.txt","r",stdin);
//freopen("out.txt","w",stdout);

    int q;
    while(cin>>n>>q){
        for(int i=0;i<205;i++)v[i].clear();
        bool todo=0;
        for(int i=0;i<n;i++){
            int t,aux;
            cin>>t;
            if(t==n)todo=1;
            for(int j=0;j<t;j++){
                cin>>aux;
                aux--;
                v[i].push_back(aux);
            }
        }
        
        while(q--){
            for(int i=0;i<205;i++)G[i].clear();
            memset(match,-1,sizeof(match));

            int t;
            cin>>t;
            if(t==0){
                if(todo)
                    cout<<"N"<<endl;
                else
                    cout<<"Y"<<endl;
                continue;
            }
            
            int aux;
            bool visited[n];
            memset(visited,0,sizeof(visited));
            for(int i=0;i<t;i++){
                cin>>aux;
                aux--;
                visited[aux]=1;
            }
            
           
            for(int i=0;i<n;i++){
                for(int j=0;j<v[i].size();j++){
                    if(visited[ v[i][j] ]){
                        G[i].push_back(n+v[i][j]);
                        //cap[i+1][n+1+v[i][j]]=1;
                    }
                }
            }

            int dev=0;
            for(int i=0;i<2*n;i++){
                memset(vis,0,sizeof(vis));
                dev+=dfs(i);
            }
            
            //for(int i=0;i<n;i++)cap[0][i+1]=1;
            //for(int i=0;i<n;i++)cap[n+1+i][size]=1;
            ///cout<<maxflow( 0, size )<<endl;
            if( dev== t )
                cout<<"Y"<<endl;
            else
                cout<<"N"<<endl;
            
        }
        
    }


    return 0;
}


