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
	继续测试输入输出的问题！！！
*/

// 全部是inf的

// <string, int>
map<string, int> nameMap;

// 最大值
const int MAX_INT = 0x7FFFFFFF;

// 保存所有的文章的vector：每个元素为一个set：保存作者列表
vector< set<string> * > allArticleVec;

/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process：处理每一组数据
*/
void Process();

/*
	Handle：处理每一组中的每一个实例
*/
void Handle(int sid);

/*
	处理paper
*/
void InputPaper(string paper, set<string> *article);

/*
	CalculateNumber
*/
void CalculateNumber();

///*
//	初始化：计算出所有与Erdos相关的即index为1的人
//	返回与Erdos有关的人的个数
//	
//*/
//int InitErdos();


/*
	输出结果
*/
void OutPut();

/*
	解析person: ...Cao, .... lei
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
	string inputStr = "C:/Users/cao/Desktop/算法/要看的书/算法/2挑战编程/input/1.inp";
	//string inputStr = "D:/2挑战编程/input/110206.inp";
	string outputStr = "C:/Users/cao/Desktop/算法/要看的书/算法/2挑战编程/input/0000001.outp";
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
	// 测试数据组数
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
	// 文章数
	int numArticle = 0;
	// 作者数
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
		// 读取一篇paper
		string paper;
		// Smith, M.N., Martin, G., Erdos, P.: Newtonian forms of prime factors
		/*getchar();*/
		getline(cin, paper);

		// 局部变量啊！
		set<string> article;
		//InputPaper(paper, &article);
		InputPaper(paper, allArticleVec[articleIndex++]);
	}
	// 计算
	CalculateNumber();

	// 输出
	cout << "Scenario " << sid << endl;
	vector<string> persons;
	string person = "";
	while (numPort--)
	{
		getline(cin, person);
		ParsePersonName(person);
		cout << person << " ";
		// 不存在
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
	// 解析出作者列表
	size_t pos = paper.find(':');
	paper = paper.substr(0, pos);
	paper += ", ";
	
	// Smith, M.N., Martin, G., Erdos, P.,
	pos = 0;
	// 去除首部空格
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

			// 将name加入map中
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
	// 1.初始化：计算出所有与Erdos相关的即index为1的人
	//int initNum = 0;
	//if ((initNum = InitErdos()) == 0)
	//{
	//	return;
	//}
	// 初始化
	// 如果不包含，直接返回
	if (nameMap.find("Erdos, P.") == nameMap.end())
	{
		return;
	}
	nameMap["Erdos, P."] = 0;
	// 2.一共计算count次
	int count = nameMap.size() - 1;
	// 从1开始计算
	int index = 0;
	while (count)
	{
		// 如果没有找到，说明未计算的人，都是inf
		bool found = false;
		// 遍历nameMap,找到==index的人，然后遍历article，找出他发表的文章
		for (map<string, int>::iterator mapItr = nameMap.begin(); mapItr != nameMap.end(); ++mapItr)
		{
			if (mapItr->second == index)
			{
				found = true;
				// 遍历article，找出他发表的文章
				int artCount = allArticleVec.size();
				for (int i = 0; i < artCount; ++i)
				{
					set<string> *setItr = allArticleVec[i];
					// 找到他发表的文章
					if (setItr->find(mapItr->first) != setItr->end())
					{
						// 遍历set，更新set中其他作者
						for (set<string>::iterator it = setItr->begin(); it != setItr->end(); ++it)
						{
							// 如果在nameMap中已经更新过，则不管，否则赋值为index+1
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
		// 如果没有找到，说明剩余的是孤立的
		if (!found)
		{
			break;
		}
		// 寻找下一个
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