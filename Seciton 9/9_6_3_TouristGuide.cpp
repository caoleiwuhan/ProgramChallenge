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
	// ��
	int edges[MAXV][MAXDEGREE];
	// Ȩ
	int dist[MAXV][MAXDEGREE];
	// ��
	int degree[MAXV];
	// ������
	int nvertices;
	// ����
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
	MainStructure: ���ṹ
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
	string inputStr = "C:/Users/cao/Desktop/�㷨/Ҫ������/�㷨/2��ս���/input/1.inp";
	//string inputStr = "D:/2��ս���/input/110205.inp";
	string outputStr = "C:/Users/cao/Desktop/�㷨/Ҫ������/�㷨/2��ս���/input/1.outp";
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
	// ������
	int nVer = 0;
	// ����
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
		// ��ʼ��
		
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
	// ����start�����б�
	for (int i = 0; i < g->degree[start]; ++i)
	{
		int e2 = g->edges[start][i];
		//// ���e2�Ѿ��������
		//if (processed[e2])
		//{
		//	continue;
		//}
		if (e2 == parent[start] || e2 == from)
		{
			continue;
		}

		// ���e2�Ѿ������֣�����û������
		if (!discovered[e2])
		{
			discovered[e2] = true;
			// ����ȡ��Сֵ:cur��ʾ�ӿ�ʼ�㵽��ǰ������ͨ·ֵ
			int tmp = g->dist[start][i] > cur ? cur : g->dist[start][i];
			minDist[e2] = tmp;
			parent[e2] = start;
			dfs(g, e2, to, tmp);
		}
		else
		{ // ����Ѿ������֣��Ƚ����ߵ����ֵ :ͨ��start�ܻ�õ����ֵ
			int tmp = g->dist[start][i] > minDist[start] ? minDist[start] : g->dist[start][i];
			
			// ����µıȽϴ󣬸���
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