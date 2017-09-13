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
int n;
char s[100000][81];
int trie[1000000][26];
int mask[1000000];
bool terminal[1000000];
int node;

void add(char *s){
    
    int p=0;
    
    for(int i=0;i<strlen(s);i++){
        mask[p]|=(1<<(s[i]-'a'));
        if(trie[p][s[i]-'a']==0){
            p=trie[p][s[i]-'a']=++node;    
        }else{
            p=trie[p][s[i]-'a'];
        }    
    }
    
    terminal[p]=1;
}

int main(){
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    
    
    while(cin>>n){
        
        memset(trie,0,sizeof(trie));
        memset(mask,0,sizeof(mask));
        memset(terminal,0,sizeof(terminal));
        
        
        node=0;
        for(int i=0;i<n;i++){
            scanf("%s",s[i]);
            add(s[i]);
        }
        
        int cont=0;
        
        for(int i=0;i<n;i++){
            int p=trie[0][s[i][0]-'a'];
            cont++;
            for(int j=1;j<strlen(s[i]);j++){
                if(__builtin_popcount(mask[p])>1 || terminal[p] ){
                    cont++;    
                }
                p=trie[p][s[i][j]-'a'];
            }
        }
        
        printf("%.2lf\n",cont/(n+0.0));
    }
     
    return 0;
}
