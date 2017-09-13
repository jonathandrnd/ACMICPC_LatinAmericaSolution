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


struct nodo{
    int q;
    double d;

    nodo(){}
    nodo(int _q,double _d){
        q=_q;
        d=_d;
    }
};


bool operator<(nodo a, nodo b){
    if(a.d!=b.d)return a.d>b.d;
    return a.q<b.q;
}

int n,m;
vector<pair<int,pair<int,int> > >v[1002];



double t;
double d[1002];

double dijkstra(){
    for(int i=1;i<=n;i++)d[i]=1e+12;
    d[1]=0;
    double dev=0;
    priority_queue<nodo >Q;
    Q.push(nodo(1,0));
    
    while(!Q.empty()){
        nodo x=Q.top();
        Q.pop();
        int q=x.q;
        double dis=x.d;
        
        for(int i=0;i<v[q].size();i++){
            if( d[v[q][i].first] >  d[q]+ (v[q][i].second.first*t+v[q][i].second.second)+1e-9 ){
                d[v[q][i].first] =d[q]+ (v[q][i].second.first*t+v[q][i].second.second);
                Q.push(nodo(v[q][i].first,d[v[q][i].first]  ));
            }
        }
    }
    
    return d[n];
}


double f(double x){
    t=x;
    return dijkstra();
    //for(int i=0;i<1002;i++)memo[i]=-1;
    //return dp(1);
}

int main(){


    while(cin>>n>>m){
        for(int i=0;i<1002;i++)v[i].clear();

        int I,J,A,B;
        double lo=0;
        double hi=1440;
        
        for(int i=0;i<m;i++){
            cin>>I>>J>>A>>B;
            v[I].push_back(make_pair(J,make_pair(A,B)));
            v[J].push_back(make_pair(I,make_pair(A,B)));
            
            if(A==0)continue;
            if(A>0){if(B<0)lo=max(lo,-(double)B/A);}
            if(A<0){if(B>0)hi=min(hi,-(double)B/A);}
        }
        
        
        
        
        for(int it=0;it<100;it++){
            double me1=(2*lo+hi)/3;
            double me2=(lo+2*hi)/3;
            if(f(me1)<f(me2)){
                lo=me1;
            }else{
                hi=me2;
            }
        }

        
        printf("%.5lf\n",f(lo));
    }
    return 0;
}

