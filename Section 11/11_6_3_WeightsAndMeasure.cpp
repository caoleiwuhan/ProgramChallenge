#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <string>
#include <cstring>
#include <fstream>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <queue>
#include <hash_map>


using namespace std;

#define _MY_DEBUG_

const int MAXV = 5610;

int dp[MAXV][MAXV];
int weight[MAXV][MAXV];

struct Node
{
	int id;
	int weight;
	int measure;
	Node()
	{}

	Node(int _id, int _weight, int _measure)
		: id(_id), weight(_weight), measure(_measure)
	{}

};

Node mack[MAXV];

bool Cmp(const Node &n1, const Node &n2)
{
	if (n1.weight != n2.weight)
	{
		return (n1.weight < n2.weight);
	}
	else
	{
		return (n1.measure < n2.measure);
	}
}

/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process
*/
void Process();

int DP(int index);

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
	string str;
	int weight;
	int measure;
	int index = 0;
	while (getline(cin, str))
	{
		stringstream ss(str);
		ss >> weight >> measure;
		if (weight > measure)
		{
			continue;
		}

		Node n(index, weight, measure);
		mack[index++] = n;
	}
	sort(mack, mack + index, Cmp);
	
	int res = DP(index);
	cout << res << endl;
}

int DP(int index)
{
	int ans = 0;
	// dp[i][j]:长度为i，以j结尾
	memset(dp, 0, sizeof(dp));
	memset(weight, 0, sizeof(weight));

	for (int i = 1; i <= index; ++i)
	{
		dp[i][1] = 1;
		weight[i][1] = mack[0].weight;
	}
	for (int i = 1; i <= index; ++i)
	{
		for (int j = 2; j <= i; ++j)
		{
			int tmp = dp[i-1][j];
			weight[i][j] = weight[i-1][j];
			if (weight[i-1][j-1] + mack[j-1].weight <= mack[j-1].measure)
			{
				if (tmp < dp[i-1][j-1] + 1)
				{
					tmp = dp[i-1][j-1] + 1;
					weight[i][j] = weight[i-1][j-1] + mack[j-1].weight;
				}
			}
			dp[i][j] = tmp;
		}
		
	}
	for (int i = 1; i <= index; ++i)
	{
		if (dp[index][i] > ans)
		{
			ans = dp[index][i];
		}
	}

	return ans;
}