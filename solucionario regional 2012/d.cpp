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

int f(int t){
    bitset<10>visited;
     
    while(t!=0){
        if(visited[t%10])return 0;
        visited[t%10]=1;
        t/=10;    
    }
    
    return 1;
}
 
int main(){
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
   
    int c[5001];
    c[0]=0;
    
    for(int i=1;i<=5000;i++)
        c[i]=c[i-1]+f(i);
    
    int a,b;
    while(scanf("%d %d",&a,&b)==2){
        printf("%d\n",c[b]-c[a-1]);
    }
    
    return 0;
}
