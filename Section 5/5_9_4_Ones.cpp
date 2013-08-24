#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <string>
#include <cstring>
#include <fstream>
#include <cassert>
#include <stack>

//#include "HP.h"

using namespace std;

//#define _MY_DEBUG_

class HP
{
public:
	static const int MAXL = 10000;
	int len, s[MAXL];

	HP() 
	{ 
		(*this) = 0; 
	}

	HP(int inte) 
	{ 
		(*this) = inte; 
	}

	HP(const char* str) 
	{ 
		(*this) = str; 
	}

	HP(string str) 
	{ 
		(*this) = str; 
	}

	friend ostream& operator << (ostream &cout, const HP &x);

	HP operator = (int inte);
	HP operator = (const char* str); 
	HP operator = (string str);
	HP operator = (const HP &hp);

	HP operator + (const HP &b); 
	HP operator += (const HP &b);

	HP operator - (const HP &b); 
	HP operator -= (const HP &b);

	HP operator * (const HP &b); 
	HP operator *= (const HP &b);

	HP operator / (const HP &b); 
	HP operator /= (const HP &b);

	HP operator % (const HP &b); 
	HP operator %= (const HP &b);

	int comp(const HP &b);

	bool operator > (const HP &b); 
	bool operator < (const HP &b);

	bool operator >= (const HP &b); 
	bool operator <= (const HP &b);

	bool operator == (const HP &b); 
	bool operator != (const HP &b);

};

ostream& operator << (ostream &cout, const HP &x)
{
	for (int i = x.len - 1; i >= 0; --i) 
	{
		cout << x.s[i];
	}
	return cout;
}

HP HP::operator = (int inte)
{
	if (inte == 0)
	{
		len = 1;
		s[0] = 0;
	}
	else
	{
		len = 0;
		while (inte)
		{
			s[len++] = inte % 10;
			inte /= 10;
		}
	}
	return (*this);
}

HP HP::operator = (const char* str)
{
	len = strlen(str);
	for (int i = 0; i != len; ++i) 
		s[i] = int(str[len - 1 - i] - '0');
	return (*this);
}

HP HP::operator = (string str)
{
	len = str.size();
	for (int i = 0; i != len; ++i) 
		s[i] = int(str[len - 1 - i] - '0');
	return (*this);
}

HP HP::operator = (const HP &hp)
{
	len = hp.len;
	for (int i = 0; i != len; ++i)
	{
		s[i] = hp.s[i];
	}
	return (*this);
}

HP HP::operator + (const HP &b)
{
	HP c;
	c.s[0] = 0;
	for (int i = 0; i < len || i < b.len; ++i)
	{
		if (i < len) 
			c.s[i] += s[i];
		if (i < b.len) 
			c.s[i] += b.s[i];
		c.s[i + 1] = c.s[i] / 10;
		c.s[i] %= 10;
	}
	c.len = max(len, b.len) + 1;
	while (c.len > 1 && !c.s[c.len - 1]) 
		--c.len;
	return c;
}

HP HP::operator - (const HP &b)
{
	HP c = (*this);
	for (int i = 0; i != b.len; ++i)
	{
		c.s[i] -= b.s[i];
		if (c.s[i] < 0)
		{
			c.s[i] += 10;
			--c.s[i + 1];
		}
	}
	while (c.len > 1 && !c.s[c.len - 1]) 
		--c.len;
	return c;
}

HP HP::operator * (const HP &b)
{
	HP c;
	for (int i = 0; i != len + b.len; ++i) 
		c.s[i] = 0;
	for (int i = 0; i != len; ++i)
		for (int j = 0; j != b.len; ++j)
		{
			c.s[i + j] += s[i] * b.s[j];
			c.s[i + j + 1] += c.s[i + j] / 10;
			c.s[i + j] %= 10;
		}
		c.len = len + b.len;
		while (c.len > 1 && !c.s[c.len - 1]) 
			--c.len;
		return c;
}

HP HP::operator / (const HP &b)
{
	HP c, d;
	if (b.len == 1 && b.s[0] == 0) 
		return c;
	for (int i = len - 1; i >= 0; --i)
	{
		if (d.len != 1 || d.s[0] != 0)
		{
			for (int j = d.len; j > 0; --j)
				d.s[j] = d.s[j - 1];
			++d.len;
		}
		d.s[0] = s[i];
		c.s[i] = 0;
		while (d >= b)
		{
			d -= b;
			++c.s[i];
		}
	}
	c.len = len;
	while (c.len > 1 && !c.s[c.len - 1]) 
		--c.len;
	return c;
}

HP HP::operator % (const HP &b)
{
	HP d;
	if (b.len == 1 && b.s[0] == 0) 
		return d;
	for (int i = len - 1; i >= 0; --i)
	{
		if (d.len != 1 || d.s[0] != 0)
		{
			for (int j = d.len; j > 0; --j)
				d.s[j] = d.s[j - 1];
			++d.len;
		}
		d.s[0] = s[i];
		while (d >= b) d -= b;
	}
	return d;
}

int HP::comp(const HP &b)
{
	if (len > b.len) return 1;
	if (len < b.len) return -1;
	int i = len - 1;
	while ((i > 0) && (s[i] == b.s[i])) 
		--i;
	return s[i] - b.s[i];
}

HP HP::operator += (const HP &b)
{
	(*this) = (*this) + b;
	return (*this);
}

HP HP::operator -= (const HP &b)
{
	(*this) = (*this) - b;
	return (*this);
}

HP HP::operator *= (const HP &b)
{
	(*this) = (*this) * b;
	return (*this);
}

HP HP::operator /= (const HP &b)
{
	(*this) = (*this) / b;
	return (*this);
}

HP HP::operator %= (const HP &b)
{
	(*this) = (*this) % b;
	return (*this);
}

bool HP::operator > (const HP &b) 
{ 
	return this->comp(b) > 0; 
}

bool HP::operator < (const HP &b) 
{ 
	return this->comp(b) < 0; 
}

bool HP::operator >= (const HP &b) 
{ 
	return this->comp(b) >= 0; 
}

bool HP::operator <= (const HP &b) 
{ 
	return this->comp(b) <= 0; 
}

bool HP::operator == (const HP &b) 
{ 
	return this->comp(b) == 0; 
}

bool HP::operator != (const HP &b) 
{ 
	return this->comp(b) != 0; 
}



/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process：处理每一组数据
*/
void Process();

/*
	Test 高精度结构
*/
void Test();

/*
	计算
*/
int CountNum(HP &hp);


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

	//ofstream fout;
	//fout.open(outputStr.c_str());

	//cout.rdbuf(fout.rdbuf());
#endif

	Process();
	//Test();
		
}


void Process()
{
	int num = 0;
	while (cin >> num)
	{
		HP hp(num);
		int count = CountNum(hp);
		cout << count << endl;
	}
}


void Test()
{
	//// 测试构造函数
	//HP hp1;
	//cout << hp1 << endl;

	//HP hp2(123);
	//cout << hp2 << endl;

	//HP hp3("456");
	//cout << hp3 << endl;

	// 测试运算重载符
	//HP tmp;

	//HP hp4(132);
	//HP hp5(123);
	//tmp = hp4;
	//assert(tmp == 132);
	//cout << hp4 << endl;
	//cout << tmp << endl;

	//hp4 += hp5;
	//assert(hp4 == (123 + 132));
	//hp4 = 132;
	//tmp = hp4 + hp5;
	//assert(tmp == (123 + 132));	

	//hp4 -= hp5;
	//assert(hp4 == (132 - 123));
	//hp4 = 132;
	//tmp = hp4 - hp5;
	//assert(tmp == (132 - 123));

	//hp4 *= hp5;
	//assert(hp4 == (123 * 132));
	//hp4 = 132;
	//tmp = hp4 * hp5;
	//assert(tmp == (123 * 132));	

	//hp4 = 132;
	//hp5 = 12;
	//hp4 /= hp5;
	//assert(hp4 == (132 / 12));
	//hp4 = 132;
	//hp5 = 12;
	//tmp = hp4 / hp5;
	//assert(tmp == (132 / 12));	

	//hp4 = 132;
	//hp5 = 12;
	//hp4 %= hp5;
	//assert(hp4 == (132 % 12));
	//hp4 = 132;
	//hp5 = 12;
	//tmp = hp4 % hp5;
	//assert(tmp == (132 % 12));	

	// 测试comp
	//HP hp1;
	//HP hp2 = 123;
	//HP hp3 = 321;
	//HP hp4 = 122;
	//HP hp5 = 123;
	/*cout << (hp2.comp(hp3)) << endl;
	assert((hp2.comp(hp3)) < 0);
	assert((hp2.comp(hp4)) > 0);
	assert((hp2.comp(hp5)) == 0);*/
	
	//// 测试关系运算符
	//HP hp1;
	//HP hp2 = 123;
	//HP hp3 = 321;
	//HP hp4 = 122;
	//HP hp5 = 123;
	//assert (hp2 < hp3);
	//assert (hp2 <= hp5);
	//assert (hp2 <= hp3);

	//assert (hp3 > hp4);
	//assert (hp2 >= hp5);
	//assert (hp3 >= hp5);

	//assert (hp2 == hp5);

	//assert (hp3 != hp5);

	//cout << "OK" << endl;
}

int CountNum(HP &hp)
{
	int count = 1;
	HP num(1);
	while (true)
	{
		HP tmp = num % hp;
		// 如果能被整除
		if (tmp == 0)
		{
			return count;
		}
		// 否则增加num
		num *= 10;
		num += 1;
		num %= hp;

		++count;
	}
}