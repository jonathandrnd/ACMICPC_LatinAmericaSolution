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
int tree[300001];
int maxVal=300000;

int query(int idx){
    int sum=0;
    while(idx!=0){
        sum+=tree[idx];
        idx-=(idx&-idx);
    }
    return sum;
}

void update(int idx,int val){
    while(idx<maxVal){
        tree[idx]+=val;
        idx+=(idx&-idx);
    }
}

int x[200005],y[200005];
map<int,int>mx,my;

vector<pair<int,pair<int,int> > >vert;
vector<pair<int,pair<int,int> > >Q;

int main(){
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);

    int n,m;//m consulta  n poligono
    while(scanf("%d %d",&m,&n)==2){
        memset(tree,0,sizeof(tree));
        int a,b;
        mx.clear();my.clear();
        int tam=n+m;
        Q.clear();
        for(int i=0;i<m;i++){
            scanf("%d %d",&a,&b);
            x[i+n]=a;y[i+n]=b;
            Q.push_back(make_pair(a, make_pair(b,i+1 ) ));
        }

        for(int i=0;i<n;i++){
            scanf("%d %d",&a,&b);
            x[i]=a;y[i]=b;
        }
        
        vert.clear();
        
        for(int i=0;i<n;i++){
            int x1=x[i];int y1=y[i];
            int x2=x[(i+1)%n];int y2=y[(i+1)%n];
            if(x1==x2){
                vert.push_back(make_pair(x1,make_pair(min(y1,y2),max(y1,y2))));
            }
        }
        
        
        
        sort(x,x+tam);
        sort(y,y+tam);
//////////////COMPRESION DE COORDENADAS//////////////////////
        mx[x[0]]=1;
        int val=2;
        for(int i=1;i<tam;i++)
            if(x[i]!=x[i-1])
                mx[x[i]]=val++;

        val=3;
        my[y[0]]=1;
        for(int i=1;i<tam;i++)
            if(y[i]!=y[i-1]){
                my[y[i]]=val;
                val+=2;
            }
///////////////////////////////////7777777777777777777777777777

        sort(vert.begin(),vert.end());
        sort(Q.begin(),Q.end());
        int id=0;
        long long  sum=0;

        for(int i=0;i<Q.size();i++){
            int x1=mx[Q[i].first];
            int y1=my[Q[i].second.first];
            int num=Q[i].second.second;
            while(id<vert.size()){
                int v1=my[vert[id].second.first];
                int v2=my[vert[id].second.second];
                int h=mx[vert[id].first];
                if(h>=x1){
                    int tot=query(y1+1);
                    if(tot%2==0)sum+=num;
                    break;
                }else{
                    update(v1,1);
                    update(v2+1,-1);
                    id++;
                }
            }
            
            if(id==vert.size())sum+=num;
        }

        cout<<sum<<endl;
    }
    
    return 0;
}


