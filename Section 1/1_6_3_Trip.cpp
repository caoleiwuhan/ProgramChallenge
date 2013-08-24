#include <iostream>
#include <cstdio>

using namespace std;

/*
	考虑用整数存！！！
*/

/*
	输入：money数组，学生数
	读入每个学生的money
*/
void InputMoney(double money[], int stuNum)
{
	for (int i = 0; i < stuNum; ++i)
	{
		cin >> money[i];
	}
}

/*
	输入num
	将一个double数据四舍五入保留2位小数
*/
double ChangeNum(double num)
{
	return ((int)(num * 100 + 0.5)) / 100.0;
}

/*
	输入money和学生数，返回花费的平均数
*/
double AverageMoney(double money[], int stuNum)
{
	double average = 0.0;
	double total = 0.0;
	for (int i = 0; i < stuNum; ++i)
	{
		total += money[i];
	}
	total = ChangeNum(total);
	average = ChangeNum(total / stuNum);
	return average;
}

/*
	输入：每个学生的花费，学生数
	计算总交易数
	输出总交易数
*/
double TotalMoney(double money[], int stuNum)
{
	// 1.计算平均数:已经四舍五入保留两位小数
	double average = AverageMoney(money, stuNum);
	double ans1 = 0.0;
	double ans2 = 0.0;

	for (int i = 0; i < stuNum; ++i)
	{
		if (money[i] > average)
		{
			ans1 += (money[i] - average);
		}
		else
		{
			ans2 += (average - money[i]);
		}
	}
	if (ans1 > ans2)
	{
		ans1 = ans2;
	}
	return ans1;
}

void TestOutPut()
{
	double d1 = 36.02;
	double d2 = d1 / 4;
	d2 = ChangeNum(d2);
	double d3 = 15.00 - d2;
	double d4 = 15.01 - d2;
	double d5 = d3 + d4;
	

	printf("%.2f\n", d1);
	printf("%.2f\n", d2);
	printf("%.2f\n", d3);
	printf("%.2f\n", d4);
	printf("%.2f\n", d5);
}

int main()
{
	// 学生数
	int stuNum = 0;
	// 存储每个学生的钱数，不超过1000
	double money[1000];
	// 交易的总钱数
	double total = 0.0;
	while (cin >> stuNum)
	{
		if (stuNum == 0)
		{
			break;
		}
		// 读入学生的钱数
		InputMoney(money, stuNum);
		// 计算总的交换钱数
		total = TotalMoney(money, stuNum);
		printf("$%.2f\n", total);
	}

	//TestOutPut();
	return 0;
}

