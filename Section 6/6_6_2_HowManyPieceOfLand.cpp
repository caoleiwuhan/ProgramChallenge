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
	static const int MAXL = 100;
	int len, s[MAXL];

	HP() 
	{ 
		memset(s, 0, sizeof(s));
		(*this) = 0; 
	};
	HP(int inte) 
	{ 
		memset(s, 0, sizeof(s));
		(*this) = inte; 
	};
	HP(const char* str) 
	{ 
		memset(s, 0, sizeof(s));
		(*this) = str; 
	};
	HP(string str) 
	{
		memset(s, 0, sizeof(s));
		(*this) = str; 
	};

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
	// 保证c > b
	int numLen = c.len;
	for (int i = 0; i != numLen; ++i)
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

/*
	计算
*/
HP FieldCount(HP hp);


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
	int count = 0;
	cin >> count;
	cin.ignore();
	while (count--)
	{
		string str;
		getline(cin, str);
		HP hp(str);
		HP ans = FieldCount(hp);
		cout << ans << endl;
	}

}

// 1 + c(n,2) + c(n,4)
HP FieldCount(HP hp)
{
	HP tmp1 = hp - 1;	
	HP tmp2 = hp * hp;
	HP tmp3 = hp * 5;
	HP tmp4 = tmp2 + 18;// - tmp3;
	tmp4 -= tmp3;
	HP tmp5 = hp * tmp1;
	tmp5 *= tmp4;
	tmp5 /= 24;
	tmp5 += 1;

	//HP ans = (hp * (hp - 1) * (hp * hp - hp * 5 + 18) / 24) + 1;
	
	return tmp5;
}