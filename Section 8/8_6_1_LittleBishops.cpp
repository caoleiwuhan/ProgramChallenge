#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <string>
#include <cstring>
#include <fstream>
#include <cassert>
#include <cmath>

using namespace std;

//#define _MY_DEBUG_

/************************************************************************/

class HP
{
public:
	// 最大长度
	static const int MAXL = 1010;
	// 数制
	static const int BASE = 10;
	// 长度
	int len;
	// 保存每一位
	int s[MAXL];

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
			s[len++] = inte % BASE;
			inte /= BASE;
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
		c.s[i + 1] = c.s[i] / BASE;
		c.s[i] %= BASE;
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
			c.s[i] += BASE;
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
			c.s[i + j + 1] += c.s[i + j] / BASE;
			c.s[i + j] %= BASE;
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


/************************************************************************/

// 棋盘
int arr[10][10];

// map
int direction[4][2] = 
{
	-1, 1,		// 右上
	1, 1,		// 右下
	1, -1,		// 左下
	-1, -1		// 左上
};



/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process
*/
void Process();

/*
	传入n、k，返回解决方案数
*/
HP BackStace(int n, int k);

void Solve(int n, int k, int step, HP &ans, int pos);

void UpdateArr(int i, int j, int n, bool add);

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
	string outputStr = "C:/Users/cao/Desktop/算法/要看的书/算法/2挑战编程/input/1.outp";
	ifstream fin;
	fin.open(inputStr);		

	cin.rdbuf(fin.rdbuf());	

	/*
	ofstream fout;
	fout.open(outputStr.c_str());
	cout.rdbuf(fout.rdbuf());
	*/

#endif

	Process();
			
}

void Process()
{
	int n, k;
	while (cin >> n >> k)
	{
		if (n == 0 && k == 0)
		{
			break;
		}
		HP ans = 0;
		ans = BackStace(n, k);
		cout << ans << endl;
	}
}



HP BackStace(int n, int k)
{
	HP ans = 0;
	memset(arr, 0, sizeof(arr));
	Solve(n, k, 0, ans, 0);

	return ans;
}

void Solve(int n, int k, int step, HP &ans, int pos)
{
	if (step == k)
	{
		ans += 1;
		return;
	}
	else
	{
		// 从arr中挑一个为0的位置
		for (int i = pos; i < n * n; ++i)
		{
			int x = i / n;
			int y = i % n;
			if (arr[x][y] == 0)
			{
				// 更新arr，将与（i，j）交叉的地方
				UpdateArr(x, y, n, true);
				// 下一个位置
				Solve(n, k, step + 1, ans, x * n + y + 1);
				UpdateArr(x, y, n, false);
			}			
		}
	}
}


void UpdateArr(int i, int j, int n, bool add)
{
	// 这样是扫描了面，优化时，直接扫描两条线
	
	for (int index = 0; index < 4; ++index)
	{
		int curX = i;
		int curY = j;
		while (true)
		{
			curX += direction[index][0];
			curY += direction[index][1];
			// 出界
			if (curX < 0 || curX >= n ||
				curY < 0 || curY >= n)
			{
				break;
			}
			else
			{
				if (add)
				{
					++arr[curX][curY];
				}
				else
				{
					--arr[curX][curY];
				}
			}
		}
	}
	if (add)
	{
		++arr[i][j];
	}
	else
	{
		--arr[i][j];
	}
}


