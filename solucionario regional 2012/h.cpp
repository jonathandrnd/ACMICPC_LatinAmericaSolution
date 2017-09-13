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


int main(){
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
   
    int n;
    bool visited[360];
    memset(visited,0,sizeof(visited));
    
    for(int i=0;i<12;i++){
        for(int j=0;j<60;j++){
            int ang1=30*i+ 6*(j/12);
            int ang2=6*j;
            int mini=min(abs(ang1-ang2),360-abs(ang1-ang2));
            visited[mini]=1;    
        }
    }
    
    while(cin>>n){
        if(visited[n])
            cout<<"Y"<<endl;
        else
            cout<<"N"<<endl;
    }
    
    return 0;
}
