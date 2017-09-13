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
#define f(i,x,y) for (int i = x; i < y; i++)
#define fd(i,x,y) for(int i = x; i>= y; i--)
#define FOR(it,A) for(typeof A.begin() it = A.begin(); it!=A.end(); it++)
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define vint vector<int>
#define ll long long
#define clr(A,x) memset(A, x, sizeof A)
#define pb push_back
#define pii pair<int,int>
#define fst first
#define snd second
#define ones(x) __builtin_popcount(x)
#define cua(x) (x)*(x)
#define eps (1e-14)
#define oo (1<<30)
#define debug(x) cout <<#x << " = " << x << endl
#define adebug(x,n) cout <<#x<<endl; f(i,0,n)cout<<x[i]<<char(i+1==n?10:32)
#define mdebug(x,m,n) cout <<#x<<endl; f(i,0,m)f(j,0,n)cout<<x[i][j]<<char(j+1==n?10:32)
#define N 10005
using namespace std;
template<class T> inline void mini(T &a,T b){if(b<a) a=b;}
template<class T> inline void maxi(T &a,T b){if(b>a) a=b;}


struct punto {
	long double x,y;
	punto(long double x, double y): x(x), y(y) {}
	punto() {}
	punto operator+ (punto p) { return punto(x + p.x, y + p.y); }
	punto operator- (punto p) { return punto(x - p.x, y - p.y); }
	punto operator* (long double t) { return punto(x*t, y*t); }
	punto operator/ (long double t) { return punto(x/t, y/t); }
	long double operator*(punto p) { return x*p.x + y*p.y; }
	long double operator%(punto p) { return x*p.y - y*p.x; }
	long double tam() { return x*x + y*y; }
	punto operator~() { return punto(-y,x); }
	void read() { scanf("%Lf%Lf", &x, &y); }
	void print() { printf("%.6Lf %.6Lf\n", x, y); }
};
struct superpunto {
	punto p; int z;
	superpunto(punto p, int z) : p(p), z(z) {}
	superpunto() {}
};

punto O,w;
int above(punto p) {
	if (p.y == O.y) return p.x > O.x;
	return p.y > O.y;
}
bool ordenCircular(punto p, punto q) {
	int tmp = above(q) - above(p);
	if (tmp!=0) return tmp > 0;
	return (p-O)%(q-O) > 0;
}
bool ordenCircular2(superpunto P, superpunto Q) {
	return ordenCircular(P.p, Q.p);
}

long double cmp(double a, double b=0) { return a < b-eps? -1 : a > b+eps? 1 : 0; }
long double norma(punto a, punto b = punto(0,0)) { return hypot(a.x-b.x, a.y-b.y); }
long double angulo(punto a, punto b) { 
	a = a/norma(a);
	b = b/norma(b);
	long double calfa = a*b;
	mini(calfa, (long double)1.0);
	maxi(calfa, (long double)-1.0);
	return acos(calfa);
}

struct recta{
	punto u,v;
	recta() {}
	recta(punto u, punto v): u(u), v(v) {}
	long double tam() {
		long double den = (u-v)%(w-O);
		if (cmp(den)==0) return -1e100;
		long double t = (u-O)%(w-O) / den; //solucion de u+(v-u)t-O paralelo a (w-O)
		if (cmp(t,0)<0 || cmp(t,1) > 0) return -1e100;
		punto p = (u-O) + (v-u)*t;
		if ( p*(w-O) < 0) return -1e100;//cmp no es necesario porque no puede ser 0
		return p.tam();
	}
};
bool operator<(recta r1, recta r2) {
	return r1.tam() < r2.tam();
}
punto p[N];
recta r[N];

int main(){
	int S,K,W;
	while(scanf("%d%d%d", &S, &K, &W) == 3) {
		f(i,0,K) p[i].read();

		f(i,0,W) {
			punto u,v;
			u.read(); v.read();
			r[i] = recta(u,v);
		}
		if (K == 1) {
			cout << 0 << endl;
			continue;
		}
		
		f(i,0,S) {
			int res = 0;
			O = p[i];
			vector<superpunto> L;
			f(j,0,K) if(j!=i) L.pb(superpunto(p[j], -1));
			f(j,0,W) {
				long double tmp = (r[j].u-O) % (r[j].v-O);
				if (tmp < 0) swap(r[j].u, r[j].v);
				L.pb( superpunto(r[j].u, j*2) );
				L.pb( superpunto(r[j].v, j*2+1) );
			}
			sort(all(L), ordenCircular2);

			set<recta> R;
			w = L[0].p;
			f(j,0,W) {
				if (r[j].tam() > 0) R.insert(r[j]);
			}
			
			f(j,0,L.size()) {
				int z = L[j].z;
				w = L[j].p;
				if(z<0) {
					if (R.empty()) {
						res++;
						continue;
					}
					recta pr = *R.begin();
					if (pr.tam() > (w-O).tam()) res++;
				} else if (z%2 == 0) R.insert(r[z>>1]);
				else R.erase(r[z>>1]);
			}
			cout << res << endl;
		}
	}
}
