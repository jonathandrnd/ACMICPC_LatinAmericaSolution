#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<cmath>
#include<queue>
#define MAX 100005
using namespace std;  

int v[MAX];
int tree[4*MAX];
int id[MAX];
int dp[MAX];

struct node{
    int L,S,C;
    node(int _L,int _S,int _C){
        L=_L;
        S=_S;
        C=_C;
    }
};

int query(int a,int b,int node,int p,int q){

    if(p<=a && b<=q)return tree[node];
    if(p>b || q<a)return 1<<30;

    int x=query(a,(a+b)/2,2*node+1,p,q);
    int y=query((a+b)/2+1,b,2*node+2,p,q);
    
    return min(x,y);
}


void update(int a, int b, int node , int ind , int val ){
    if(ind>b || ind<a)return;

    if(a==b){
	   tree[node]= val;
	   return ;
    }

    int v1 = 2*node+1;
    int v2 = 2*node+2;
    update(a,(a+b)/2 ,v1,ind, val );
    update((a+b)/2+1, b, v2, ind , val );

    tree[node]= min(tree[v1] , tree[v2]);
}


vector<pair<int,int> > niv[MAX];
int F[MAX];

int main(){
    
    int oo=(1<<30)-5;
    int n,m;

    while(cin>>n>>m){
        F[0]=0;
        
        for(int i=0;i<n;i++){
            scanf("%d",&v[i]);
            F[i+1]=F[i]+v[i];
        }

        int a,b,c;
        for(int i=0;i<m;i++){
            scanf("%d %d %d",&a,&b,&c);
            a--;
            niv[a].push_back( make_pair(b,c) );
        }
        
        dp[n]=0;
        int pos=n-1;
        int tam=n+1;
        update(0,tam-1,0,n,0);
        
        
        for(int i=n-1;i>=0;i--){
            dp[i]=oo;
            update(0,tam-1,0,i,oo);
            if(niv[i].size()>0){
                for(int j=0;j<niv[i].size();j++){
                    int S=niv[i][j].first;
                    int C=niv[i][j].second;
                    int lo=i;
                    int hi=n;
                    
                    if(S<v[i])continue;

                    while(lo+1!=hi){
                        int me=(lo+hi)/2;
                        if(F[me+1]-F[i] <=S){
                            lo=me;
                        }else{
                            hi=me;
                        }
                    }
                    
                    dp[i]=min(dp[i],C+query(0,tam-1,0,i+1,lo+1)  );
                    update(0,tam-1,0,i,dp[i]);=
                }
            }
        }
        
        if(dp[0]>=oo){
            cout<<-1<<endl;
        }else{
            cout<<dp[0]<<endl;
        }
        
        for(int i=0;i<MAX;i++)if(niv[i].size()>0)niv[i].clear();
    }
    return 0;
}
