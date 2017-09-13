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
int R,C;
int c[101][101];
bool visited[101][101];
int di[4]={-1,1,0,0};
int dj[4]={0,0,1,-1};

void dfs(int x, int y){
    visited[x][y]=1;
    for(int i=0;i<4;i++){
        int X=x+di[i];
        int Y=y+dj[i];
        if(X>=0 && X<R && Y>=0 && Y<C)
            if(!visited[X][Y] && c[x][y]==c[X][Y]){
                dfs(X,Y);
            }
    }
    return ;
}

int main(){


    while(cin>>R>>C){
        for(int i=0;i<R;i++)
            for(int j=0;j<C;j++)
                cin>>c[i][j];
        int dev=5;
        //cout<<"dev "<<dev<<endl;
        //parte1
        for(int i=R-2;i>=0;i--){
            int ini=0;int fin=0;
            for(int j=0;j<C;j++){
                if(c[i][j]>c[i+1][j]){
                    if(c[i][j]<=ini || c[i+1][j]>=fin){
                        dev++;
                    }
                    ini=c[i+1][j];
                    fin=c[i][j];
                }else{
                    ini=0;fin=0;
                }
            }
        }
        
        //cout<<"dev "<<dev<<endl;
        //parte2
        for(int i=1;i<R;i++){
            int ini=0;int fin=0;
            for(int j=0;j<C;j++){
                if(c[i][j]>c[i-1][j]){
                    if(c[i][j]<=ini || c[i-1][j]>=fin){
                        dev++;
                    }
                    ini=c[i-1][j];
                    fin=c[i][j];
                }else{
                    ini=0;fin=0;
                }
            }
        }

        //cout<<"dev "<<dev<<endl;
        //parte3
        for(int j=C-2;j>=0;j--){
            int ini=0;int fin=0;
            for(int i=0;i<R;i++){
                if(c[i][j]>c[i][j+1]){
                    if(c[i][j]<=ini || c[i][j+1]>=fin){
                        dev++;
                    }
                    ini=c[i][j+1];
                    fin=c[i][j];
                }else{
                    ini=0;fin=0;
                }
            }
        }

        //cout<<"dev "<<dev<<endl;
        //parte4
        for(int j=1;j<C;j++){
            int ini=0;int fin=0;
            for(int i=0;i<R;i++){
                if(c[i][j]>c[i][j-1]){
                    if(c[i][j]<=ini || c[i][j-1]>=fin){
                        dev++;
                    }
                    ini=c[i][j-1];
                    fin=c[i][j];
                }else{
                    ini=0;fin=0;
                }
            }
        }

        memset(visited,0,sizeof(visited));
        //cout<<"dev "<<dev<<endl;
        for(int i=0;i<R;i++)
            for(int j=0;j<C;j++)
                if(!visited[i][j]){
                    dev++;
                    dfs(i,j);
                }
        
        cout<<dev<<endl;
    }

    return 0;
}

