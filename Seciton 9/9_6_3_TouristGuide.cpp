#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <string>
#include <cstring>
#include <fstream>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <queue>


using namespace std;

//#define _MY_DEBUG_

const int MAXV = 101;
const int MAXDEGREE = 101;

bool processed[MAXV];
bool discovered[MAXV];
int parent[MAXV];

int minDist[MAXV];

int from;
int to;
int nPeople;

struct graph
{
	// 边
	int edges[MAXV][MAXDEGREE];
	// 权
	int dist[MAXV][MAXDEGREE];
	// 度
	int degree[MAXV];
	// 顶点数
	int nvertices;
	// 边数
	int nedges;
};

void initialize_graph(graph *g);

void read_graph(graph *g, bool directed);

void insert_edge(graph *g, int e1, int e2, int dis, bool directed);

void dfs(graph *g, int start, int to, int cur);

void initialize_dfs();

void initialize_graph(graph *g)
{
	g->nvertices = 0;
	g->nedges = 0;
	for (int i = 0; i <= MAXV; ++i)
	{
		g->degree[i] = 0;
	}
}

void read_graph(graph *g, bool directed)
{
	int e1, e2, dis;
	for (int i = 1; i <= g->nedges; ++i)
	{
		cin >> e1 >> e2 >> dis;
		insert_edge(g, e1, e2, dis, directed);
	}	
}

void insert_edge(graph *g, int e1, int e2, int dis, bool directed)
{
	g->edges[e1][g->degree[e1]] = e2;
	g->dist[e1][g->degree[e1]] = dis;
	++g->degree[e1];

	if (directed == false)
	{
		insert_edge(g, e2, e1,  dis, true);
	}
}
//
//void dfs(graph *g, int start)
//{
//	if (finished)
//	{
//		return;
//	}
//
//	discovered[start] = true;
//	process_vertex(start);
//
//	for (int i = 0; i < g->degree[start]; ++i)
//	{
//		int v2 = g->edges[start][i];
//		if (valid_edge(v2))
//		{
//			if (!discovered[v2])
//			{
//				parent[v2] = start;
//				dfs(g, v2);
//			}
//			else
//			{
//				if (!processed[v2])
//				{
//					process_edge(start, v2);
//				}
//			}			
//		}
//		if (finished)
//		{
//			return;
//		}
//	}
//	processed[start] = true;
//}


/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process
*/
void Process();


int main()
{
	MainStructure();
	return 0;
}


void MainStructure()
{
	
#ifdef _MY_DEBUG_
	string inputStr = "C:/Users/cao/Desktop/算法/要看的书/算法/2挑战编程/input/1.inp";
	//string inputStr = "D:/2挑战编程/input/110205.inp";
	string outputStr = "C:/Users/cao/Desktop/算法/要看的书/算法/2挑战编程/input/1.outp";
	ifstream fin;
	fin.open(inputStr);		

	cin.rdbuf(fin.rdbuf());	

	/*
	ofstream fout;
	fout.open(outputStr.c_str());
	cout.rdbuf(fout.rdbuf());
	*/

#endif

	Process();
			
}
void Process()
{
	// 顶点数
	int nVer = 0;
	// 边数
	int nEdg = 0;
	int count = 1;
	while (cin >> nVer >> nEdg)
	{
		if (nVer == 0 && nEdg == 0)
		{
			break;
		}
		graph g;
		initialize_graph(&g);
		g.nvertices = nVer;
		g.nedges = nEdg;
		read_graph(&g, false);
		cin >> from >> to >> nPeople;
		// 初始化
		
		initialize_dfs();
		discovered[from] = true;
		minDist[from] = 0x7FFFFFFF;
		parent[from] = -1;

		dfs(&g, from, to, 0x7FFFFFFF);
		int num = minDist[to];
		--num;
		int nPath = nPeople / num;

		cout << "Scenario #" << count << endl;
		cout << "Minimum Number of Trips = ";
		/*if (from == to)
		{
			cout << 1 << endl;
		}
		else */if (nPath * num == nPeople)
		{
			cout << nPath << endl;
		}
		else
		{
			cout << (nPath + 1) << endl;
		}
		cout << endl;
		++count;
	}
}



void dfs(graph *g, int start, int to, int cur)
{
	if (start == to)
	{
		return;
	}
	// 遍历start的所有边
	for (int i = 0; i < g->degree[start]; ++i)
	{
		int e2 = g->edges[start][i];
		//// 如果e2已经被处理过
		//if (processed[e2])
		//{
		//	continue;
		//}
		if (e2 == parent[start] || e2 == from)
		{
			continue;
		}

		// 如果e2已经被发现，但还没被处理
		if (!discovered[e2])
		{
			discovered[e2] = true;
			// 两者取最小值:cur表示从开始点到当前点的最大通路值
			int tmp = g->dist[start][i] > cur ? cur : g->dist[start][i];
			minDist[e2] = tmp;
			parent[e2] = start;
			dfs(g, e2, to, tmp);
		}
		else
		{ // 如果已经被发现，比较两者的最大值 :通过start能获得的最好值
			int tmp = g->dist[start][i] > minDist[start] ? minDist[start] : g->dist[start][i];
			
			// 如果新的比较大，更新
			if (tmp > minDist[e2])
			{
				minDist[e2] = tmp;
				parent[e2] = start;
				dfs(g, e2, to, tmp);
			}			
		}
	}
	processed[start] = true;
}

void initialize_dfs()
{
	memset(discovered, 0, sizeof(discovered));
	memset(processed, 0, sizeof(processed));
	memset(parent, 0, sizeof(parent));
	memset(minDist, 0, sizeof(minDist));
	
}