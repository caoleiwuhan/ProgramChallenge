#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <string.h>
#include <cassert>
#include <iomanip>

using namespace std;

//#define _MY_DEBUG_

// 订单
struct Order
{
	int id;			// 订单号
	int time;		// 完成订单所需时间
	int punish;		// 罚款
	bool isServed;	// 是否被处理：似乎用不到
	Order() : id(0), time(0), punish(0), isServed(false)
	{}
	Order(int _id, int _time, int _punish, bool _isServed)
		: id(_id), time(_time), punish(_punish), isServed(_isServed)
	{
	}
};

// 存放订单
Order orders[1010];


/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process：处理每一组数据
*/
void Process();

/*
	排序函数：按照punish/time
*/
bool OrderCompare(Order o1, Order o2);


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
	string outputStr = "C:/Users/cao/Desktop/算法/要看的书/算法/2挑战编程/input/0000001.outp";
	ifstream fin;
	fin.open(inputStr);	

	cin.rdbuf(fin.rdbuf());	

	ofstream fout;
	fout.open(outputStr);
	//cout.rdbuf(fout.rdbuf());

#endif

	Process();
		
}

void Process()
{
	int count = 0;
	cin >> count;
	while (count--)
	{
		int num = 0;
		cin >> num;
		int id = 0;
		int time = 0;
		int punish = 0;
		while (num--)
		{
			cin >> time >> punish;
			Order o(id + 1, time, punish, false);
			orders[id] = o;
			++id;
		}

		sort(orders, orders + id, OrderCompare);

		//stable_sort(orders, orders + id, OrderCompare);

		for (int i = 0; i < id; ++i)
		{
			if (i != 0)
			{
				cout << ' ';
			}
			cout << orders[i].id;
		}
		cout << endl;


		if (count)
		{
			cout << endl;
		}
	}

}

bool OrderCompare(Order o1, Order o2)
{
	double d1 = (double)o1.punish / o1.time;
	double d2 = (double)o2.punish / o2.time;
	return (d1 > d2);
}