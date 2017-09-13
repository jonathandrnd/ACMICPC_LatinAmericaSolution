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
double a1[9],a2[9];
double b1[9],b2[9];
int w,d,a,k;

inline double f(double x,double me){
    double num1=0,den1=0,num2=0,den2=0;
    
    for(int i=k;i>=0;i--){
        num1=num1*x+a1[i];
        den1=den1*x+b1[i];
        num2=num2*x+a2[i];
        den2=den2*x+b2[i];
    }
    
    double image1=num1/den1;
    double image2=num2/den2;
    
    if(me>image1)return 0;
    
    if(me>image2)return image1-me;
    return image1-image2;
}

int main(){
    
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    
    int n;
    
    while(scanf("%d %d %d %d",&w,&d,&a,&k)==4){
        
        for(int i=0;i<k+1;i++)
            scanf("%lf",&a1[i]);    
        
        for(int i=0;i<k+1;i++)
            scanf("%lf",&b1[i]);    
        
        for(int i=0;i<k+1;i++)
            scanf("%lf",&a2[i]);    
        
        for(int i=0;i<k+1;i++)
            scanf("%lf",&b2[i]);    
        
        double low=-d;
        double hi=0;
            
        for(int ii=0;ii<22;ii++){
            double me=(low+hi)/2;
            double dif=1e-3;
            double ini=0;
            double sum=0;
            
            for(int i=0;i<1000*w;i++,ini+=dif)
                sum+=(f(ini,me)+4*f(ini+dif/2,me)+f(ini+dif,me) )/6.0;
            
                          
            if(sum*dif <a ){
                hi=me;
            }else{
                low=me;    
            }
        }
        
        printf("%.5f\n",-low);
    }
    
    return 0;
}
