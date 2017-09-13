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

int target[66];
long long memo[66][2][66];

long long dp(int pos,bool menor,int sum){
    if(pos==-1)return sum;
    if(memo[pos][menor][sum]!=-1)return memo[pos][menor][sum];
    long long dev=0;
    
    if(menor){
        dev+=dp(pos-1,menor,sum+1)+dp(pos-1,menor,sum);    
    }else{
        if(target[pos]==0){
            dev+=dp(pos-1,menor,sum);    
        }else{
            dev+=dp(pos-1,1,sum)+dp(pos-1,0,sum+1);    
        }    
    }
    
    memo[pos][menor][sum]=dev;
    return dev;
}

long long f(long long t){
    int cont=0;
    while(t!=0){
        target[cont++]=t%2;
        t/=2;    
    }
    memset(memo,-1,sizeof(memo));
    return dp(cont-1,0,0);
}

int main(){
    
    long long a,b;
    while(cin>>a>>b){
        cout<<f(b)-f(a-1)<<endl;    
    }
    
    
    return 0;
}
