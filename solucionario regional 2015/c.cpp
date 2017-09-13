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
using namespace std; 
int n;
long long x[100001],y[100001];
long long ac[200005];
long long area;

long long f(int a,int b){
    long long dev=ac[b-1];
    if(a>0)dev-=ac[a-1];
    long long A1=abs( dev+(x[b%n]*y[a%n]-x[a%n]*y[b%n])  );
    long long A2= area-A1;
    return max(A1,A2);
}

int main(){

    
    while(cin>>n){
        int a,b;
        for(int i=0;i<n;i++){
            scanf("%d %d",&a,&b);
            x[i]=a;
            y[i]=b;
        }
        
        long long sum=0;
        area=0;
        for(int i=0;i<n;i++)
            area+=(x[i%n]*y[(i+1)%n]- x[(i+1)%n]*y[i%n] );
            
        area=abs(area);

        for(int i=0;i<2*n;i++){
            ac[i]= (x[i%n]*y[(i+1)%n]- x[(i+1)%n]*y[i%n] );
            if(i>0)ac[i]+=ac[i-1];
        }
        
        long long maxi=0;

        for(int i=0;i<n;i++){
            int lo=i;
            int hi=i+n-1;
            for(int j=0;j<35;j++){
                int me1=(2*lo+hi)/3;
                int me2=(lo+2*hi)/3;
                if( f(i,me1)<f(i,me2) ){
                    hi=me2;
                }else{
                    lo=me1;
                }
            }
            
            long long mini=1LL<<60;
            for(int j=lo;j<=hi;j++)
                mini=min(mini,f(i,j));
            
            maxi=max(mini,maxi);
        }
        cout<<maxi<<" "<<(area-maxi)<<endl;
    }
    
    return 0;
}
