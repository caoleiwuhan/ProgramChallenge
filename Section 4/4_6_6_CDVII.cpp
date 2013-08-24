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
#include <map>

using namespace std;

//#define _MY_DEBUG_

// һ����¼
struct Record
{
	int total;		// ʱ�䣺((day*24 + hour)*3600 + minute) 
	int hour;
	int minute;
	bool isEnter;
	int distance;

	Record() : total(0), hour(0), minute(0), isEnter(true), distance(0)
	{}
	Record(int _total, int _hour, int _minute, bool _isEnter, int _distance)
		:total(_total), hour(_hour), minute(_minute), isEnter(_isEnter), distance(_distance)
	{}
};

// ���name-records��¼��
map<string, vector<Record> * > recordMap;

// �ֶμ�ʱ����24
const int TIME_NUM = 24;
// �շ�����
int fee[TIME_NUM + 1];

/*
	MainStructure: ���ṹ
*/
void MainStructure();

/*
	Process������ÿһ������
*/
void Process();

/*
	����str������name
*/
string ParseStrRecord(string &str, Record &r);

/*
	�ȽϺ���
*/
bool RecordCompare(Record r1, Record r2);

/*
	���ݽ���ʱ�䣬����fee
*/


int main()
{
	MainStructure();
	return 0;
}


void MainStructure()
{
	
#ifdef _MY_DEBUG_
	string inputStr = "C:/Users/cao/Desktop/�㷨/Ҫ������/�㷨/2��ս���/input/1.inp";
	//string inputStr = "D:/2��ս���/input/1.inp";
	string outputStr = "C:/Users/cao/Desktop/�㷨/Ҫ������/�㷨/2��ս���/input/0000001.outp";
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
		recordMap.clear();

		// ����fee
		for (int i = 0; i < TIME_NUM; ++i)
		{
			cin >> fee[i];
		}
		// ȥ����β���з�
		cin.get();

		string str;
		while (getline(cin, str))
		{
			if (str == "")
			{
				break;
			}
			// ����str
			Record r;
			string name = ParseStrRecord(str, r);
			vector<Record> *pRecVec = recordMap[name];
			if (!pRecVec)
			{ // ��������name������vector
				pRecVec = new vector<Record>();
				recordMap[name] = pRecVec;
			}
			pRecVec->push_back(r);
		}

		// �Ƿ���Ҫ�������
		bool needEndl = false;

		// ���򣬲�����Ƿ���ԣ��������ԣ�ɾ��
		for (map<string, vector<Record> * >::iterator itr = recordMap.begin(); 
			itr != recordMap.end(); ++itr)
		{
			// ����
			sort(itr->second->begin(), itr->second->end(), RecordCompare);

			vector<Record> *pRecVec = itr->second;
			
			for (int i = 0; i < pRecVec->size(); ++i)
			{
				int num = pRecVec->size();
				if ((i + 1 < num) && pRecVec->at(i).isEnter && !pRecVec->at(i + 1).isEnter)
				{
					++i;
				}
				else
				{
					pRecVec->erase(pRecVec->begin() + i);
					--i;
				}
			}
			// ����
			int money = 0;
			for (int i = 0; i < pRecVec->size(); i += 2)
			{
				int index = pRecVec->at(i).hour;
				int difDis = abs(pRecVec->at(i).distance - pRecVec->at(i + 1).distance);
				money += 100;
				money += fee[index] * difDis;
			}
			if (pRecVec->size() > 0)
			{
				money += 200;
			}
			int zheng = money / 100;
			int xiao = money % 100;

			// ���ܲ��ǰ����ֵ������ģ�����
			if (money > 0)
			{
				cout << itr->first << " $" << zheng << "." 
					<< setw(2) << setfill('0') << xiao << endl;
				needEndl = true;
			}
		}
		// �ͷſռ�
		for (map<string, vector<Record> * >::iterator itr = recordMap.begin(); 
			itr != recordMap.end(); ++itr)
		{
			delete itr->second;
		}


		if (count && needEndl)
		{
			cout << endl;
		}
	}

}

string ParseStrRecord(string &str, Record &r)
{
	stringstream ss(str);
	string name;
	// ����name
	ss >> name;
	int month;
	int day;
	int hour;
	int minute;
	string strEnter; 
	char rawCh;
	ss >> month >> rawCh;	
	ss >> day >> rawCh;
	ss >> hour >> rawCh;
	ss >> minute;
	r.hour = hour;
	r.minute = minute;
	r.total = (day * 24 + hour) * 60 + minute;
	ss >> strEnter;
	if (strEnter == "exit")
	{
		r.isEnter = false;
	}
	else
	{
		r.isEnter = true;
	}
	ss >> r.distance;

	return name;
}


bool RecordCompare(Record r1, Record r2)
{
	return (r1.total < r2.total);
}