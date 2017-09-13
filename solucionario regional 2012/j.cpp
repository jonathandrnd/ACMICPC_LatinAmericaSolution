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
#define MAX 100005
int uf[MAX];
int FIND(int x){ return uf[x]==x? x:uf[x] = FIND(uf[x]); }
void UNION(int x,int y){ uf[FIND(x)] = FIND(y); }

int n;
int p[100001];
int P[100001][17];
int L[100001];
int val[100001];

int pciclo[100001];
int Pciclo[100001];
int   papi[100001];

bool visited[100001];
vector<int>v[100001];
int tamciclo[100001];

void getArbol(int node,int nivel){
    visited[node]=1;
    L[node]=nivel;
    
    for(int i=0;i<v[node].size();i++){
        int t=v[node][i];
        if(!visited[t]){
            if(pciclo[t]!=-1){
                getArbol(t,nivel);
            }else{
                papi[t]=node;
                getArbol(t,nivel+1);
            }         
        }    
    }
    
    return ;
}

void init(){
    for(int i=0;i<n;i++)
        if(pciclo[i]!=-1)P[i][0]=-1;
        else P[i][0]=papi[i];
    
    for(int i=1;(1<<i)<=n;i++)
        for(int j=0;j<n;j++)
            if(P[j][i-1]!=-1)
                P[j][i]=P[P[j][i-1]][i-1];        
}

pair<int,int> lca(int a,int b){
    if(a==b)return make_pair(a,b);
    if(L[a]<L[b])swap(a,b);
    
    int dif=L[a]-L[b];
    
    for(int i=16;i>=0;i--){
        if(dif>=(1<<i)){
            dif-=1<<i;
            a=P[a][i];
        }
    }
    
    if(a==b || L[a]==0)return make_pair(a,b);
    
    for(int i=16;i>=0;i--){
        if(P[a][i] != P[b][i] && L[P[a][i]]!=0){
            a=P[a][i];
            b=P[b][i];
        }
    }
    
    return make_pair(papi[a],papi[b]);
}

int main(){
    
    //freopen("input.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    
    while(cin>>n){
        memset(p,-1,sizeof(p));
        memset(P,-1,sizeof(P));
        memset(pciclo,-1,sizeof(pciclo));
        memset(papi,-1,sizeof(papi));
        memset(visited,0,sizeof(visited));
        memset(L,0,sizeof(L));
        memset(tamciclo,0,sizeof(tamciclo));
        memset(val,0,sizeof(val));
        
        int u;
        for(int i=0;i<n;i++)uf[i]=i;
        for(int i=0;i<n;i++)v[i].clear();
        
        for(int i=0;i<n;i++){
            scanf("%d",&u);  
            u--;
            if(FIND(i)==FIND(u)){
                int aux=i;
                int tam=0;
                p[i]=u;
                
                while(true){
                    tam++;
                    visited[aux]=1;
                    pciclo[aux]=p[aux];
                    aux=p[aux];
                    if(visited[aux])break;    
                }
                
                int aux2=i;
            
                for(int j=1;;j++){
                    val[aux2]=j;
                    tamciclo[aux2]=tam;
                    aux2=p[aux2];
                    if(aux2==aux)break;    
                }
            }
            
            UNION(i,u);
            p[i]=u;
            v[i].push_back(u);
            v[u].push_back(i);
        }
        
        int q;
        cin>>q;
        memset(visited,0,sizeof(visited));
        
        for(int i=0;i<n;i++)
            if(pciclo[i]!=-1 && !visited[i])
                getArbol(i,0);
        
        
        for(int i=0;i<n;i++)
            if(!visited[i])
                getArbol(i,0);
        
        init();
        
        for(int i=0;i<q;i++){
            int a,b;
            scanf("%d %d",&a,&b);
            a--;b--;
            if(FIND(a)!=FIND(b) ){
                printf("-1\n");    
            }else{
                pair<int,int> node=lca(a,b);
                
                if(node.first==node.second)
                    printf("%d\n",L[a]-L[node.first]+L[b]-L[node.first] );
                else{
                    int dif=abs(val[node.first]-val[node.second]);
                    printf("%d\n",L[a]+L[b]+ min( tamciclo[node.first]-dif,dif) );
                }
            }
        }    
        
    }
    
    return 0;    
}
