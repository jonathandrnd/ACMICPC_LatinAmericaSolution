#include <iostream>
#include <cstring>
#include <cmath>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <map>
#include <unordered_map>
using namespace std;

//dot product
int area(pair<int,int>a,pair<int,int>b,pair<int,int>c){
	int x1 = b.first - a.first;
	int y1 = b.second - a.second;
	
	int x2 = c.first - a.first;
	int y2 = c.second -a.second;
	
	return x1*y2 -x2*y1;
}

vector<pair<int,int>> ConvexHull(vector <pair<int,int>> &P){
    sort(P.begin(),P.end());
    int n = P.size(),k = 0;
    pair<int,int> H[2*n];
    
    for(int i=0;i<n;++i){
        while(k>=2 && area(H[k-2],H[k-1],P[i]) <0) --k;
        H[k++] = P[i];
    }
    
    for(int i=n-2,t=k;i>=0;--i){
        while(k>t && area(H[k-2],H[k-1],P[i]) < 0) --k;
        H[k++] = P[i];
    }
    
    return vector <pair<int,int>> (H,H+k-1);
}



int main() {
	int n;	
	while(cin>>n){
		map< pair<int,int>, int>m;
		vector<pair<int,int> >P;
		vector<pair<int, pair<int,int> > >ordered;//(bright, x,y)
		
		
		for(int i = 0;i < n; i++){
			int x, y, b;
			cin>>x>>y>>b;
			P.push_back(make_pair(x,y));
			m[make_pair(x,y)] = b;
			ordered.push_back(make_pair(b,make_pair(x,y)));
		}
		
		sort(ordered.begin(),ordered.end());
		vector<pair<int,int> > hull = ConvexHull(P);
		
		int sizeorder = ordered.size();
		n = hull.size();
		
		if(hull.size()<3){
			cout<<"Y"<<endl;
			continue;
		}
		
		bool ok = 0;
		
		for(int i = 0;i< hull.size() && !ok;i++)
			for(int j = i + 1;j < hull.size();j++){
				int dx = hull[i].first -hull[j].first;
				int dy = hull[i].second - hull[j].second;
				
				int firstval = 1<<30;
				
				bool increasing = false;
				bool yeah = true;
				for(int k = 0; k< sizeorder;){
					int B = ordered[k].first;
					int minimum = 1<<30;
					int maximum = -1<<30;
					
					while(k < sizeorder && ordered[k].first ==B){
						int val = ordered[k].second.first*dy -ordered[k].second.second*dx;
						minimum = min(minimum, val);
						maximum = max(maximum, val);
						k++;
					}
					
					if(increasing){
						if(minimum < firstval){
							yeah = false;
							break;
						}
						firstval = maximum;
					}else{
						
						if(maximum >firstval){
							yeah = false;
							break;
						}
						firstval =  minimum;
					}
					
				}
				
				
				if(yeah){
					ok=true;
					break;
				}
				
				
				firstval = -1<<30;
			    increasing = true;
				yeah = true;
				for(int k = 0; k < sizeorder;){
					int B = ordered[k].first;
					int minimum = 1<<30;
					int maximum = -1<<30;
					
					while(k < sizeorder && ordered[k].first ==B){
						int val = ordered[k].second.first*dy -ordered[k].second.second*dx;
						minimum = min(minimum, val);
						maximum = max(maximum, val);
						k++;
					}
					
					if(increasing){
						if(minimum < firstval){
							yeah = false;
							break;
						}
						firstval = maximum;
					}else{
						
						if(maximum >firstval){
							yeah = false;
							break;
						}
						firstval =  minimum;
					}	
				}
				
				if(yeah){
					ok=true;
					break;
				}
			}
		
		if(ok){
			cout<<"Y"<<endl;
		}else{
			cout<<"N"<<endl;
		}
		
	}
	
	
		
	return 0;
}
