#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>

using namespace std;

// register
int reg[11];
// memory
int memory[1010];

/*
	输入memory，开始解析计算，
	返回一共执行的次数
*/
int Execute();

/*
	输入一个三位数，得到第二位，第三位的值
*/
void ParseNum(int num, int &n2, int &n3);

void Test();


//int main()
//{
//	//cout << "Test" << endl;
//	int count = 0;	
//	cin >> count;
//
//	char ch;
//	// 读入第一个空行
//	ch = cin.get();
//
//	while (count--)
//	{
//		memset(memory, 0, sizeof(memory));
//		memset(reg, 0, sizeof(reg));
//		// 内存的index
//		int index = 0;
//		// 从控制台读入内存的数
//		int num = 0;
//
//		while (true)
//		{
//			ch = cin.get();
//			ch = cin.peek();
//			if (ch == '\n')
//			{
//				break;
//			}
//			else
//			{
//				cin >> num;
//				memory[index++] = num;
//			}
//		}
//		cout << Execute() << endl;
//		if (count)
//		{
//			cout << endl;
//		}
//	}
//	return 0;
//}


int main()
{
	int count = 0;	
	cin >> count;

	getchar();
	getchar();

	char buf[11];

	while (count--)
	{
		memset(memory, 0, sizeof(memory));
		memset(reg, 0, sizeof(reg));
		// 内存的index
		int index = 0;
		// 从控制台读入内存的数
		int num = 0;

		while (gets(buf))
		{			
			if (buf[0] == '\0')
			{
				break;
			}			
			sscanf(buf, "%d", &memory[index]);
			++index;			
		}

		cout << Execute() << endl;
		if (count)
		{
			cout << endl;
		}
	}

	return 0;
}

int Execute()
{
	// 指令执行的总数
	int ans = 0;
	// 从0开始
	// 内存中的index
	int curIndex = 0;
	// 当前执行的指令
	int instr = memory[curIndex];

	while (instr != 100)
	{
		// 下一条
		++curIndex;
		++ans;
		// 当前指令的类型
		int kind = instr / 100;
		int d = 0;
		int n = 0;
		int s = 0;
		int a = 0;
		switch(kind)
		{
		case 2:
			ParseNum(instr, d, n);
			// 将寄存器的值设为n
			reg[d] = n;
			break;
		case 3:			
			ParseNum(instr, d, n);
			// 将寄存器的值增加N
			reg[d] = (reg[d] + n) % 1000;
			break;
		case 4:
			ParseNum(instr, d, n);
			// 将寄存器的值乘以N
			reg[d] = (reg[d] * n) % 1000;
			break;
		case 5:
			ParseNum(instr, d, s);
			// 将s的值赋给d
			reg[d] = reg[s];
			break;
		case 6:
			ParseNum(instr, d, s);
			// 将s的值加到d
			reg[d] = (reg[d] + reg[s]) % 1000;
			break;
		case 7:
			ParseNum(instr, d, s);
			// 将s的值乘给d
			reg[d] = (reg[d] * reg[s]) % 1000;
			break;
		case 8:
			ParseNum(instr, d, a);
			reg[d] = memory[reg[a]];
			break;
		case 9:
			ParseNum(instr, s, a);
			memory[reg[a]] = reg[s];
			break;		
		case 0:
			ParseNum(instr, d, s);
			if (reg[s])
			{
				curIndex = reg[d];
			}
			break;
		}
		instr = memory[curIndex];
	}
	++ans;
	return ans;
}


void ParseNum(int num, int &n2, int &n3)
{
	n3 = num % 10;
	n2 = (num / 10) % 10;
}

void Test()
{
	// 测试078
	//int num;
	//cin >> num;
	//memory[0] = num;

	memset(memory, 0, sizeof(memory));
	memset(reg, 0, sizeof(reg));

	memory[0] = 299;
	memory[1] = 492;
	memory[2] = 495;
	memory[3] = 399;
	memory[4] = 492;
	memory[5] = 495;
	memory[6] = 399;
	memory[7] = 283;
	memory[8] = 279;
	memory[9] = 689;
	memory[10] = 78;
	memory[11] = 100;
	memory[12] = 0;
	memory[13] = 0;
	memory[14] = 0;
	Execute();
}