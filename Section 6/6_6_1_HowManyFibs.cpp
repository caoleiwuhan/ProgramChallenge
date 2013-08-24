#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <string>
#include <cstring>
#include <fstream>
#include <cassert>

using namespace std;

//#define _MY_DEBUG_
/*****************************Big Int****************************/

class HP
{
public:
	static const int MAXL = 110;
	int len, s[MAXL];

	HP() { (*this) = 0; };
	HP(int inte) { (*this) = inte; };
	HP(const char* str) { (*this) = str; };
	HP(string str) { (*this) = str; };

	friend ostream& operator << (ostream &cout, const HP &x);

	HP operator = (int inte);
	HP operator = (const char* str); 
	HP operator = (string str);

	HP operator + (const HP &b); HP operator += (const HP &b);
	HP operator - (const HP &b); HP operator -= (const HP &b);
	HP operator * (const HP &b); HP operator *= (const HP &b);
	HP operator / (const HP &b); HP operator /= (const HP &b);
	HP operator % (const HP &b); HP operator %= (const HP &b);

	int comp(const HP &b);

	bool operator > (const HP &b); bool operator < (const HP &b);
	bool operator >= (const HP &b); bool operator <= (const HP &b);
	bool operator == (const HP &b); bool operator != (const HP &b);
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
bool HP::operator > (const HP &b) { return this->comp(b) > 0; }
bool HP::operator < (const HP &b) { return this->comp(b) < 0; }
bool HP::operator >= (const HP &b) { return this->comp(b) >= 0; }
bool HP::operator <= (const HP &b) { return this->comp(b) <= 0; }
bool HP::operator == (const HP &b) { return this->comp(b) == 0; }
bool HP::operator != (const HP &b) { return this->comp(b) != 0; }

/****************************************************************/


/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process：处理每一组数据
*/
void Process();


int main()
{
	MainStructure();
	return 0;
}

/*
	计算在hp1和hp2之间的fib的个数
*/
unsigned FibNum(HP &hp1, HP &hp2);

void MainStructure()
{
	
#ifdef _MY_DEBUG_
	string inputStr = "C:/Users/cao/Desktop/算法/要看的书/算法/2挑战编程/input/1.inp";
	//string inputStr = "D:/2挑战编程/input/110205.inp";
	string outputStr = "C:/Users/cao/Desktop/算法/要看的书/算法/2挑战编程/input/1.outp";
	ifstream fin;
	fin.open(inputStr);		

	cin.rdbuf(fin.rdbuf());	

	/*ofstream fout;
	fout.open(outputStr.c_str());
	cout.rdbuf(fout.rdbuf());*/

#endif

	Process();
			
}

void Process()
{
	string str;
	while (getline(cin, str))
	{
		size_t pos = str.find(' ');
		string num1 = str.substr(0, pos);
		string num2 = str.substr(pos + 1);
		if (num1 == "0" && num2 == "0")
		{
			break;
		}
		HP hp1(num1);
		HP hp2(num2);
		unsigned ans = FibNum(hp1, hp2);
		cout << ans << endl;			
	}
}

unsigned FibNum(HP &hp1, HP &hp2)
{
	HP num1 = 1;
	HP num2 = 2;
	while (num1 < hp1)
	{
		HP tmp = num2;
		num2 += num1;
		num1 = tmp;
	}
	unsigned ans = 0;
	while (num1 <= hp2)
	{
		HP tmp = num2;
		num2 += num1;
		num1 = tmp;
		ans += 1;
	}

	return ans;
}
