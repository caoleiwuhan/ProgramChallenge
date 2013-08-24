#include <iostream>
#include <string>
#include <stack>
#include <cstdio>

using namespace std;

/*
	没有注意X1、X2的大小关系！！！
*/

// 像素点
char matrix[300][300];

// 行列数
int M = 0;
int N = 0;

// Rectangle
int rec[4][2] = 
{
	0, -1,
	1, 0,
	0, 1,
	-1, 0
};

// 解析str，并执行相应操作
int ParseStrAndExe(string str);

// I M N
void HandleIMN(string str);

// C
void HandleC();

// L X Y C
void HandleLXYC(string str);

// V X Y1 Y2 C
void HandleVXY1Y2C(string str);

// H X1 X2 Y C
void HandleHX1X2YC(string str);

// K X1 Y1 X2 Y2 C
void HandleKX1Y1X2Y2C(string str);

// F X Y C
void HandleFXYC(string str);

// S Name
void HandleSName(string str);

// X
void HandleX();

// 测试种子点填充
void TestFill();

int main()
{
	//cout << "Test" << endl;
	string str;
	while (getline(cin, str))
	{
		//cout << str << endl;
		// 解析str并执行
		if (ParseStrAndExe(str) == -1)
		{
			break;
		}
	}

	//TestFill();

	return 0;
}

/*
	解析str，并执行相应的函数
	返回值：
		0：正常
		-1：exit
*/
int ParseStrAndExe(string str)
{
	// 1.取得第一个字母
	char ch = str.at(0);
	switch(ch)
	{
	case 'I':
		HandleIMN(str);
		break;
	case 'C':
		HandleC();
		break;
	case 'L':
		HandleLXYC(str);
		break;
	case 'V':
		HandleVXY1Y2C(str);
		break;
	case 'H':
		HandleHX1X2YC(str);
		break;
	case 'K':
		HandleKX1Y1X2Y2C(str);
		break;
	case 'F':
		HandleFXYC(str);
		break;
	case 'S':
		HandleSName(str);
		break;
	case 'X':
		HandleX();
		return -1;
		break;
	default:
		return 0;
	}
	return 0;
}

/*
	I M N:创建一个新的M*N图像，所有图像为白色
*/
void HandleIMN(string str)
{
	// 1.先解析str I M N
	char ch;
	sscanf(str.c_str(), "%c %d %d", &ch, &M, &N);
	// 创建一个M*N的图像，由于M、N已经赋值，因此只需要clear就行了
	// 清空
	HandleC();
}

/*
	C:清除图像，所有图像为白色（0）
*/
void HandleC()
{
	// 遍历
	for (int i = 0; i < M; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			matrix[i][j] = 'O';
		}
	}
}


/*
	把图像（X，Y）涂成C
*/
void HandleLXYC(string str)
{
	char ch1;
	int X;
	int Y;
	char color;
	sscanf(str.c_str(), "%c %d %d %c", &ch1, &X, &Y, &color);
	matrix[X - 1][Y - 1] = color;
}

/*
	画一条竖线:颜色为C，列号为X，从第Y1到Y2行
*/
void HandleVXY1Y2C(string str)
{
	char ch1;
	int X;
	int Y1;
	int Y2;
	char color;
	sscanf(str.c_str(), "%c %d %d %d %c", &ch1, &X, &Y1, &Y2, &color);
	if (Y1 > Y2)
	{
		swap(Y1, Y2);
	}
	for (int i = Y1; i <= Y2; ++i)
	{
		matrix[X - 1][i - 1] = color;
	}
}

/*
	画一条水平线，颜色为C，行号为Y，从X1到X2
*/
void HandleHX1X2YC(string str)
{
	char ch1;
	int X1;
	int X2;
	int Y;	
	char color;
	sscanf(str.c_str(), "%c %d %d %d %c", &ch1, &X1, &X2, &Y, &color);
	if (X1 > X2)
	{
		swap(X1, X2);
	}
	for (int i = X1; i <= X2; ++i)
	{
		matrix[i - 1][Y - 1] = color;
	}
}

/*
	画一个矩形，颜色为C，左上角（X1，Y1),右下角（X2, Y2)
*/
void HandleKX1Y1X2Y2C(string str)
{
	char ch1;
	int X1;
	int Y1;
	int X2;
	int Y2;	
	char color;
	sscanf(str.c_str(), "%c %d %d %d %d %c", &ch1, &X1, &Y1, &X2, &Y2, &color);
	if (X1 > X2)
	{
		swap(X1, X2);
	}
	if (Y1 > Y2)
	{
		swap(Y1, Y2);
	}
	for (int i = X1; i <= X2; ++i)
	{
		for (int j = Y1; j <= Y2; ++j)
		{
			matrix[i - 1][j - 1] = color;
		}
	}
}

/*
	把区域R填充为C，若像素（x，y）属于R，则所有与R有公共边且颜色相同的像素也属于R
*/
void HandleFXYC(string str)
{
	// 类似于种子点填充
	char ch1;
	int X;
	int Y;
	char color;
	sscanf(str.c_str(), "%c %d %d %c", &ch1, &X, &Y, &color); 
	// 记录X、Y的颜色
	char cxy = matrix[X - 1][Y - 1];
	
	// 构造一个stack，
	stack<int> istack;
	bool map[300][300] = {false};
	istack.push(Y - 1);
	istack.push(X - 1);
	while (!istack.empty())
	{
		int x = istack.top();
		istack.pop();
		int y = istack.top();
		istack.pop();
		// 判断x、y是否出界,颜色是否不对、是否已经访问过
		if (x < 0 || x == M || y < 0 || y == N ||
			matrix[x][y] != cxy || map[x][y])
		{
			continue;
		}
		// 将x、y填充为color，并且将周围的四个地方填入
		matrix[x][y] = color;
		map[x][y] = true;

		for (int i = 0; i < 4; ++i)
		{
			int nX = x + rec[i][0];
			int nY = y + rec[i][1];
			// 如果满足条件，加入
			if (nX >= 0 && nX < M && nY >= 0 && nY < N &&
				!map[nX][nY] && matrix[nX][nY] == cxy)
			{
				istack.push(nY);
				istack.push(nX);				
			}
		}

		//// 上面	
		//istack.push(x);
		//istack.push(y - 1);
		//// 右面
		//istack.push(x + 1);
		//istack.push(y);
		//// 下面
		//istack.push(x);
		//istack.push(y + 1);
		//// 左面
		//istack.push(x - 1);
		//istack.push(y);
	}

}

/*
	原样输出文件名以及图像像素
*/
void HandleSName(string str)
{
	string strName = str.substr(2);
	cout << strName << endl;
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			cout << matrix[j][i];
		}
		cout << endl;
	}
}

/*
	退出程序
*/
void HandleX()
{
}

void TestFill()
{
	// 1.初始化matrix	
	string str1 = "I 3 4";
	HandleIMN(str1);
	string str2 = "L 3 1 T";
	HandleLXYC(str2);
	string str3 = "L 3 4 T";
	HandleLXYC(str3);
	HandleSName("1.bmp");
	string str4 = "F 2 2 M";
	HandleFXYC(str4);
	HandleSName("1.bmp");
}