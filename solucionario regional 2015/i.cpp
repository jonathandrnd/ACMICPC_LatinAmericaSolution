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

int main(){
//freopen("in.txt","r",stdin);
//freopen("out.txt","w",stdout);

    int t;

    while(cin>>t){
        int x;int cont=0;
        for(int i=0;i<5;i++){
            cin>>x;
            if(x==t)cont++;
        }
        cout<<cont<<endl;
    }


    return 0;
}


