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

static const unsigned int Grid6_6[6][6][2] =
{
    {{4,5}, {5,6}, {4,7}, {4,7}, {5,7}, {6,7}},
    {{3,4}, {3,6}, {0,3}, {3,5}, {0,6}, {0,7}},
    {{2,5}, {1,4}, {0,1}, {3,4}, {2,5}, {1,6}},
    {{2,5}, {5,6}, {4,7}, {0,2}, {1,5}, {0,6}},
    {{3,4}, {1,4}, {4,7}, {4,7}, {0,2}, {1,7}},
    {{2,3}, {1,3}, {1,0}, {3,0}, {0,2}, {0,1}}
};

static const unsigned int Grid6_8[6][8][2] =
{
    {{4,5}, {4,6}, {4,7}, {4,7}, {4,6}, {4,6}, {5,7}, {6,7}},
    {{3,4}, {3,6}, {6,0}, {0,4}, {0,3}, {0,3}, {0,5}, {0,7}},
    {{2,5}, {1,4}, {0,5}, {2,5}, {2,5}, {0,3}, {2,5}, {1,6}},
    {{2,5}, {2,6}, {6,7}, {0,6}, {6,7}, {5,6}, {5,7}, {1,6}},
    {{3,4}, {1,4}, {3,7}, {1,4}, {1,3}, {1,4}, {2,7}, {1,7}},
    {{2,3}, {1,2}, {0,2}, {0,2}, {2,3}, {0,3}, {1,2}, {0,1}}
};

static const unsigned int Grid8_8[8][8][2] =
{
    {{4,5}, {5,6}, {5,7}, {4,7}, {5,7}, {4,7}, {5,7}, {6,7}},
    {{3,5}, {3,6}, {0,3}, {3,6}, {3,6}, {0,3}, {5,6}, {0,7}},
    {{2,5}, {1,6}, {1,7}, {1,5}, {4,5}, {1,3}, {2,5}, {1,6}},
    {{2,3}, {1,5}, {2,5}, {2,4}, {6,7}, {2,4}, {0,5}, {1,6}},
    {{2,5}, {1,6}, {3,7}, {4,5}, {1,6}, {0,1}, {2,5}, {0,1}},
    {{3,5}, {5,6}, {1,4}, {1,2}, {4,5}, {0,5}, {2,5}, {1,6}},
    {{2,4}, {1,4}, {4,7}, {2,7}, {0,1}, {4,7}, {0,7}, {1,7}},
    {{2,3}, {1,3}, {0,1}, {0,3}, {0,3}, {1,3}, {1,2}, {0,1}}
};

static const unsigned int Grid8_10[8][10][2] =
{
    {{4,5}, {4,6}, {4,7}, {4,7}, {4,7}, {6,7}, {4,7}, {4,7}, {5,7}, {6,7}},
    {{3,4}, {3,6}, {0,3}, {0,3}, {0,3}, {0,3}, {0,3}, {3,4}, {0,5}, {0,6}},
    {{2,4}, {1,6}, {0,6}, {6,7}, {2,4}, {4,6}, {5,7}, {5,6}, {2,5}, {0,1}},
    {{2,5}, {3,5}, {0,5}, {4,6}, {3,5}, {5,7}, {0,4}, {0,7}, {2,5}, {1,7}},
    {{2,5}, {2,6}, {2,7}, {3,5}, {2,4}, {0,3}, {2,7}, {1,3}, {0,1}, {1,6}},
    {{3,5}, {1,6}, {1,2}, {1,6}, {3,5}, {1,7}, {0,1}, {4,5}, {5,7}, {1,6}},
    {{2,4}, {1,4}, {4,7}, {3,7}, {1,4}, {4,7}, {3,7}, {4,7}, {2,7}, {0,7}},
    {{2,3}, {1,3}, {0,2}, {0,3}, {0,3}, {1,3}, {0,3}, {0,3}, {1,2}, {0,1}}
};

static const unsigned int Grid10_10[10][10][2] =
{
    {{4,5}, {4,6}, {5,7}, {4,6}, {4,7}, {6,7}, {5,7}, {4,7}, {5,7}, {6,7}},
    {{3,4}, {4,6}, {0,3}, {0,3}, {3,5}, {0,3}, {0,3}, {3,4}, {5,6}, {6,0}},
    {{2,4}, {1,6}, {0,2}, {0,1}, {2,4}, {6,7}, {5,6}, {1,6}, {2,5}, {0,1}},
    {{2,4}, {5,6}, {0,6}, {3,5}, {4,5}, {1,4}, {0,4}, {2,6}, {2,5}, {1,6}},
    {{2,5}, {4,5}, {0,7}, {4,5}, {2,6}, {2,5}, {0,2}, {0,1}, {0,6}, {1,6}},
    {{2,3}, {2,6}, {1,7}, {0,5}, {1,7}, {0,1}, {2,6}, {6,7}, {2,6}, {1,7}},
    {{3,5}, {1,6}, {1,3}, {2,7}, {1,5}, {3,7}, {1,7}, {2,3}, {2,5}, {6,7}},
    {{2,5}, {3,6}, {5,6}, {3,7}, {1,3}, {2,7}, {2,6}, {2,3}, {5,6}, {6,7}},
    {{2,4}, {1,3}, {4,7}, {3,4}, {4,7}, {1,7}, {4,7}, {3,4}, {2,7}, {1,7}},
    {{2,3}, {1,2}, {0,3}, {1,3}, {0,3}, {0,2}, {0,3}, {2,3}, {0,2}, {0,1}}
};

static const unsigned int Grid10_12[10][12][2] =
{
    {{4,5}, {4,6}, {6,7}, {4,7}, {5,6}, {4,7}, {5,7}, {4,7}, {4,6}, {4,7}, {5,6}, {6,7}},
    {{3,5}, {3,6}, {0,7}, {0,3}, {3,6}, {0,3}, {6,7}, {0,3}, {5,6}, {0,3}, {0,5}, {0,6}},
    {{2,3}, {1,2}, {6,7}, {2,6}, {3,4}, {1,7}, {5,6}, {1,2}, {5,7}, {2,4}, {2,5}, {1,6}},
    {{2,3}, {1,6}, {4,5}, {2,3}, {4,7}, {2,7}, {0,3}, {2,7}, {5,7}, {1,6}, {2,5}, {0,1}},
    {{4,5}, {2,6}, {2,3}, {3,5}, {0,4}, {2,3}, {0,3}, {1,7}, {4,6}, {1,7}, {2,5}, {1,6}},
    {{2,4}, {4,5}, {0,7}, {1,6}, {4,6}, {3,6}, {0,7}, {3,6}, {2,5}, {1,6}, {0,7}, {1,6}},
    {{2,3}, {1,6}, {0,7}, {0,5}, {1,3}, {4,6}, {0,7}, {2,4}, {3,7}, {4,5}, {2,5}, {1,6}},
    {{3,5}, {5,6}, {1,2}, {2,7}, {2,3}, {5,6}, {2,3}, {0,5}, {2,7}, {0,1}, {2,5}, {0,6}},
    {{2,4}, {3,4}, {4,7}, {4,7}, {1,2}, {4,7}, {3,4}, {4,7}, {4,7}, {4,7}, {1,2}, {1,7}},
    {{2,3}, {1,3}, {0,1}, {0,3}, {0,2}, {0,3}, {1,3}, {0,3}, {0,1}, {0,3}, {0,2}, {0,1}}
};

static const int offsetDirArr[8][2] =
{{-2,-1}, {-1,-2}, {1,-2}, {2,-1}, {2, 1}, {1, 2}, {-1,2}, {-2,1}};

bool vis[MAXN][MAXM];
int trace[MAXN][MAXM];
map<pair<int,int>,pair<int,int>> mpp, storeSize;
pair<int,int> gridDim[MAXN][MAXN], offset[MAXN][MAXN];

void solve(int x, int y, int n, int m) {
	if(n < 12 || m < 12)
		return;
	int halve_x = n / 2;
	int halve_y = m / 2;
	int side1 = halve_x, side2 = halve_x, side3 = halve_y, side4 = halve_y;
	if(halve_x % 2){
		side1 = halve_x - 1;
		side2 = halve_x + 1;
	}
	if(halve_y % 2) {
		side3 = halve_y - 1;
		side4 = halve_y + 1;
	}
	pair<int,int> q1 = {side1 - 1 + x, side3 - 1 + y};
	pair<int,int> q2 = {q1.F + 1, q1.S};
	pair<int,int> q3 = {q1.F, q1.S + 1};
	pair<int,int> q4 = {q1.F + 1, q1.S + 1};


	mpp[mp(q1.F - 1, q1.S)] = mp(q3.F - 2, q3.S + 1);
	mpp[mp(q3.F - 2, q3.S + 1)] = mp(q1.F - 1, q1.S);

	mpp[q3] = mp(q4.F, q4.S + 2);
	mpp[mp(q4.F, q4.S + 2)] = q3;

	mpp[mp(q4.F + 1, q4.S)] = mp(q2.F + 2, q2.S - 1);
	mpp[mp(q2.F + 2, q2.S - 1)] = mp(q4.F + 1, q4.S);

	mpp[q2] = mp(q1.F, q1.S - 2);
	mpp[mp(q1.F, q1.S - 2)] = q2;

	storeSize[mp(x, y)] = mp(side1, side3);
	storeSize[mp(x + side1, y)] = mp(side2, side3);
	storeSize[mp(x, y + side3)] = mp(side1, side4);
	storeSize[mp(q4.F, q4.S)] = mp(side2, side4);

//	cout << q1.F << " " << q1.S << endl;
//	cout << q2.F << " " << q2.S << endl;
//	cout << q3.F << " " << q3.S << endl;
//	cout << q4.F << " " << q4.S << endl;
//	cout << x << "  " << y << " " << n << " ++ " << m << " "
//			<< side1 << " " << side2 << " " << side3 << " " << side4 << endl;
//	cout << x << " " << y << endl;
//	cout << side1 << " " << y<< endl;
//	cout << x << " " << side3 << endl;
//	cout << q4.F << " " << q4.S << endl;
//	cout << endl;

//	cout << mpp[q2].F << "**" << mpp[q2].S  << " " << q1.F << "  " << q1.S<< endl;
	solve(x, y, side1, side3);
	solve(x + side1, y, side2, side3);
	solve(x, y + side3, side1, side4);
	solve(q4.F, q4.S, side2, side4);
}

void traverseChess(int x, int y, int n) {

	for(auto it : storeSize){
		for(int i = it.F.F; i < it.F.F + it.S.F; i++) {
			for(int j = it.F.S; j < it.F.S + it.S.S; j++){
				offset[i][j] = it.F;
				gridDim[i][j] = it.S;
			}
		}
	}

	int i = 0;
	int offset_x, offset_y;
	bool f = 0;
	while(1) {
		trace[x][y] = ++i;
		cout << i << " " << x << " " << y << endl;
		vis[x][y] = true;
		offset_x = offset[x][y].F;
		offset_y = offset[x][y].S;
		const unsigned int *p = (gridDim[x][y] == mp(8, 6)) ? Grid6_8[y - offset_y][x - offset_x]:
								(gridDim[x][y] == mp(6, 8)) ? Grid6_8[x - offset_x][y - offset_y]:
								(gridDim[x][y] == mp(10, 8)) ? Grid8_10[y - offset_y][x - offset_x]:
								(gridDim[x][y] == mp(8, 10)) ? Grid8_10[x - offset_x][y - offset_y]:
								(gridDim[x][y] == mp(12, 10)) ? Grid10_12[y - offset_y][x - offset_x]:
								(gridDim[x][y] == mp(10, 12)) ? Grid10_12[x - offset_x][y - offset_y]:
								(gridDim[x][y] == mp(6, 6)) ? Grid6_6[x - offset_x][y - offset_y]:
								(gridDim[x][y] == mp(8, 8)) ? Grid8_8[x - offset_x][y - offset_y]:
								 Grid10_10[x - offset_x][y - offset_y];



		bool shouldReverse = false;
		if(gridDim[x][y].F > gridDim[x][y].S)
			shouldReverse = true;
//		cout << i << " " << x - offset_x << " " << y - offset_y << " " << gridDim[x][y].F
//				<< " " << gridDim[x][y].S << " " << p[0] << "  " << p[1] << " " <<  shouldReverse << endl;
		unsigned int next_a = p[0];
		unsigned int next_b = p[1];

		if(shouldReverse) {
//			cout << next_a << " " << next_b << endl;
			next_a = (9 - next_a) % 8;
			next_b = (9 - next_b) % 8;
//			cout << next_a << " " << next_b << endl;
		}

		const int *dir1 = offsetDirArr[next_a];
		const int *dir2 = offsetDirArr[next_b];
		if(mpp.count(mp(x, y)) && !vis[mpp[mp(x, y)].F][mpp[mp(x, y)].S]){
			int tx = mpp[mp(x, y)].F;
			int ty = mpp[mp(x, y)].S;
			f = 1;
			x = tx;
			y = ty;
		}
		else if(!f){
			if(!vis[x + dir1[1]][y + dir1[0]]){
						x = x + dir1[1];
						y = y + dir1[0];
			}
			else if(!vis[x + dir2[1]][y + dir2[0]]){
				x = x + dir2[1];
				y = y + dir2[0];

			}
			else
				break;
		}
		else{
			if(!vis[x + dir1[1]][y + dir1[0]] && !mpp.count(mp(x + dir1[1], y + dir1[0]))){
				x = x + dir1[1];
				y = y + dir1[0];
				f = 0;
			}
			else if(!vis[x + dir2[1]][y + dir2[0]] && !mpp.count(mp(x + dir2[1], y + dir2[0]))){
				x = x + dir2[1];
				y = y + dir2[0];
				f = 0;
			}
			else
				break;
		}
	}
/*
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++){
			cout << trace[i][j] << "\t";
		}
		cout << endl;
	}*/
}


int main() {

	int x = 5, y = 4;
//	cin >> x >> y;
	int n = 8;
	cin >> x >> y >> n;

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++)
			gridDim[i][j] = mp(n, n);
	}

	solve(0, 0, n, n);
//	cout << storeSize.size() << endl;
//	for(auto it : storeSize){
//		cout << it.F.F << " " << it.F.S << " -> " << it.S.F << " " << it.S.S << endl;
//	}
	traverseChess(x, y, n);
//	perr();
	return 0;
}

