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
#include <string>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <climits>
#include <cctype>
#define SZ(x) ( (int) (x).size() )
#define me(x,a) memset(x,a,sizeof(x))
#define FN(a,n) for(int a=0;a<n;a++)
#define FOR(a,ini,fin) for(int a=(ini);a<(fin);a++)
#define sc1(x) scanf("%d",&x)
#define sc2(x,y) scanf("%d %d",&x,&y)
#define sc3(x,y,z) scanf("%d %d %d",&x,&y,&z)
#define all(v) v.begin(),v.end()
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define F first
#define S second
#define endl "\n"
#define MOD 1000000007
#define MAXN 100005
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;

int d[100]; // precios de cada político del partido d
int p[100]; // 			"							p
vector<int> adj[200]; // lista de adyacencia
bool vis[200];
int counterD[200];
int counterP[200];
int componentCost[200];

int memo[200][10001][2];

int dp(int i, int b, bool forD) {
	if (i == -1) return 0;
	int &res = memo[i][b][forD];
	if (res != -1) return res;
	res = dp(i - 1, b, forD);
	int ganancia = ((int)forD* 2 - 1)*(counterP[i] - counterD[i]);
	int presupuestoRestante = b - componentCost[i];
	if (ganancia > 0 && presupuestoRestante >= 0)
		res = max(res, ganancia + dp(i - 1, presupuestoRestante, forD));

	return res;
}

int main() {
	int D, P, R, B;

	while (sc2(D, P) == 2) {
		sc2(R, B);

		// limpiando
		FN (i, D + P) adj[i].clear();
		me(vis, 0);
		me(memo, -1);


		FN (i, D) {
			sc1(d[i]);
		}
		FN (i, P) {
			sc1(p[i]);
		}

		FN (i, R) {
			int a, b;
			sc2(a, b);
			a--; b--;
			adj[a].pb(b + D);
			adj[b + D].pb(a);
		}

		/*
		* Obteniendo las ganancias en cantidad de politicos para cada
		* componente conexa en cada partido
		*/
		int numberOfComponents = 0;
		FN (i, D + P) {
			if (!vis[i]) {

				int &cp = counterP[numberOfComponents];
				int &cd = counterD[numberOfComponents];
				int &cc = componentCost[numberOfComponents];
				cp = 0;
				cd = 0;
				cc = 0;

				numberOfComponents ++;

				stack<int> st;
				st.push(i);
				while(!st.empty()) {
					int node = st.top();
					st.pop();

					if (vis[node]) continue;

					vis[node] = 1;
					if (node >= D) {
						cp ++;
						cc += p[node - D];
					} else {
						cd ++;
						cc += d[node];
					}

					FN (j, SZ(adj[node])) {
						int son = adj[node][j];
						if (!vis[son]) {
							st.push(son);
						}
					}
				}

			}
		}

		int gananciaD = dp(numberOfComponents - 1, B, true);
		int gananciaP = dp(numberOfComponents - 1, B, false);

		printf("%d %d\n", (D + gananciaD), (P + gananciaP));

	}

}
