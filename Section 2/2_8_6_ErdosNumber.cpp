#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

#define _MY_DEBUG_

/*
	��������������������⣡����
*/

// ȫ����inf��

// <string, int>
map<string, int> nameMap;

// ���ֵ
const int MAX_INT = 0x7FFFFFFF;

// �������е����µ�vector��ÿ��Ԫ��Ϊһ��set�����������б�
vector< set<string> * > allArticleVec;

/*
	MainStructure: ���ṹ
*/
void MainStructure();

/*
	Process������ÿһ������
*/
void Process();

/*
	Handle������ÿһ���е�ÿһ��ʵ��
*/
void Handle(int sid);

/*
	����paper
*/
void InputPaper(string paper, set<string> *article);

/*
	CalculateNumber
*/
void CalculateNumber();

///*
//	��ʼ���������������Erdos��صļ�indexΪ1����
//	������Erdos�йص��˵ĸ���
//	
//*/
//int InitErdos();


/*
	������
*/
void OutPut();

/*
	����person: ...Cao, .... lei
*/
void ParsePersonName(string &name);


int main()
{
	MainStructure();
	return 0;
}


void MainStructure()
{
	
#ifdef _MY_DEBUG_
	string inputStr = "C:/Users/cao/Desktop/�㷨/Ҫ������/�㷨/2��ս���/input/1.inp";
	//string inputStr = "D:/2��ս���/input/110206.inp";
	string outputStr = "C:/Users/cao/Desktop/�㷨/Ҫ������/�㷨/2��ս���/input/0000001.outp";
	ifstream fin;
	fin.open(inputStr);	
	cin.rdbuf(fin.rdbuf());	

	ofstream fout;
	fout.open(outputStr);

	//cout.rdbuf(fout.rdbuf());
	Process();

#endif
		
}

void Process()
{
	// ������������
	int count = 0;
	cin >> count;
	int sid = 1;
	while (count--)
	{
		Handle(sid++);
	}
}

void Handle(int sid)
{	
	allArticleVec.clear();	
	nameMap.clear();
	// ������
	int numArticle = 0;
	// ������
	int numPort = 0;
	cin >> numArticle >> numPort;
	allArticleVec.reserve(numArticle);
	for (int i = 0; i < numArticle; ++i)
	{
		set<string> *pSet = new set<string>();
		allArticleVec.push_back(pSet);
	}
	cin.get();
	int articleIndex = 0;
	while (numArticle--)
	{
		// ��ȡһƪpaper
		string paper;
		// Smith, M.N., Martin, G., Erdos, P.: Newtonian forms of prime factors
		/*getchar();*/
		getline(cin, paper);

		// �ֲ���������
		set<string> article;
		//InputPaper(paper, &article);
		InputPaper(paper, allArticleVec[articleIndex++]);
	}
	// ����
	CalculateNumber();

	// ���
	cout << "Scenario " << sid << endl;
	vector<string> persons;
	string person = "";
	while (numPort--)
	{
		getline(cin, person);
		ParsePersonName(person);
		cout << person << " ";
		// ������
		if (nameMap.find(person) == nameMap.end())
		{
			cout << "infinity" << endl;
			continue;
		}
		if (nameMap[person] != MAX_INT)
		{
			cout << nameMap[person] << endl;
		}
		else
		{
			cout << "infinity" << endl;
		}
	}
	for (int i = 0; i < numArticle; ++i)
	{
		set<string> *pSet = allArticleVec[i];
		delete pSet;
	}
}

void InputPaper(string paper, set<string> *article)
{
	// Smith, M.N., Martin, G., Erdos, P.: Newtonian forms of prime factors
	string name;
	bool isSecond = false;
	// �����������б�
	size_t pos = paper.find(':');
	paper = paper.substr(0, pos);
	paper += ", ";
	
	// Smith, M.N., Martin, G., Erdos, P.,
	pos = 0;
	// ȥ���ײ��ո�
	while (isspace(paper.at(pos)))
	{
		++pos;
	}
	paper = paper.substr(pos);
	while ((pos = paper.find(',', pos + 1)) != string::npos)
	{
		if (!isSecond)
		{
			isSecond = true;
			name = paper.substr(0, pos);

			int len = name.length();
			while (isspace(name.at(len - 1)))
			{
				name.erase(len - 1, 1);
				--len;
			}

			paper = paper.substr(pos + 1);
			pos = 0;
			while ((pos < paper.length()) && isspace(paper.at(pos)))
			{
				++pos;
			}
			paper = paper.substr(pos);
			pos = 0;
		}
		else
		{
			name += ", ";
			name += paper.substr(0, pos);
			int len = name.length();
			while (isspace(name.at(len - 1)))
			{
				name.erase(len - 1, 1);
				--len;
			}

			// ��name����map��
			if (nameMap.find(name) == nameMap.end())
			{
				nameMap[name] = MAX_INT;
			}
			article->insert(name);

			paper = paper.substr(pos + 1);
			pos = 0;

			while ((pos < paper.length()) && isspace(paper.at(pos)))
			{
				++pos;
			}
			paper = paper.substr(pos);
			pos = 0;
			isSecond = false;
		}
	}
}



void OutPut()
{
}

void CalculateNumber()
{
	// 1.��ʼ���������������Erdos��صļ�indexΪ1����
	//int initNum = 0;
	//if ((initNum = InitErdos()) == 0)
	//{
	//	return;
	//}
	// ��ʼ��
	// �����������ֱ�ӷ���
	if (nameMap.find("Erdos, P.") == nameMap.end())
	{
		return;
	}
	nameMap["Erdos, P."] = 0;
	// 2.һ������count��
	int count = nameMap.size() - 1;
	// ��1��ʼ����
	int index = 0;
	while (count)
	{
		// ���û���ҵ���˵��δ������ˣ�����inf
		bool found = false;
		// ����nameMap,�ҵ�==index���ˣ�Ȼ�����article���ҳ������������
		for (map<string, int>::iterator mapItr = nameMap.begin(); mapItr != nameMap.end(); ++mapItr)
		{
			if (mapItr->second == index)
			{
				found = true;
				// ����article���ҳ������������
				int artCount = allArticleVec.size();
				for (int i = 0; i < artCount; ++i)
				{
					set<string> *setItr = allArticleVec[i];
					// �ҵ������������
					if (setItr->find(mapItr->first) != setItr->end())
					{
						// ����set������set����������
						for (set<string>::iterator it = setItr->begin(); it != setItr->end(); ++it)
						{
							// �����nameMap���Ѿ����¹����򲻹ܣ�����ֵΪindex+1
							if (nameMap[*it] == MAX_INT)
							{
								nameMap[*it] = index + 1;
								--count;
							}
						}
					}
				}
			}
		}
		// ���û���ҵ���˵��ʣ����ǹ�����
		if (!found)
		{
			break;
		}
		// Ѱ����һ��
		++index;
	}	
}

void ParsePersonName(string &name)
{
	int pos = 0;
	while (isspace(name.at(pos)))
	{
		++pos;
	}
	name = name.substr(pos);
	pos = name.find(',');
	if (pos == string::npos)
	{
		return;
	}
	string tmp = name.substr(0, pos);
	tmp += ", ";
	name = name.substr(pos + 1);
	pos = 0;	
	while (isspace(name.at(pos)))
	{
		name.erase(pos, 1);
	}
	tmp += name;
	name = tmp;
	int len = name.length();
	while (isspace(name.at(len - 1))) 
	{
		name.erase(len - 1, 1);
		--len;
	}
}