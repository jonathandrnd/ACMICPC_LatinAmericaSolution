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
vector<int>v1[40001],v2[40001];
int dis1[40001];
int dis2[40001];
int visited[40001];

pair<int,int>diametro(vector<int>v[40001]){
    memset(visited,0,sizeof(visited));
    queue<int>Q;
    Q.push(0);
    int ini=0;
    
    while(!Q.empty()){
        ini=Q.front();
        Q.pop();
        visited[ini]=1;
        
        for(int i=0;i<v[ini].size();i++){
            if(!visited[v[ini][i]]){
                Q.push(v[ini][i]);    
            }        
        }
        
    }
    
    int fin=ini;
    while(!Q.empty())Q.pop();
 
    Q.push(ini);
    memset(visited,0,sizeof(visited));
    
    while(!Q.empty()){
        fin=Q.front();
        Q.pop();
        visited[fin]=1;
        
        for(int i=0;i<v[fin].size();i++){
            if(!visited[v[fin][i]]){
                Q.push(v[fin][i]);    
            }        
        }
        
    }
    
    return make_pair(ini,fin);
}

void llenar1(int node){
    queue<int>Q;
    Q.push(node);
    memset(visited,-1,sizeof(visited));    
    visited[node]=0;
    
    while(!Q.empty()){
        int nodo=Q.front();
        dis1[nodo]=max(dis1[nodo],visited[nodo]);
        Q.pop();
        for(int i=0;i<v1[nodo].size();i++)
            if(visited[v1[nodo][i]]==-1){
                Q.push(v1[nodo][i]);    
                visited[v1[nodo][i]]=visited[nodo]+1;
            }  
    }
}

void llenar2(int node){
    queue<int>Q;
    Q.push(node);
    memset(visited,-1,sizeof(visited));    
    visited[node]=0;
    
    while(!Q.empty()){
        int nodo=Q.front();
        dis2[nodo]=max(dis2[nodo],visited[nodo]);
        Q.pop();
        for(int i=0;i<v2[nodo].size();i++)
            if(visited[v2[nodo][i]]==-1){
                Q.push(v2[nodo][i]);    
                visited[v2[nodo][i]]=visited[nodo]+1;
            }  
    }
}




void bfs(){
    memset(dis1,0,sizeof(dis1));
    memset(dis2,0,sizeof(dis2));
    
    pair<int,int>d1=diametro(v1);
    pair<int,int>d2=diametro(v2);
        
    //cout<<"diametro "<<d1.first<<" "<<d1.second<<" "<<d2.first<<" "<<d2.second<<endl;     
    
    llenar1(d1.first);
    llenar1(d1.second);
    
    llenar2(d2.first);
    llenar2(d2.second);
}

long long F[40001];
int main(){
    
    
    int n,q;
    
    while(cin>>n>>q){
        
        for(int i=0;i<40001;i++){v1[i].clear();v2[i].clear();}
        
        for(int i=0;i<n-1;i++){
            int a,b;
            scanf("%d %d",&a,&b);
            a--;
            b--;
            v1[a].push_back(b);  
            v1[b].push_back(a);  
        }
        
        for(int i=0;i<q-1;i++){
            int a,b;
            scanf("%d %d",&a,&b);
            a--;
            b--;
            v2[a].push_back(b);
            v2[b].push_back(a);    
        }
        
        
        bfs();
        long long sum1=0;long long sum2=0;
        long long dev=0;
        int maxi=0;
        
        for(int i=0;i<n;i++){sum1+=dis1[i];maxi=max(maxi,dis1[i]);}
        sort(dis2,dis2+q);
        
        for(int i=0;i<q;i++){sum2+=dis2[i];maxi=max(maxi,dis2[i]);}
        
        
        for(int i=q-1;i>=0;i--){
            if(i==q-1)F[i]=dis2[i];
            else F[i]=dis2[i]+F[i+1];
            
        }
        
        for(int i=0;i<n;i++){
            
            //for(int j=0;j<q;j++)
            //    dev+=max(maxi,dis1[i]+dis2[j]+1);
            
            
            int id=lower_bound(dis2,dis2+q,maxi-(dis1[i]+1))-dis2;
            dev+=(long long)maxi*id;
            if(id<q)dev+=F[id]+(dis1[i]+1)*(long long)(q-id);  
            
        }
        
        
        printf("%.3lf\n",(double)dev/((long long)n*q));
    }
    
    return 0;
}
