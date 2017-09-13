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

struct point{
    point(){}
    long long x,y;
    point(long long _x,long long _y){
        x=_x;y=_y;    
    }
};

long long operator %(point a, point b){return a.x*b.y-b.x*a.y;}
point operator -(point a,point b){return point(a.x-b.x,a.y-b.y);}

int n,K;
int tam;
long long p[1001],w[1001];
long long dp[1001][1001];
long long W[1001];
long long G[1001];
point T[1001];

inline void add(long long x, long long y){
    point p(x, y);
    while(tam>= 2 && (p-T[tam-1])%(p-T[tam-2])>= 0)tam--;
    T[tam++] = p;
    //if(tam>=2 && T[tam - 1].x == T[tam - 2].x) tam--;
}

inline long long evalua(int a,int pos){
    return T[a].x*W[pos] +T[a].y ;
}

int main(){
    
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    
    while(cin>>n>>K){
        W[0]=G[0]=0;
        
        for(int i=0;i<n;i++){
            scanf("%lld %lld",&p[i],&w[i]);
            G[i+1]=G[i]+w[i]*p[i];
            W[i+1]= W[i]+w[i];
        }
                    
        for(int k=0;k<=K;k++){
            tam=0;
            for(int pos=n;pos>=0;pos--){
                dp[pos][k]=1LL<<60;
                if(pos==n){
                    if(k==0)dp[pos][k]=0;
                    continue;
                }
                
                if(k==0)continue;
                
                if(dp[pos+1][k-1]!=(1LL<<60))
                    add(-p[pos],dp[pos+1][k-1]+p[pos]*W[pos+1]-G[pos+1] );
                
                int low=0;int hi=tam-1;
                
                
                long long mid1,mid2;
                
                while(hi-low>=4){
                    mid1=(2*low+hi)/3;
                    mid2=(low+2*hi)/3;
                    if(evalua(mid1,pos)< evalua(mid2,pos) ){
                        hi=mid2;    
                    }else{
                        low=mid1;       
                    }    
                }
                
                long long mini=1LL<<60;
                for(int jj=low;jj<=hi;jj++){
                    mini=min(mini,evalua(jj,pos)+G[pos]);
                }
                
                dp[pos][k]=mini;
            }
        }
        
        cout<<dp[0][K]<<endl; 
    }
    
    return 0;
}


