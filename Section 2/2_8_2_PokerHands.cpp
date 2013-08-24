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
	�����С�Լ���ɫ
*/
void InputCard(string str, int cards1[], char color1[], int cards2[], char color2[]);


/*
	�����С����ɫ���ж�����
	9.ͬ��˳
	8.������ȵ�
	7.��«��������ȡ��������
	6.ͬ��
	5.˳��
	4.����
	3.����
	2.һ��
	1.������
*/
int KindOfCard(int cards[], char color[], int &max);

/*
	�Ƚ������ƣ�
		1.black win��1
		2.write win��-1
		3.tied�� 0
*/	
int CompareTwoCards(string str);


/*
	�Ƚ���������ͬ�ƵĴ�С
		ǰ�ߴ�1
		��ȣ�0
		���ߴ�-1
*/
int CompareDifference(int cards1[], int cards2[]);

/*
	�Ƚ���һ����ͬ�Ĵ�С
*/
int CompareOnePair(int cards1[], int cards2[]);

// �ҵ�һ�Ե�λ�ã�
int CompareOnePairHelp(int cards1[]);


/*
	�Ƚ���������ͬ�Ĵ�С
*/
int CompareTwoPair(int cards1[], int cards2[]);

void CompareTwoPairHelp(int cards1[], int &num1, int &num2, int &num3);

/*
	�Ƿ�ͬ��˳
*/
bool IsTongHuaShun(int cards[], char color[]);

/*
	�Ƿ�������ͬ������ǣ���������
*/
bool IsFourEqual(int cards[], int &max);

/*
	�Ƿ��Ǻ�«������ǣ���������
*/
bool IsHuLu(int cards[], int &max);

/*
	�Ƿ���ͬ��
*/
bool IsTongHua(char color[]);

/*
	�Ƿ���˳��
*/
bool IsShunZi(int cards[]);

/*
	�Ƿ�������ͬ
*/
bool IsThreeEqual(int cards[], int &max);

/*
	�Ƿ�������
*/
bool IsTwoPair(int cards[]);

/*
	�Ƿ�������
*/
bool IsOnePair(int cards[]);

void TestIO();

/*
	Structure
*/
void Structure();

/*
	�ɴ�С���������ȽϺ���
*/
bool MyCompare(int num1, int num2);


/*
	����
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
	string inputStr = "C:/Users/cao/Desktop/�㷨/Ҫ������/�㷨/2��ս���/input/0000001.inp";

	string outputStr = "C:/Users/cao/Desktop/�㷨/Ҫ������/�㷨/2��ս���/input/0000001.outp";
	ifstream fin;
	fin.open(inputStr);	

	cin.rdbuf(fin.rdbuf());	

	ofstream fout;
	fout.open(outputStr);

	// cout.rdbuf(fout.rdbuf());
#endif
	// 1.��������
	// 23456789TJQKA
	// ͬ��˳������
	string str = "AH KH TH QH JH TC QH QS QC QH";
	//Test(str);
	// ͬ������«						33888
	str = "JH 9H TH QH 8H TC QH QS TC TH";
	//Test(str);
	// ͬ����˳��
	str = "2H 3H 7H 6H 4H 8C TH 9S QC JH";
	//Test(str);

	// ���� 77742	74442
	str = "4H 7H 7H 2C 7H 7C 4H 4S 4C 2H";
	//Test(str);

	// ����	88433	84433
	str = "8H 8H 4H 3C 3H 8C 4H 4S 3C 3H";
	//Test(str);

	// ����	88433	88332
	str = "8H 8H 4H 3C 3H 8C 8H 3S 3C 2H";
	//Test(str);

	// ����	88443	88442
	str = "8H 8H 4H 4C 3H 8C 8H 4S 4C 2H";
	//Test(str);

	// һ��	88432	84432
	str = "8H 8H 4H 3C 2H 8C 4H 4S 3C 2H";
	Test(str);

	// ����	84332	84322
	str = "8H 4H 3H 3C 2H 8C 4H 3S 2C 2H";
	Test(str);

	// ����	88543	88542
	str = "8H 8H 5H 4C 3H 8C 8H 5S 4C 2H";
	Test(str);

	// 1.�������룬һ���ַ�һ���ַ���ȡ���м��һ�� cin.get()
	//int ch;
	//while ((ch = cin.get()) != EOF)
	//{
	//	cout << ch << " " << (char)ch << endl;
	//}
	// getline
	//string str;
	//while (getline(cin, str))
	//{
	//	// ��������
	//	if (str == "")
	//	{
	//		continue;
	//	}
	//	cout << str << endl;
	//}
	// 
	// һ���ַ�һ���ַ����
}

void Structure()
{
	// �������ļ�
#ifdef _MY_DEBUG_
	string inputStr = "C:/Users/cao/Desktop/�㷨/Ҫ������/�㷨/2��ս���/input/0000001.inp";

	string outputStr = "C:/Users/cao/Desktop/�㷨/Ҫ������/�㷨/2��ս���/input/0000001.outp";
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
	// ����str
	stringstream ss(str);
	// �ݴ�
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
		// ��һ��ch������
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
	�Ƚ������ƣ�
		1.black win��1
		2.write win��-1
		3.tied�� 0
*/	
int CompareTwoCards(string str)
{
	// �����ƣ�ֻ�ñ����ƴ�С���Լ��Ƿ�ɫ��ͬ
	int blackCard[NUM_CARD];
	char blackColor[NUM_CARD];

	int whiteCard[NUM_CARD];
	char whiteColor[NUM_CARD];

	InputCard(str, blackCard, blackColor, whiteCard, whiteColor);
	// �ڷ��������͡����ֵ��ֻ�����ֵ��һ�ԡ����ԡ�ͬ��ʱmax��ȷ��
	int blackKind;
	int blackMax;
	// �׷��������͡����ֵ
	int whiteKind;
	int whiteMax;
	
	// ������cards��������
	sort(blackCard, blackCard + NUM_CARD, MyCompare);
	sort(whiteCard, whiteCard + NUM_CARD, MyCompare);	

	blackKind = KindOfCard(blackCard, blackColor, blackMax);
	whiteKind = KindOfCard(whiteCard, whiteColor, whiteMax);

	if (blackKind == whiteKind)
	{
		// ���ֵ��һ�ԡ����ԡ�ͬ����������������֣�ֱ�ӱȽ�max��С
		/*
			�����С����ɫ���ж�����
			9.ͬ��˳
			8.������ȵ�
			7.��«��������ȡ��������
			6.ͬ��
			5.˳��
			4.����
			3.����
			2.һ��
			1.������
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

// ���ֵ��һ�ԡ����ԡ�ͬ����������������֣�ֱ�ӱȽ�max��С
/*
	�����С����ɫ���ж�����
	9.ͬ��˳
	8.������ȵ�
	7.��«��������ȡ��������
	6.ͬ��
	5.˳��
	4.����
	3.����
	2.һ��
	1.������
*/
int KindOfCard(int cards[], char color[], int &max)
{
	// �Ƿ���ͬ��˳
	if (IsTongHuaShun(cards, color))
	{
		max = cards[0];
		return 9;
	}
	// �������
	if (IsFourEqual(cards, max))
	{
		return 8;
	}
	// ��«
	if (IsHuLu(cards, max))
	{
		return 7;
	}
	// ͬ��
	if (IsTongHua(color))
	{
		return 6;
	}
	// ˳��
	if (IsShunZi(cards))
	{
		max = cards[0];
		return 5;
	}
	// ����
	if (IsThreeEqual(cards, max))
	{
		return 4;
	}
	// ����
	if (IsTwoPair(cards))
	{
		return 3;
	}
	// һ��
	if (IsOnePair(cards))
	{
		return 2;
	}
	return 1;	
}

int CompareDifference(int cards1[], int cards2[])
{
	// �����Ѿ��ź���
	int i;
	for (i = 0; i < NUM_CARD && cards1[i] == cards2[i]; ++i)
		;
	if (i == NUM_CARD)
	{
		return 0;
	}
	return cards1[i] - cards2[i];	
}

// һ�ԣ����󣡣��� ���ԣ�����
int CompareOnePair(int cards1[], int cards2[])
{
	// 1.�ҵ�һ�Ե�λ�ã�������ȥ��
	int pos1 = CompareOnePairHelp(cards1);
	int pos2 = CompareOnePairHelp(cards2);
	
	if (cards1[pos1] == cards2[pos2])
	{
		// 2.���ظ���ȥ����Ȼ����Ϊ���ֵ�Ƚ�
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

// ���ԣ����󣡣��� ���ԣ�����
int CompareTwoPair(int cards1[], int cards2[])
{
	// ��ɫ
	int blackNum1;
	int blackNum2;
	int blackNum3;
	// ��ɫ
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
	// ��ȵĳ���
	int len = 1;
	// ��һ������
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
	// ������ȣ�������ȣ�ֻ��ǰ��������������
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
	// ��ȵĳ���
	int len = 1;
	// ��һ������
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
	// ����
	int numPair = 0;
	// ��һ��
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