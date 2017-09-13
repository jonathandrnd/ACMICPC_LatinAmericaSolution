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
string s;
int pot3[21];long long pot10[21];
long long memo[20][2][100001];

long long dp(int pos,bool menor,int val){
    if(pos==-1)return 0;
    if(memo[pos][menor][val]!=-1)return memo[pos][menor][val];

    int aux=val;
    int c[10];
    for(int i=0;i<10;i++){
        c[i]=aux%3;
        aux/=3;
    }

    long long dev=-1LL<<60;
    if(menor){//el numero que estoy formando ya es menor asi que le puedo meter cualquier digito
        for(int i=0;i<=9;i++)
            if(c[i]<2)
                dev=max(dev, i*pot10[pos] +  dp(pos-1,menor,val+pot3[i]));
    }else{
        //Si pongo un digito menor al digito  en analisis entonces ya estare formando un numero menor bool menor=1
        for(int i=0;i<(s[pos]-'0');i++)
            if(c[i]<2)
                dev=max(dev, i*pot10[pos] +  dp(pos-1,1,val+pot3[i]));
        //colocamos el mismo digito que el de analisis S  bool menor=0 se mantiene.
        if(c[s[pos]-'0']<2)
            dev=max(dev, (s[pos]-'0')*pot10[pos] + dp(pos-1,menor,val+pot3[s[pos]-'0']));
    }

    memo[pos][menor][val]=dev;
    return dev;
}

int main(){

    pot3[0]=pot10[0]=1;
    for(int i=1;i<=10;i++)pot3[i]=pot3[i-1]*3;
    for(int i=1;i<=18;i++)pot10[i]=pot10[i-1]*10;

    while(cin>>s){
        reverse(s.begin(),s.end());
        //cout<<s<<endl;
        int t=s.size();

        memset(memo,-1,sizeof(memo));
        long long dev=1;
        //voy desde la posicion mas significativa
        for(int i=1;i<=(s[t-1]-'0');i++)
            if(i==(s[t-1]-'0'))
                dev=max(dev, i*pot10[t-1]  +dp(t-2,0,pot3[i]));
            else
                dev=max(dev, i*pot10[t-1]  +dp(t-2,1,pot3[i]));

        if(t>=2)
            dev=max(dev,  9*pot10[t-2]  +dp(t-3,1,pot3[9])  )   ;

        cout<<dev<<endl;
    }

    return 0;
}


