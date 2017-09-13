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
char c[603][303];
bool puede[603][603][4];
bool visited[603][603];

int main(){
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    
    int n;
    // arriba abajo derecha izquierda
    int di[4]={-1,1,0,0};
    int dj[4]={0,0,1,-1};
    
    while(cin>>n){
        
        memset(puede,1,sizeof(puede));
        memset(visited,0,sizeof(visited));
        
        for(int i=0;i<2*n-1;i++){
            for(int j=0;j<n;j++){
                int x=i;
                int y=2*j+(i&1);
                char ch;
                cin>>ch;
                
                if(ch=='H'){
                    puede[x][y][1]=puede[x][y+1][1]=0;
                    puede[x+1][y][0]=puede[x+1][y+1][0]=0;
                }else{
                    puede[x][y][2]=puede[x][y+1][3]=0;
                    puede[x+1][y][2]=puede[x+1][y+1][3]=0;
                }
                
            }   
        }
        
        int cont=-1;
        
        for(int i=0;i<2*n;i++){
            for(int j=0;j<2*n+1;j++){
                if(!visited[i][j]){
                    queue<pair<int,int> >Q; 
                    Q.push(make_pair(i,j));
                    visited[i][j]=1;
                    
                    while(!Q.empty()){
                        pair<int,int>P=Q.front();    
                        Q.pop();
                        for(int i=0;i<4;i++){
                            int X=P.first+di[i];
                            int Y=P.second+dj[i];
                            if(X>=0 && X<2*n && Y>=0 && Y<2*n+1)
                                if(!visited[X][Y]&& puede[P.first][P.second][i]){
                                    visited[X][Y]=1;
                                    Q.push(make_pair(X,Y));    
                                }
                        }
                        
                    }
                    cont++;        
                }
            }
        }
        
        cout<<cont<<endl;
    }
     
    return 0;
}
