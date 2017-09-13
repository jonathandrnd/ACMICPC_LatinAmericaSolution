#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<sstream>
#include<set>
#include<vector>
#include<map>
#include<cassert>
#include<queue>
using namespace std;

int main(){

    int n,m;
    
    while(cin>>n>>m){
        int dev=0;
        int budget,tengo,aux;
        
        for(int i=0;i<m;i++){
            cin>>budget;
            cin>>tengo;
            int sum=0;
            for(int j=0;j<n-1;j++){
                cin>>aux;
                sum+=aux;
            }
            
            if(sum>budget)continue;
            int win=0;
            if(sum+tengo<=budget)
                win=tengo;
                
            int diez=1;
            int maxi=0;
            for(int j=0;j<5;j++){
                if(sum+diez<=budget){
                    maxi=max(maxi,diez);
                }
                diez*=10;
            }
            
            dev+=maxi-win;
        }
        
        cout<<dev<<endl;
    }

    return 0;
}





