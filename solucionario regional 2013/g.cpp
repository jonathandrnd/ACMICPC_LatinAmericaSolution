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
int c[100001];
int n;
int tree2[100001][20];
int loga[300001];

void rmq2(){
    for(int i=0;i<n;i++)tree2[i][0]=c[i];
    for(int i=1;i<=16;i++)
        for(int j=0;j+(1<<i)-1<=n;j++)
            tree2[j][i]=min(tree2[j][i-1], tree2[j+(1<<(i-1))][i-1]);    
}

int query2(int a,int b){
    int k=b-a+1;
    return min(tree2[a][loga[k]], tree2[b+1-(1<<loga[k])][loga[k]] );
}


int main(){
    
    
    loga[1]=0;
    for(int i=1;i<=16;i++)
        for(int j=(1<<i);j<(1<<(i+1));j++)
            loga[j]=i;
    
    
    while(cin>>n){
        for(int i=0;i<n;i++)
            scanf("%d",&c[i]);
        
        rmq2();
        
        
        int der[n];
        der[n-1]=n;
        for(int i=n-2;i>=0;i--){
            der[i]=i+1;
            while(der[i]<n && c[i]>=c[der[i]])
                der[i]=der[der[i]];    
        }
        
        int izq[n];
        izq[0]=-1;
        
        for(int i=1;i<n;i++){
            izq[i]=i-1;    
            while(izq[i]>=0 && c[i]>=c[izq[i]])
                izq[i]=izq[izq[i]];
        }
        
        
        vector<int>dev;
        
        for(int i=1;i+1<n;i++){
            if(c[i]>c[i+1] && c[i]>c[i-1]){
                int ini=izq[i];
                
                int nivel=c[i];
                
                if(ini!=-1)
                    nivel=c[i]-query2(ini,i);
                
                if(nivel<150000)continue;
                
                ini=der[i];
                nivel=c[i];
                
                if(ini!=n)
                    nivel=c[i]-query2(i,ini);
                
                if(nivel<150000)continue;
                
                dev.push_back(i+1);
            }    
        }
        
        
        printf("%d",dev[0]);
        
        for(int i=1;i<dev.size();i++)
            printf(" %d",dev[i]);
        printf("\n");
    }
    
    return 0;
}
