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
int c[100000];
int tree[400001];

void init(int node,int a,int b){
    if(a==b){
        tree[node]=c[a];
        return ;    
    }
    
    init(2*node+1,a,(a+b)/2);
    init(2*node+2,(a+b)/2+1,b);
    
    tree[node]=tree[2*node+1]*tree[2*node+2];    
}

int query(int node,int a,int b,int p,int q){
    if( q<a || b<p )return 1;
    
    if(p<=a && b<=q){
        return tree[node];    
    }
    
    return query(2*node+1,a,(a+b)/2,p,q)*query(2*node+2,(a+b)/2+1,b,p,q);
}

void update(int node,int a,int b,int p,int val){
    if(p<a || b<p)return;
    
    if(a==b){
        tree[node]=val;    
        return ;
    }
    
    update(2*node+1,a,(a+b)/2,p,val);
    update(2*node+2,(a+b)/2+1,b,p,val);
    
    tree[node]=tree[2*node+1]*tree[2*node+2]; 
}

int f(int t){
    if(t>0)return 1;
    if(t<0)return -1;
    return 0;    
}

int main(){
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    
    int n,m;
    
    while(scanf("%d %d",&n,&m)==2){
        int aux;
        
        for(int i=0;i<n;i++){
            scanf("%d",&aux);
            c[i]=f(aux);
        }
        
        init(0,0,n-1);
        
        
        for(int i=0;i<m;i++){
            char ch;
            cin>>ch;
            
            if(ch=='C'){
                int a,val;
                scanf("%d %d",&a,&val);
                a--;
                update(0,0,n-1,a,f(val));
            }else{
                int a,b;
                scanf("%d %d",&a,&b);
                a--;b--;
                int x=query(0,0,n-1,a,b);
                
                if(x==0)printf("0");
                if(x>0)printf("+");
                if(x<0)printf("-");
                
            }
        }
        printf("\n");
    }
     
    return 0;
}
