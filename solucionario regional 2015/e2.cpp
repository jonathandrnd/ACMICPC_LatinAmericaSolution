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
int a[101],b[101];
vector<int>v1[101];
vector<int>v2[101];
bool visitedL[101];
bool visitedR[101];
set<int>L,R;
int memo[101][10005];
vector<int>tam,cost;
int n,m,r,c;

void dfs(int t,bool izq){
    if(izq){
        visitedL[t]=1;
        L.insert(t);
        for(int i=0;i<v1[t].size();i++){
            if(!visitedR[v1[t][i]]){
                dfs(v1[t][i],!izq);
            }
        }
    }else{
        visitedR[t]=1;
        R.insert(t);
        for(int i=0;i<v2[t].size();i++){
            if(!visitedL[v2[t][i]]){
                dfs(v2[t][i],!izq);
            }
        }
    }
    return ;
}

int dp(int pos,int ac){
    if(pos==-1)return 0;
    if(memo[pos][ac]!=-1)return memo[pos][ac];
    int dev=dp(pos-1,ac);
    if(ac+cost[pos]<=c )
        dev=max(dev, tam[pos]+dp(pos-1,ac+cost[pos])  );
    memo[pos][ac]=dev;
    return dev;
}


int main(){

    
    while(cin>>n>>m>>r>>c){
        for(int i=0;i<101;i++){v1[i].clear();v2[i].clear();}
        for(int i=0;i<n;i++)cin>>a[i];
        for(int i=0;i<m;i++)cin>>b[i];
        for(int i=0;i<r;i++){
            int p,q;
            cin>>p>>q;
            p--;q--;
            v1[p].push_back(q);
            v2[q].push_back(p);
        }

        memset(visitedL,0,sizeof(visitedL));
        memset(visitedR,0,sizeof(visitedR));
        tam.clear();cost.clear();
        
        for(int i=0;i<n;i++){
            if(!visitedL[i]){
                L.clear();R.clear();
                dfs(i,1);
                if(R.size()<L.size()){
                    vector<int>nodoizq(L.begin(),L.end());
                    vector<int>nododer(R.begin(),R.end());
                    int sumcost=0;
                    for(int j=0;j<nodoizq.size();j++)
                        sumcost+= a[nodoizq[j]];
                    for(int j=0;j<nododer.size();j++)
                        sumcost+= b[nododer[j]];
                    tam.push_back(L.size()-(int)R.size());
                    cost.push_back(sumcost);
                }
            }
        }
        
        memset(memo,-1,sizeof(memo));
        int dev1=m;
        if(tam.size()>0)
            dev1+=dp(tam.size()-1,0);
        /*
        cout<<"x ";
        for(int i=0;i<tam.size();i++)cout<<tam[i]<<" ";
        cout<<endl;
        cout<<"x ";
        for(int i=0;i<cost.size();i++)cout<<cost[i]<<" ";
        cout<<endl;
        */
        
        tam.clear();cost.clear();
        memset(memo,-1,sizeof(memo));
        memset(visitedL,0,sizeof(visitedL));
        memset(visitedR,0,sizeof(visitedR));

        for(int i=0;i<m;i++){
            if(!visitedR[i]){
                L.clear();R.clear();
                dfs(i,0);
                if(R.size()>L.size()){
                    vector<int>nodoizq(L.begin(),L.end());
                    vector<int>nododer(R.begin(),R.end());
                    int sumcost=0;
                    for(int j=0;j<nodoizq.size();j++)
                        sumcost+= a[nodoizq[j]];
                    for(int j=0;j<nododer.size();j++)
                        sumcost+= b[nododer[j]];
                    tam.push_back(R.size()-(int)L.size());
                    cost.push_back(sumcost);
                }
            }
        }

        /*
        cout<<"x ";
        for(int i=0;i<tam.size();i++)cout<<tam[i]<<" ";
        cout<<endl;
        cout<<"x ";
        for(int i=0;i<cost.size();i++)cout<<cost[i]<<" ";
        cout<<endl;
        */
        int dev2=n;
        if(tam.size()>0)
            dev2+=dp(tam.size()-1,0);

        cout<<dev2<<" "<<dev1<<endl;
    }
    
    return 0;
}

