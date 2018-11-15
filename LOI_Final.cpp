//============================================================================
// Name        : LOI-code2.cpp
// Author      : Tapan Modi
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>


using namespace std;

#define pb push_back
#define mp make_pair
#define F first
#define S second

#define MAXN 2000
#define MAXM 2000

pair<int,int> vis[2][MAXN][MAXM];
int trace[MAXN][MAXM];
map<pair<int,int>,pair<int,int>> mpp, storeSize;
map<pair<int,int>, vector<pair<int,int>>> closed_bases, stretched_bases;
bool v[MAXN][MAXN];

void solve(int x, int y, int n, int m, int tx, int ty) {
	if(n <= 10 && m <= 10) {
		vector<pair<int,int>> base;

		if(x == 0 && y == 0) {
			if(n <= m) {
				base = closed_bases[mp(n,m)];
				vis[0][x + base[base.size() - 1].F][y + base[base.size() - 1].S] = mp(x + base[0].F, y + base[0].S);
				vis[1][x + base[0].F][y + base[0].S] = mp(x + base[base.size() - 1].F, y + base[base.size() - 1].S);
				for(int i = 0; i < (int)base.size() - 1;i++) {
					vis[0][x + base[i].F][y + base[i].S] = mp(x + base[i + 1].F, y + base[i + 1].S);
					vis[1][x + base[i + 1].F][y + base[i + 1].S] = mp(x + base[i].F, y + base[i].S);
				}
			}
			else {
				base = closed_bases[mp(m,n)];
				vis[0][x + base[base.size() - 1].S][y + base[base.size() - 1].F] = mp(x + base[0].S, y + base[0].F);
				vis[1][x + base[0].S][y + base[0].F] = mp(x + base[base.size() - 1].S, y + base[base.size() - 1].F);
				for(int i = 0; i < (int)base.size() - 1;i++) {
					vis[0][x + base[i].S][y + base[i].F] = mp(x + base[i + 1].S, y + base[i + 1].F);
					vis[1][x + base[i + 1].S][y + base[i + 1].F] = mp(x + base[i].S, y + base[i].F);
				}
			}
		}
		else {
			if(x != tx || y != ty) {
				base = stretched_bases[mp(n,m)];
				for(int i = 0; i < (int)base.size() - 1;i++) {
					vis[0][x + base[i].F][y + base[i].S] = mp(x + base[i + 1].F, y + base[i + 1].S);
					vis[1][x + base[i + 1].F][y + base[i + 1].S] = mp(x + base[i].F, y + base[i].S);
				}
			}
			else {
				base = stretched_bases[mp(m,n)];
				for(int i = 0; i < (int)base.size() - 1;i++) {
					vis[0][x + base[i].S][y + base[i].F] = mp(x + base[i + 1].S, y + base[i + 1].F);
					vis[1][x + base[i + 1].S][y + base[i + 1].F] = mp(x + base[i].S, y + base[i].F);
				}
			}
		}
		return;
	}

	if(n <= 10) {
		int halve_y = (m / 4) * 2 + (m % 2);
		int side3 = halve_y;
		int side4 = m - halve_y;
		mpp[mp(x, y + side3 - 2)] = mp(x + 1, y + side3);
		mpp[mp(x + 1, y + side3)] = mp(x, y + side3 - 2);

		mpp[mp(x + 2, y + side3 - 1)] = mp(x, y + side3);
		mpp[mp(x, y + side3)] = mp(x + 2, y + side3 - 1);
		solve(x, y, n, side3, tx, ty);
		solve(x, y + side3, n, side4, tx, ty);
		return;
	}
	int halve_x = (n / 4) * 2 + (n % 2);
	int halve_y = (m / 4) * 2 + (m % 2);
	int side1 = halve_x, side2 = n - halve_x, side3 = halve_y, side4 = m - halve_y;

	mpp[mp(x, y + side3 - 2)] = mp(x + 1, y + side3);
	mpp[mp(x + 1, y + side3)] = mp(x, y + side3 - 2);

	mpp[mp(x + 2, y + side3 - 1)] = mp(x, y + side3);
	mpp[mp(x, y + side3)] = mp(x + 2, y + side3 - 1);

	mpp[mp(x + side1, y + side3 - 2)] = mp(x + 1 + side1, y + side3);
	mpp[mp(x + 1 + side1, y + side3)] = mp(x + side1, y + side3 - 2);

	mpp[mp(x + 2 + side1, y + side3 - 1)] = mp(x + side1, y + side3);
	mpp[mp(x + side1, y + side3)] = mp(x + 2 + side1, y + side3 - 1);


	mpp[mp(x + side1 - 2, y)] = mp(x + side1, y + 1);
	mpp[mp(x + side1, y + 1)] = mp(x + side1 - 2, y);

	mpp[mp(x + side1 - 1, y + 2)] = mp(x + side1, y);
	mpp[mp(x + side1, y)] = mp(x + side1 - 1, y + 2);

	if(tx == -1){
		tx = side1;
		ty = y;
	}

	solve(x, y, side1, side3, tx, ty);
	solve(x + side1, y, side2, side3, x + side1, y);
	solve(x, y + side3, side1, side4, tx, ty);
	solve(x + side1, y + side3, side2, side4, tx, ty);
}

void traverseChess(int x, int y, int n, int m) {
	int tx = x, ty = y;
	int cnt = 0;
	int flag = 0;
	while(cnt < n * m) {
		trace[tx][ty] = ++cnt;
		cout << cnt << " " << tx << " " << ty << endl;
		v[tx][ty] = true;
		if(vis[flag][tx][ty] == mp(x,y))
			break;
		if(mpp.count(mp(tx,ty)) && !v[mpp[mp(tx,ty)].F][mpp[mp(tx,ty)].S]) {
			vis[flag][tx][ty] = mpp[mp(tx,ty)];
		}
		else if(vis[flag][tx][ty] == mp(-1,-1) ||
				v[vis[flag][tx][ty].F][vis[flag][tx][ty].S])
			flag = (flag == 0) ? 1 : 0;
		int txx = tx;
		tx = vis[flag][tx][ty].F;
		ty = vis[flag][txx][ty].S;
	}
}

string closedBaseNames[] = {"5_6","5_8","5_10","6_6","6_7","6_8","6_9","6_10","7_8","7_10","8_8","8_9","8_10",
						"9_10", "10_10"};

string stretchedBaseNames[] = {"5_6","5_8","5_10","6_6","6_8","6_10","7_6","7_8","7_10","8_6","8_8","8_10",
									"9_6","9_8","9_10","10_6","10_8","10_10"};

int x[] = {5, 5, 5, 6, 6, 6, 6, 6, 7, 7, 8, 8, 8, 9, 10};
int y[] = {6, 8, 10, 6, 7, 8, 9, 10, 8, 10, 8, 9, 10, 10, 10};

int xx[] = {5, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9, 10, 10, 10};
int yy[] = {6, 8, 10, 6, 8, 10, 6, 8, 10, 6, 8, 10, 6, 8, 10, 6, 8, 10};

void printStretched(int n, int m) {
	int cnt = 1;
	int tr[n][m];
	for(auto it : stretched_bases[mp(n,m)]) {
		tr[it.F][it.S] = cnt++;
	}
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++)
			printf("%d\t", tr[i][j]);
		printf("\n");
	}
}

void printClosed(int n, int m) {
	int cnt = 1;
	int tr[n][m];
	for(auto it : closed_bases[mp(n,m)]) {
		tr[it.F][it.S] = cnt++;
	}
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++)
			printf("%d\t", tr[i][j]);
		printf("\n");
	}
}

int main() {

	FILE * fp;

	for(int i = 0; i < 15; i++) {

		string fileName = closedBaseNames[i] + "_closed.txt";
		fp = fopen(fileName.c_str(),"r");
		if(!fp) continue;
		int dim = x[i] * y[i];
		for(int j = 0; j < dim; j++){
			int a, b;
			fscanf(fp,"%d %d",&a,&b);
			closed_bases[mp(x[i],y[i])].pb(mp(a, b));
		}
		fclose(fp);
	}

	for(int i = 0; i < 18; i++) {

		string fileName = stretchedBaseNames[i] + "_stretched.txt";
		fp = fopen(fileName.c_str(),"r");
		if(!fp) continue;
		int dim = xx[i] * yy[i];
		for(int j = 0; j < dim; j++){
			int a, b;
			fscanf(fp,"%d %d",&a,&b);
			stretched_bases[mp(xx[i],yy[i])].pb(mp(a, b));
		}
		fclose(fp);
	}

	int x = 2, y = 5;
	int n = 13;
	int m = 50;
	cin >> n >> m >> x >> y;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++)
			vis[0][i][j] = vis[1][i][j] = mp(-1, -1);
	}

	solve(0, 0, n, m, -1, -1);
	traverseChess(x, y, n, m);
	return 0;
}

