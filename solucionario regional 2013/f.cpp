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

int main(){
    
    int n,g;
    while(cin>>n>>g){
        int win=0;
        vector<int>v;
        
        for(int i=0;i<n;i++){
            int a,b;
            cin>>a>>b;
            if(a>b)win+=3;
            else{
                if(a==b)win++;
                v.push_back(b-a);   
            }   
        }
        
        sort(v.begin(),v.end());
        int dev=win;
        int sum=0;
        
        for(int i=0;i<v.size();i++){
            if(v[i]==0){
                if(g>0){
                    g--;       
                    dev+=2;
                }
            }
            
            
            if(v[i]>0 && g>=v[i]+1){
                g-=v[i]+1;
                dev+=3;    
            }else{
                if(v[i]>0&& g==v[i]){
                    g=0;
                    dev++;    
                }    
            }    
        }
        
        cout<<dev<<endl;
    }
    
    return 0;
}
