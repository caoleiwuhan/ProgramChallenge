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

const int MAXV = 201;
const int MAXDEGREE = 201;

bool processed[MAXV];
bool discovered[MAXV];
int parent[MAXV];

bool color[MAXV];

struct graph
{
	int edges[MAXV + 1][MAXDEGREE];
	int degree[MAXV + 1];
	int nvertices;
	int nedges;
};

void initialize_graph(graph *g);


void insert_edge(graph *g, int e1, int e2, bool directed);


void initialize_graph(graph *g)
{
	g->nvertices = 0;
	g->nedges = 0;
	for (int i = 0; i <= MAXV; ++i)
	{
		g->degree[i] = 0;
	}
}

void insert_edge(graph *g, int e1, int e2, bool directed)
{
	if (g->degree[e1] > MAXDEGREE)
	{
		cout << "Warning:edge insert" << endl;
	}
	g->edges[e1][g->degree[e1]++] = e2;

	if (directed == false)
	{
		insert_edge(g, e2, e1, true);
	}
	else
	{
		g->nedges++;
	}
}


bool BFS_Color(graph *g, int start);

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
	int nVertex = 0;
	while (cin >> nVertex)
	{
		if (nVertex == 0)
		{
			break;
		}
		graph g;
		initialize_graph(&g);
		g.nvertices = nVertex;

		int nEdges = 0;
		cin >> nEdges;
		int e1, e2;
		for (int i = 1; i <= nEdges; ++i)
		{
			cin >> e1 >> e2;
			insert_edge(&g, e1, e2, false);
		}
		if (BFS_Color(&g, 0))
		{
			cout << "BICOLORABLE." << endl;
		}
		else
		{
			cout << "NOT BICOLORABLE." << endl;
		}
	}		
}

bool BFS_Color(graph *g, int start)
{
	memset(color, 0, sizeof(color));
	memset(discovered, 0, sizeof(discovered));
	memset(processed, 0, sizeof(processed));

	queue<int> q;
	q.push(start);
	discovered[start] = true;
	color[start] = true;

	while (!q.empty())
	{
		int cur = q.front();
		q.pop();
		processed[cur] = true;

		for (int i = 0; i < g->degree[cur]; ++i)
		{
			int v2 = g->edges[cur][i];
			if (!discovered[v2])
			{
				discovered[v2] = true;
				q.push(v2);
				parent[v2] = cur;
				color[v2] = !color[cur];
			}
			else
			{
				if (color[v2] == color[cur])
				{
					return false;
				}
			}
		}
	}

	return true;
}