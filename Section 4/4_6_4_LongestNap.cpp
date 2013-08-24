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

/*	
	没考虑：
		1.输入为0
		// 提交错误！！！这错误也能出啊！！！
*/	

//#define _MY_DEBUG_

// 时间结构
struct MyTime
{
	int hour;
	int minute;
	int total;

	MyTime & operator= (MyTime &t)
	{
		if (this == &t)
		{
			return *this;
		}
		hour = t.hour;
		minute = t.minute;
		total = t.total;
		return *this;
	}
};

// 事件结构
struct Event
{
	MyTime sTime;	// 开始时间
	MyTime eTime;	// 结束时间
};

/*
	解析str，得到开始时间，结束时间
*/
void ParseTime(string str, Event &e);


/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process：处理每一组数据
*/
void Process();

/*
	事件的排序函数
*/
bool EventStartCompare(const Event &e1, const Event &e2);

/*
	遍历vector，找到最长的nap时间
*/
int LongestNap(vector<Event> & events, MyTime &start, MyTime &end);
	

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

	/*ofstream fout;
	fout.open(outputStr);
*/
	//cout.rdbuf(fout.rdbuf());

#endif

	Process();
		
}

void Process()
{
	// 数据组数
	int count = 0;
	// 每组数据的事件数
	int num = 0;
	// 事件数组
	vector<Event> events;
	while (cin >> num)
	{
		// 去掉数字后面的换行符
		cin.get();
		events.clear();
		++count;
		while (num--)
		{			
			string str;
			getline(cin, str);
			Event e;
			ParseTime(str, e);
			events.push_back(e);
		}
		// 排序
		sort(events.begin(), events.end(), EventStartCompare);
		MyTime start, end;
		int total = LongestNap(events, start, end);
		if (total >= 60)
		{
			cout << "Day #" << count << ": the longest nap starts at " 
				<< start.hour << ":" << setfill('0') << setw(2) << start.minute 
				<< " and will last for " 
				<< total / 60 << " hours and " << (total % 60) << " minutes." << endl;
		}
		else
		{
			cout << "Day #" << count << ": the longest nap starts at " 
				<< start.hour << ":" << setfill('0') << setw(2) << start.minute 
				<< " and will last for " 
				<< (total % 60) << " minutes." << endl;
		}
	}
}


void ParseTime(string str, Event &e)
{ // 10:00 12:00 Lectures [10, 18], [0, 60)
	stringstream ss(str);
	int num1;
	int num2;
	char ch;
	// 时
	ss >> num1;
	// :
	ss >> ch;
	// 分
	ss >> num2;
	e.sTime.hour = num1;
	e.sTime.minute = num2;	
	e.sTime.total = num1 * 60 + num2;
	// 时
	ss >> num1;
	// :
	ss >> ch;
	// 分
	ss >> num2;
	e.eTime.hour = num1;
	e.eTime.minute = num2;
	e.eTime.total = num1 * 60 + num2;
}

bool EventStartCompare(const Event &e1, const Event &e2)
{
	//int minutes1 = e1.sTime.hour * 60 + e1.sTime.minute;
	//int minutes2 = e2.sTime.hour * 60 + e2.sTime.minute;
	// 以开始时间为准排序，开始早为先
	//if (e1.sTime.total != e2.sTime.total)
	//{
	//	return (e1.sTime.total < e2.sTime.total);
	//}
	//// 如果开始时间相同，以结束时间早为先
	//return (e1.eTime.total < e2.eTime.total);
	return (e1.sTime.total < e2.sTime.total);
}

int LongestNap(vector<Event> & events, MyTime &start, MyTime &end)
{
	int count = events.size();
	int max = 0;
	
	start.hour = 10;
	start.minute = 0;
	start.total = 10 * 60;
	if (events.size() == 0)
	{
		return (8 * 60);
	}

	Event e1 = events[0];
	// 如果第一个不是0
	if (e1.sTime.total != start.total)
	{
		max = e1.sTime.total - start.total;
		end = e1.sTime;
	}
	for (int i = 1; i < count; ++i)
	{
		// 用i的开始时间减去i-1的结束时间
		int tmp = events[i].sTime.total - events[i - 1].eTime.total;
		if (tmp > max)
		{
			max = tmp;
			start = events[i - 1].eTime;
			end = events[i].sTime;
		}
	}
	if (events[count - 1].eTime.total != 18 * 60)
	{
		int tmp = 18 * 60 - events[count - 1].eTime.total;
		if (tmp > max)
		{
			max = tmp;
			start = events[count - 1].eTime;
			end.hour = 18;
			end.minute = 0;
			end.total = 18 * 60;
		}
	}
	return max;
}

