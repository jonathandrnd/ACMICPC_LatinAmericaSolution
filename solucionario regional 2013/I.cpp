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
#include <assert.h>
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

int main(){
    
    int x[52];
    int n;
    
    while(cin>>n){
        memset(x,0,sizeof(x));
        int mayor=0;
        
        for(int i=0;i<n;i++){
            int aux;
            scanf("%d",&aux);
            x[aux]++;
            mayor=max(aux,mayor);    
        }
        
        
        long long maxi=1;
        vector<long long>dev;
        
        for(int i=0;i<x[mayor]/2;i++)dev.push_back(2);
        
        for(int i=mayor-1;i>0;i--){
            for(int j=0;j<x[i];j++)
                dev.push_back(maxi);
            
            vector<long long>aux;
            for(int j=0;j<dev.size();j+=2){
                aux.push_back(dev[j]+dev[j+1]);
                maxi=max(maxi,dev[j]+dev[j+1]);
            }
            
            dev=aux;    
        }
        
        cout<<dev[0]<<endl;
    }
    
    return 0;
}
