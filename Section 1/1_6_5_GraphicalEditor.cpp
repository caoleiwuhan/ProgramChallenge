#include <iostream>
#include <string>
#include <stack>
#include <cstdio>

using namespace std;

/*
	û��ע��X1��X2�Ĵ�С��ϵ������
*/

// ���ص�
char matrix[300][300];

// ������
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

// ����str����ִ����Ӧ����
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

// �������ӵ����
void TestFill();

int main()
{
	//cout << "Test" << endl;
	string str;
	while (getline(cin, str))
	{
		//cout << str << endl;
		// ����str��ִ��
		if (ParseStrAndExe(str) == -1)
		{
			break;
		}
	}

	//TestFill();

	return 0;
}

/*
	����str����ִ����Ӧ�ĺ���
	����ֵ��
		0������
		-1��exit
*/
int ParseStrAndExe(string str)
{
	// 1.ȡ�õ�һ����ĸ
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
	I M N:����һ���µ�M*Nͼ������ͼ��Ϊ��ɫ
*/
void HandleIMN(string str)
{
	// 1.�Ƚ���str I M N
	char ch;
	sscanf(str.c_str(), "%c %d %d", &ch, &M, &N);
	// ����һ��M*N��ͼ������M��N�Ѿ���ֵ�����ֻ��Ҫclear������
	// ���
	HandleC();
}

/*
	C:���ͼ������ͼ��Ϊ��ɫ��0��
*/
void HandleC()
{
	// ����
	for (int i = 0; i < M; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			matrix[i][j] = 'O';
		}
	}
}


/*
	��ͼ��X��Y��Ϳ��C
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
	��һ������:��ɫΪC���к�ΪX���ӵ�Y1��Y2��
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
	��һ��ˮƽ�ߣ���ɫΪC���к�ΪY����X1��X2
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
	��һ�����Σ���ɫΪC�����Ͻǣ�X1��Y1),���½ǣ�X2, Y2)
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
	������R���ΪC�������أ�x��y������R����������R�й���������ɫ��ͬ������Ҳ����R
*/
void HandleFXYC(string str)
{
	// ���������ӵ����
	char ch1;
	int X;
	int Y;
	char color;
	sscanf(str.c_str(), "%c %d %d %c", &ch1, &X, &Y, &color); 
	// ��¼X��Y����ɫ
	char cxy = matrix[X - 1][Y - 1];
	
	// ����һ��stack��
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
		// �ж�x��y�Ƿ����,��ɫ�Ƿ񲻶ԡ��Ƿ��Ѿ����ʹ�
		if (x < 0 || x == M || y < 0 || y == N ||
			matrix[x][y] != cxy || map[x][y])
		{
			continue;
		}
		// ��x��y���Ϊcolor�����ҽ���Χ���ĸ��ط�����
		matrix[x][y] = color;
		map[x][y] = true;

		for (int i = 0; i < 4; ++i)
		{
			int nX = x + rec[i][0];
			int nY = y + rec[i][1];
			// �����������������
			if (nX >= 0 && nX < M && nY >= 0 && nY < N &&
				!map[nX][nY] && matrix[nX][nY] == cxy)
			{
				istack.push(nY);
				istack.push(nX);				
			}
		}

		//// ����	
		//istack.push(x);
		//istack.push(y - 1);
		//// ����
		//istack.push(x + 1);
		//istack.push(y);
		//// ����
		//istack.push(x);
		//istack.push(y + 1);
		//// ����
		//istack.push(x - 1);
		//istack.push(y);
	}

}

/*
	ԭ������ļ����Լ�ͼ������
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
	�˳�����
*/
void HandleX()
{
}

void TestFill()
{
	// 1.��ʼ��matrix	
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