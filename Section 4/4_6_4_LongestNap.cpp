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
	û���ǣ�
		1.����Ϊ0
		// �ύ���󣡣��������Ҳ�ܳ���������
*/	

//#define _MY_DEBUG_

// ʱ��ṹ
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

// �¼��ṹ
struct Event
{
	MyTime sTime;	// ��ʼʱ��
	MyTime eTime;	// ����ʱ��
};

/*
	����str���õ���ʼʱ�䣬����ʱ��
*/
void ParseTime(string str, Event &e);


/*
	MainStructure: ���ṹ
*/
void MainStructure();

/*
	Process������ÿһ������
*/
void Process();

/*
	�¼���������
*/
bool EventStartCompare(const Event &e1, const Event &e2);

/*
	����vector���ҵ����napʱ��
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
	string inputStr = "C:/Users/cao/Desktop/�㷨/Ҫ������/�㷨/2��ս���/input/1.inp";
	//string inputStr = "D:/2��ս���/input/110205.inp";
	string outputStr = "C:/Users/cao/Desktop/�㷨/Ҫ������/�㷨/2��ս���/input/0000001.outp";
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
	// ��������
	int count = 0;
	// ÿ�����ݵ��¼���
	int num = 0;
	// �¼�����
	vector<Event> events;
	while (cin >> num)
	{
		// ȥ�����ֺ���Ļ��з�
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
		// ����
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
	// ʱ
	ss >> num1;
	// :
	ss >> ch;
	// ��
	ss >> num2;
	e.sTime.hour = num1;
	e.sTime.minute = num2;	
	e.sTime.total = num1 * 60 + num2;
	// ʱ
	ss >> num1;
	// :
	ss >> ch;
	// ��
	ss >> num2;
	e.eTime.hour = num1;
	e.eTime.minute = num2;
	e.eTime.total = num1 * 60 + num2;
}

bool EventStartCompare(const Event &e1, const Event &e2)
{
	//int minutes1 = e1.sTime.hour * 60 + e1.sTime.minute;
	//int minutes2 = e2.sTime.hour * 60 + e2.sTime.minute;
	// �Կ�ʼʱ��Ϊ׼���򣬿�ʼ��Ϊ��
	//if (e1.sTime.total != e2.sTime.total)
	//{
	//	return (e1.sTime.total < e2.sTime.total);
	//}
	//// �����ʼʱ����ͬ���Խ���ʱ����Ϊ��
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
	// �����һ������0
	if (e1.sTime.total != start.total)
	{
		max = e1.sTime.total - start.total;
		end = e1.sTime;
	}
	for (int i = 1; i < count; ++i)
	{
		// ��i�Ŀ�ʼʱ���ȥi-1�Ľ���ʱ��
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

