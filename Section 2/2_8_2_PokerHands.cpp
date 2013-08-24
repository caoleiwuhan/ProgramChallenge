#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

//#define _MY_DEBUG_

// 
const int NUM_CARD = 5;

/*
	读入大小以及花色
*/
void InputCard(string str, int cards1[], char color1[], int cards2[], char color2[]);


/*
	输入大小，颜色，判断类型
	9.同花顺
	8.四张相等的
	7.葫芦：三张相等、两张相等
	6.同花
	5.顺子
	4.三张
	3.两对
	2.一对
	1.都不是
*/
int KindOfCard(int cards[], char color[], int &max);

/*
	比较两个牌：
		1.black win：1
		2.write win：-1
		3.tied： 0
*/	
int CompareTwoCards(string str);


/*
	比较两个不相同牌的大小
		前者大：1
		相等：0
		后者大：-1
*/
int CompareDifference(int cards1[], int cards2[]);

/*
	比较有一对相同的大小
*/
int CompareOnePair(int cards1[], int cards2[]);

// 找到一对的位置，
int CompareOnePairHelp(int cards1[]);


/*
	比较有两对相同的大小
*/
int CompareTwoPair(int cards1[], int cards2[]);

void CompareTwoPairHelp(int cards1[], int &num1, int &num2, int &num3);

/*
	是否同花顺
*/
bool IsTongHuaShun(int cards[], char color[]);

/*
	是否四张相同，如果是：返回最大的
*/
bool IsFourEqual(int cards[], int &max);

/*
	是否是葫芦，如果是：返回最大的
*/
bool IsHuLu(int cards[], int &max);

/*
	是否是同花
*/
bool IsTongHua(char color[]);

/*
	是否是顺子
*/
bool IsShunZi(int cards[]);

/*
	是否三张相同
*/
bool IsThreeEqual(int cards[], int &max);

/*
	是否有两对
*/
bool IsTwoPair(int cards[]);

/*
	是否有两对
*/
bool IsOnePair(int cards[]);

void TestIO();

/*
	Structure
*/
void Structure();

/*
	由大到小排序的排序比较函数
*/
bool MyCompare(int num1, int num2);


/*
	测试
*/
void Test(string str)
{
	int ans = CompareTwoCards(str);
	if (ans == 0)
	{
		cout << "Tie." << endl;
	}
	if (ans > 0)
	{
		cout << "Black wins." << endl;
	}
	if (ans < 0)
	{
		cout << "White wins." << endl;
	}
}


int main()
{
	// 
	//TestIO();
	Structure();

	return 0;
}

void TestIO()
{
#ifdef _MY_DEBUG_
	string inputStr = "C:/Users/cao/Desktop/算法/要看的书/算法/2挑战编程/input/0000001.inp";

	string outputStr = "C:/Users/cao/Desktop/算法/要看的书/算法/2挑战编程/input/0000001.outp";
	ifstream fin;
	fin.open(inputStr);	

	cin.rdbuf(fin.rdbuf());	

	ofstream fout;
	fout.open(outputStr);

	// cout.rdbuf(fout.rdbuf());
#endif
	// 1.测试类型
	// 23456789TJQKA
	// 同花顺、四张
	string str = "AH KH TH QH JH TC QH QS QC QH";
	//Test(str);
	// 同花、葫芦						33888
	str = "JH 9H TH QH 8H TC QH QS TC TH";
	//Test(str);
	// 同花、顺子
	str = "2H 3H 7H 6H 4H 8C TH 9S QC JH";
	//Test(str);

	// 三张 77742	74442
	str = "4H 7H 7H 2C 7H 7C 4H 4S 4C 2H";
	//Test(str);

	// 两对	88433	84433
	str = "8H 8H 4H 3C 3H 8C 4H 4S 3C 3H";
	//Test(str);

	// 两对	88433	88332
	str = "8H 8H 4H 3C 3H 8C 8H 3S 3C 2H";
	//Test(str);

	// 两对	88443	88442
	str = "8H 8H 4H 4C 3H 8C 8H 4S 4C 2H";
	//Test(str);

	// 一对	88432	84432
	str = "8H 8H 4H 3C 2H 8C 4H 4S 3C 2H";
	Test(str);

	// 两对	84332	84322
	str = "8H 4H 3H 3C 2H 8C 4H 3S 2C 2H";
	Test(str);

	// 两对	88543	88542
	str = "8H 8H 5H 4C 3H 8C 8H 5S 4C 2H";
	Test(str);

	// 1.测试输入，一个字符一个字符读取，中间空一行 cin.get()
	//int ch;
	//while ((ch = cin.get()) != EOF)
	//{
	//	cout << ch << " " << (char)ch << endl;
	//}
	// getline
	//string str;
	//while (getline(cin, str))
	//{
	//	// 遇到空行
	//	if (str == "")
	//	{
	//		continue;
	//	}
	//	cout << str << endl;
	//}
	// 
	// 一个字符一个字符输出
}

void Structure()
{
	// 测试用文件
#ifdef _MY_DEBUG_
	string inputStr = "C:/Users/cao/Desktop/算法/要看的书/算法/2挑战编程/input/0000001.inp";

	string outputStr = "C:/Users/cao/Desktop/算法/要看的书/算法/2挑战编程/input/0000001.outp";
	ifstream fin;
	fin.open(inputStr);	

	cin.rdbuf(fin.rdbuf());	

	ofstream fout;
	fout.open(outputStr);

	//cout.rdbuf(fout.rdbuf());
#endif

	// black card
	string str;
	
	while (getline(cin, str))
	{
		if (str == "")
		{
			break;
		}
		int ans = CompareTwoCards(str);
		if (ans == 0)
		{
			cout << "Tie." << endl;
		}
		if (ans > 0)
		{
			cout << "Black wins." << endl;
		}
		if (ans < 0)
		{
			cout << "White wins." << endl;
		}
	}	
}

/*
	T:10
	J:11
	Q:12
	K:13
	A:14
*/
void InputCard(string str, int cards1[], char color1[], int cards2[], char color2[])
{
	// 解析str
	stringstream ss(str);
	// 暂存
	char ch;
	int index = 0;
	bool isBlack = true;
	while (ss >> ch)
	{
		if (index == 5)
		{
			index = 0;
			isBlack = false;
		}
		// 第一个ch是数字
		int num = 0;
		switch(ch)
		{
		case 'A':
			num = 14;
			break;
		case 'K':
			num = 13;
			break;
		case 'Q':
			num = 12;
			break;
		case 'J':
			num = 11;
			break;
		case 'T':
			num = 10;
			break;
		default:
			num = ch - '0';
			break;
		}
		if (isBlack)
		{
			cards1[index] = num;
			ss >> ch;
			color1[index++] = ch;
		}
		else
		{
			cards2[index] = num;
			ss >> ch;
			color2[index++] = ch;
		}
	}	
}

/*
	比较两个牌：
		1.black win：1
		2.write win：-1
		3.tied： 0
*/	
int CompareTwoCards(string str)
{
	// 对于牌，只用保存牌大小，以及是否花色相同
	int blackCard[NUM_CARD];
	char blackColor[NUM_CARD];

	int whiteCard[NUM_CARD];
	char whiteColor[NUM_CARD];

	InputCard(str, blackCard, blackColor, whiteCard, whiteColor);
	// 黑方的牌类型、最大值：只有最大值、一对、两对、同花时max不确定
	int blackKind;
	int blackMax;
	// 白方的牌类型、最大值
	int whiteKind;
	int whiteMax;
	
	// 对两个cards进行排序
	sort(blackCard, blackCard + NUM_CARD, MyCompare);
	sort(whiteCard, whiteCard + NUM_CARD, MyCompare);	

	blackKind = KindOfCard(blackCard, blackColor, blackMax);
	whiteKind = KindOfCard(whiteCard, whiteColor, whiteMax);

	if (blackKind == whiteKind)
	{
		// 最大值、一对、两对、同花：如果不是这四种，直接比较max大小
		/*
			输入大小，颜色，判断类型
			9.同花顺
			8.四张相等的
			7.葫芦：三张相等、两张相等
			6.同花
			5.顺子
			4.三张
			3.两对
			2.一对
			1.都不是
		*/
		switch(blackKind)
		{
		case 9:
		case 8:
		case 7:
		case 5:
		case 4:
			return (blackMax - whiteMax);
		case 1:
		case 6:
			return CompareDifference(blackCard, whiteCard);
			break;
		case 2:
			return CompareOnePair(blackCard, whiteCard);
			break;
		case 3:
			return CompareTwoPair(blackCard, whiteCard);
			break;
		}		
	}
	else 
	{
		return (blackKind - whiteKind);
	}
}

// 最大值、一对、两对、同花：如果不是这四种，直接比较max大小
/*
	输入大小，颜色，判断类型
	9.同花顺
	8.四张相等的
	7.葫芦：三张相等、两张相等
	6.同花
	5.顺子
	4.三张
	3.两对
	2.一对
	1.都不是
*/
int KindOfCard(int cards[], char color[], int &max)
{
	// 是否是同花顺
	if (IsTongHuaShun(cards, color))
	{
		max = cards[0];
		return 9;
	}
	// 四张相等
	if (IsFourEqual(cards, max))
	{
		return 8;
	}
	// 葫芦
	if (IsHuLu(cards, max))
	{
		return 7;
	}
	// 同花
	if (IsTongHua(color))
	{
		return 6;
	}
	// 顺子
	if (IsShunZi(cards))
	{
		max = cards[0];
		return 5;
	}
	// 三张
	if (IsThreeEqual(cards, max))
	{
		return 4;
	}
	// 两对
	if (IsTwoPair(cards))
	{
		return 3;
	}
	// 一对
	if (IsOnePair(cards))
	{
		return 2;
	}
	return 1;	
}

int CompareDifference(int cards1[], int cards2[])
{
	// 由于已经排好序
	int i;
	for (i = 0; i < NUM_CARD && cards1[i] == cards2[i]; ++i)
		;
	if (i == NUM_CARD)
	{
		return 0;
	}
	return cards1[i] - cards2[i];	
}

// 一对：错误！！！ 测试！！！
int CompareOnePair(int cards1[], int cards2[])
{
	// 1.找到一对的位置，并把它去掉
	int pos1 = CompareOnePairHelp(cards1);
	int pos2 = CompareOnePairHelp(cards2);
	
	if (cards1[pos1] == cards2[pos2])
	{
		// 2.将重复的去掉，然后作为最大值比较
		int tmp1[NUM_CARD] = {0};
		int tmp2[NUM_CARD] = {0};
		int index = 0;
		for (int i = 0; i < NUM_CARD; ++i)
		{
			if (i == pos1)
			{
				++i;
			}
			else
			{
				tmp1[index++] = cards1[i];
			}
		}
		index = 0;
		for (int i = 0; i < NUM_CARD; ++i)
		{
			if (i == pos2)
			{
				++i;
			}
			else
			{
				tmp2[index++] = cards2[i];
			}
		}
		return CompareDifference(tmp1, tmp2);
	}
	else
	{
		return cards1[pos1] - cards2[pos2];
	}
}

int CompareOnePairHelp(int cards[])
{
	int last = cards[0];
	for (int i = 1; i < NUM_CARD; ++i)
	{
		if (cards[i] == last)
		{
			return (i - 1);
		}
		last = cards[i];
	}
}

// 两对：错误！！！ 测试！！！
int CompareTwoPair(int cards1[], int cards2[])
{
	// 黑色
	int blackNum1;
	int blackNum2;
	int blackNum3;
	// 白色
	int whiteNum1;
	int whiteNum2;
	int whiteNum3;
	CompareTwoPairHelp(cards1, blackNum1, blackNum2, blackNum3);
	CompareTwoPairHelp(cards2, whiteNum1, whiteNum2, whiteNum3);
	return (blackNum1 == whiteNum1 ? 
		((blackNum2 == whiteNum2) ? (blackNum3 - whiteNum3) : (blackNum2 - whiteNum2)) :
		(blackNum1 - whiteNum1));
}

void CompareTwoPairHelp(int cards[], int &num1, int &num2, int &num3)
{	
	int numPair = 0;	

	for (int i = 0; i < NUM_CARD; )
	{
		if ((i < NUM_CARD - 1) && cards[i] == cards[i + 1])
		{
			if (numPair == 0)
			{
				num1 = cards[i];
			}
			else 
			{
				num2 = cards[i];
			}
			++numPair;
			i += 2;
		}
		else
		{
			num3 = cards[i];
			++i;
		}
	}
}

bool MyCompare(int num1, int num2)
{
	return (num1 > num2);
}

bool IsTongHuaShun(int cards[], char color[])
{
	return IsShunZi(cards) && IsTongHua(color);
}

bool IsFourEqual(int cards[], int &max)
{
	// 相等的长度
	int len = 1;
	// 上一个数字
	int last = cards[0];
	max = cards[0];
	for (int i = 1; i < NUM_CARD; ++i)
	{
		if (len >= 4)
		{			
			return true;
		}
		if (cards[i] == last)
		{
			++len;
			//max = cards[i];
		}
		else
		{
			last = cards[i];
			len = 1;
			max = cards[i];
		}
	}
	if (len >= 4)
	{			
		return true;
	}
	return false;
}

bool IsHuLu(int cards[], int &max)
{
	// 三张相等，两张相等：只能前三个或后三个相等
	if (cards[0] == cards[1] && cards[1] == cards[2])		
	{
		if (cards[3] == cards[4])
		{
			max = cards[0];
			return true;
		}
	}
	if (cards[2] == cards[3] && cards[3] == cards[4])		
	{
		if (cards[0] == cards[1])
		{
			max = cards[2];
			return true;
		}
	}
	return false;
}

bool IsTongHua(char color[])
{
	for (int i = 1; i < NUM_CARD; ++i)
	{
		if (color[i - 1] != color[i])
		{
			return false;
		}
	}
	return true;
}

bool IsShunZi(int cards[])
{
	for (int i = 1; i < NUM_CARD; ++i)
	{
		if (cards[i - 1] != (cards[i] + 1))
		{
			return false;
		}
	}
	return true;
}

bool IsThreeEqual(int cards[], int &max)
{
	// 相等的长度
	int len = 1;
	// 上一个数字
	int last = cards[0];
	max = cards[0];
	for (int i = 1; i < NUM_CARD; ++i)
	{
		if (len >= 3)
		{
			return true;
		}
		if (cards[i] == last)
		{
			++len;
			//max = cards[i];
		}
		else
		{
			last = cards[i];
			len = 1;
			max = cards[i];
		}
	}
	if (len >= 3)
	{
		return true;
	}
	return false;
}

// 
bool IsTwoPair(int cards[])
{
	// 对数
	int numPair = 0;
	// 上一个
	int last = cards[0];

	for (int i = 1; i < NUM_CARD; ++i)
	{
		if (cards[i] == last)
		{
			++numPair;
		}

		last = cards[i];		
	}
	if (numPair == 2)
	{
		return true;
	}
	return false;
}

bool IsOnePair(int cards[])
{
	int last = cards[0];
	for (int i = 1; i < NUM_CARD; ++i)
	{
		if (cards[i] == last)
		{
			return true;
		}

		last = cards[i];		
	}
	return false;
}