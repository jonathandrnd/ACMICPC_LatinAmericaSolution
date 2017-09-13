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
#include <assert.h>
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
string s,t;
int n,m,q;

long long mascara[400001];
int flag[400001];

inline void init(int node,int a,int b){
    if(a==b){
        long long mask=0;
        if(n-a>=m){
            for(int i=0;i<m;i++)
                if(tolower(t[i])==tolower(s[a+i])){
                    if(isupper(s[a+i])){
                        mask|=(1<<i);
                    }
                }else{
                    mask=-1;
                    break;
                }
        }else mask=-1;
        
        if(mask!=-1)mascara[node]=1LL<<mask; 
        else mascara[node]=0;
        flag[node]=0;
        return ;
    }
    
    init(2*node+1,a,(a+b)/2);
    init(2*node+2,(a+b)/2+1,b);
    
    mascara[node]=mascara[2*node+1]|mascara[2*node+2];    
    flag[node]=0;
    
}

inline void push(int node,int a,int b){
    if(flag[node]==1){
        long long aux=mascara[node];
        long long aux2=0;
        
        for(int i=(1<<m)-1;i>=0;i--){
            if((aux&(1LL<<i))!=0 )
                aux2|=1LL<<(i^((1<<m)-1));
        }
        
        mascara[node]=aux2;
        flag[node]=0;
        
        
        if(a!=b){
            flag[2*node+1]=!flag[2*node+1];
            flag[2*node+2]=!flag[2*node+2];
        } 
        
    }
    
    if(flag[node]<0){
        flag[node]=-flag[node];
        
        if(mascara[node]==0){
            flag[node]=0;
            return;
        }
        
        int cont=0;
        long long x=mascara[node];
        while(x!=1){
            cont++;
            x/=2;
        }
        
        mascara[node]=1LL<<(cont^((1<<flag[node])-1));
        flag[node]=0;
    }
        
}

inline long long query(int node,int p,int q,int a,int b){
    push(node,p,q);
    if(q<a || p>b)return 0;
    
    if(a<=p && q<=b)return mascara[node];
    
    long long v1=query(2*node+1,p,(p+q)/2,a,b);
    long long v2=query(2*node+2,(p+q)/2+1,q,a,b);
    
    mascara[node]=mascara[2*node+1]|mascara[2*node+2];
    
    return v1|v2;
}

void update(int node,int p,int q,int a,int b){
    push(node,p,q);
    if(q<a || p>b)return ;
    
    if(a<=p && q<=b){
        flag[node]=1;
        push(node,p,q);
        return ;    
    }
    
    update(2*node+1,p,(p+q)/2,a,b);
    update(2*node+2,(p+q)/2+1,q,a,b);
    
    mascara[node]=mascara[2*node+1]|mascara[2*node+2];   
    return ;
}

void update2(int node,int p,int q,int a,int b){
    push(node,p,q);
    if(q<a || p>b)return ;
    
    if(p==q){
        flag[node]=-(b-p+1);
        push(node,p,q);
        return ;    
    }
    
    update2(2*node+1,p,(p+q)/2,a,b);
    update2(2*node+2,(p+q)/2+1,q,a,b);
    
    mascara[node]=mascara[2*node+1]|mascara[2*node+2];
    
    return ;
}

int main(){
    
    while(cin>>q){
        cin>>t>>s;
        n=s.size();
        m=t.size();
        
        init(0,0,n-1);
        int maximo[32];
        for(int i=0;i<(1<<m);i++){
            int cont=0;
            for(int j=0;j<m;j++){
                if( ((i&(1<<j))==0&& isupper(t[j])) || 
                    ((i&(1<<j))!=0&& islower(t[j]))){
                    cont++;        
                }
            }
            maximo[i]=cont;
        }
        
        for(int i=0;i<q;i++){
            int a,b;
            scanf("%d %d",&a,&b);
            a--;b--;
            
            if(b-a+1<m)printf("-1\n");
            else{
                long long mask=query(0,0,n-1,a,b-m+1);
                 
                int maxi=-1;
                
                if(mask!=0){
                    for(int j=0;j<(1<<m);j++)
                        if( (mask&(1LL<<j))!=0 ){
                            maxi=max(maxi,maximo[j]);
                        }
                }
                
                printf("%d\n",maxi);
                
            }
            
            if(b-m+1>=0)
                update(0,0,n-1,0,b-m+1);
            
            update2(0,0,n-1,max(0,b-m+2),b);
            
            if(a-m>=0)
                update(0,0,n-1,0,a-m);
            
            if(a>0)    
                update2(0,0,n-1,max(0,a-1-m+2),a-1);
            
        }        
    }
    
    return 0;
}
