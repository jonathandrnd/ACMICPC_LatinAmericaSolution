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
int cant[10];
long long memo[11][11][101];
long long C[101][101];

void combinatoria(){
    C[0][0]=1;
    for(int i=1;i<=100;i++){
        C[i][0]=1;C[i][i]=1;
        for(int j=1;j<i;j++){
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%1000000007;
        }
    }
}


long long dp(int pos,int modulo,int posi,int nega){
    if(pos==10)return (modulo==0);
    if(memo[pos][modulo][posi]!=-1)return memo[pos][modulo][posi];
    
    long long dev=0;
    int tam=posi+nega;
    int tot=cant[pos];
    
    for(int i=0;i<=min(posi,tot);i++){
        int primer=i;
        int segundo=tot-i;
        if(segundo<=nega){
            long long aux=(C[posi][primer]*C[nega][segundo])%1000000007;
            dev+=aux*dp(pos+1,(modulo+primer*pos-segundo*pos+110000)%11,posi-primer,nega-segundo);
            dev=dev%1000000007;
        }
    }
    
    
    memo[pos][modulo][posi]=dev;
    return dev;
}

int main(){
    combinatoria();
    
    string s;
    while(cin>>s){
        memset(cant,0,sizeof(cant));
        for(int i=0;i<s.size();i++)
            cant[s[i]-'0']++;    
        
        int posi=(s.size()+1)/2;
        int nega=s.size()-posi;
        
        long long dev=0;
        for(int i=1;i<=9;i++){
            if(cant[i]==0)continue;
            int aux=i;
            if(s.size()%2==0)nega--,aux=11-i;
                else posi--;
            
            cant[i]--;
            memset(memo,-1,sizeof(memo));
            
            
            dev=(dev+dp(0,aux,posi,nega))%1000000007;
            cant[i]++;
            if(s.size()%2==0)nega++;
                else posi++;
            
        }
        
        cout<<dev<<endl;
    }
    return 0;
}
