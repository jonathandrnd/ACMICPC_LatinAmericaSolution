#include<iostream>
#include<cstring>
#include<map>
#include<cstdio>
#include<vector>
#include<cmath>
#include<sstream>
#include<algorithm>
#include<set>
#include<queue>
#define MOD 1000000007LL
#define MAX 100005
using namespace std;

int uf[MAX];
int FIND(int x){ return uf[x]==x? x:uf[x] = FIND(uf[x]); }
void UNION(int x,int y){ uf[FIND(x)] = FIND(y); }

struct node{
	int u,v,d;
	
	node(int _u,int _v,int _d){
		u=_u;v=_v;d=_d;
	}
	
	node(){}	
};

bool operator<(node a,node b){
	if(a.d!=b.d)return a.d<b.d;
	if(a.u!=b.u)return a.u<b.u;
	return a.v<b.v;
}

int n,e;//nodes and edges
vector<pair<int,int> >adj[100005];

int papi[100005];
bool visited[100005];
int L[100005];
int M[100005];
int Maximo[100005][18];
int P[100005][18];

void getArbol(int node,int niv){
    visited[node]=1;
    L[node]=niv;
    
    for(int i=0;i<adj[node].size();i++){
        if(!visited[adj[node][i].first]){
        	M[adj[node][i].first]=adj[node][i].second;
            papi[adj[node][i].first]=node;
            getArbol(adj[node][i].first,niv+1);     
        }
    }
}

void getPapi(){
    memset(P,-1,sizeof(P));
    //memset(Maximo,-1,sizeof(Maximo));
    
	for(int i=0;i<n;i++)P[i][0]=papi[i];
    for(int i=0;i<n;i++)Maximo[i][0]=M[i];
    
    
    for(int j=1;(1<<j)<n;j++)
        for(int i=1;i<n;i++)
            if(P[i][j-1]!=-1){
                P[i][j]=P[P[i][j-1]][j-1];		
				Maximo[i][j]=max(Maximo[i][j-1],  Maximo[P[i][j-1]][j-1]);
			}	
    return ;      
}

int LCA(int a,int b){
    if(L[a]<L[b])swap(a,b);
    
    for(int i=16;i>=0;i--)
        if(L[a]-(1<<i)>=L[b] )
            a=P[a][i];    
    
    if(a==b)return b;
    
    for(int i=16;i>=0;i--)
        if(P[a][i]!= P[b][i]){
            a=P[a][i];
            b=P[b][i];    
        }
    
    return papi[a];
}

int maxim(int a,int b){  //L[b]<=L[a]
	int dif=L[a]-L[b];
	int dev=0;
	
	for(int i=16;i>=0;i--)
    	if(L[a]-L[b]>=(1<<i)){
    		dev=max(dev,Maximo[a][i]);
			a=P[a][i];
		}
	return dev;
}

int main(){
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	
	while(cin>>n>>e){
		for(int i=0;i<n;i++)if(adj[i].size()>0)adj[i].clear();
		for(int i=0;i<n;i++)uf[i]=i;
		
		vector<node>v;
		map<pair<int,int>,int>m;
		int sum=0;
		
		for(int i=0;i<e;i++){
			int a,b,d;
			scanf("%d %d %d",&a,&b,&d);
			a--;b--;
			v.push_back(node(a,b,d));
			m[make_pair(min(a,b),max(a,b))]=d;
		}
		
		sort(v.begin(),v.end());
		
		for(int i=0;i<e;i++){
			if(FIND(v[i].u)!=FIND(v[i].v)){
				UNION(v[i].u,v[i].v);
				adj[v[i].u].push_back(make_pair(v[i].v,v[i].d));
				adj[v[i].v].push_back(make_pair(v[i].u,v[i].d));
				sum+=v[i].d;
			}
		}
		
		memset(visited,0,sizeof(visited));
        memset(papi,-1,sizeof(papi));
        memset(M,0,sizeof(M));
        
        getArbol(0,0);
        getPapi();
		
		
		int q;
		scanf("%d",&q);
		
		for(int i=0;i<q;i++){
			int a,b;	
			scanf("%d %d",&a,&b);
			a--;b--;
			int x=LCA(a,b);
			int value=m[make_pair(min(a,b),max(a,b))];
			printf("%d\n" , sum+value-max( maxim(a,x),maxim(b,x) ));
		}
	}
	
	
	return 0;
}
