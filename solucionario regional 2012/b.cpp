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
#define MOD 1000000007
long long S,B;

long long memo[101][201][201];

long long dp(int pos,int piedras,int val){
    
    if(pos==0){
        if(val==0 && piedras==0)return 1;    
        return 0;
    }
    
    if(memo[pos][piedras][val]!=-1)return memo[pos][piedras][val];
    long long dev=dp(pos-1,piedras,val/2);
    if(piedras>0)
        dev= (dev+dp(pos,piedras-1,val+1))%MOD;
    
    memo[pos][piedras][val]=dev;
    return dev;
}

int main(){
    
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    
    int n;
    memset(memo,-1,sizeof(memo));
    
    while(cin>>S>>B){
        cout<<dp(B-1,S,0)%MOD<<endl;
    }
    
    return 0;
}
