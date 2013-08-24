
#include <string>
#include <cstring>
#include <iostream>
#include <queue>
#include <map>

using namespace std;

#define MAXN 100
#define EARLIER 18
#define LATER 6
#define HOURS 24
#define NO_ROUTE (-1)

// 当前路线的状态，其中 city 标志当前到达的城市，time 表示到达的时间，litres 表示已经使用的血量。
class state
{
public:
	int city, time, litres;

	// 使用血量少的路线先处理。
	bool operator<(const state at) const
	{
		return litres > at.litres;
	}
	state(int _city, int _time, int _litres)
	{
		city = _city;
		time = _time;
		litres = _litres;
	}
};

// 火车路线。
class route
{
public:
	int departure;		// 出发时间。
	int arrive;		// 到达时间。
	int to;			// 到达城市。

	route(int _dep, int _arr, int _to)
	{
		departure = _dep;
		arrive = _arr;
		to = _to;
	}
};

// 城市之间的火车路线。
vector < route > edges[MAXN + 1];

// 使用优先队列的方法来遍历所有从起始城市 from 到 终点城市 to 的路线。在此过程中，先处理使用血
// 量少的路线，当发现当前路线的状态 state 所标志的城市 city 已经为目标城市 to 时，表明当前需要
// 血量最少的路线即为该 state 所走的路线。
int travel(int from, int to)
{
	// 建立优先队列，需要血量少的路线先处理。
	priority_queue < state > states;

	// 将当前城市为 from，到达时间为 18:00 的状态添加到优先队列中，表示已经从一个虚拟的地
	// 方到达了起始城市 from，到达时间小于起始城市 from 的所有可用火车路线的出发时间，当前
	// 已经使用血量为 0 升。
	states.push(state(from, EARLIER, 0));

	// 处理队列中的路线状态。
	while (!states.empty())
	{
		// 取出队首的路线状态处理。
		state current = states.top();
		states.pop();

		// 若当前城市已经为目标城市，则直接返回当前路线所使用的血量。
		if (current.city == to)
			return current.litres;

		// 遍历当前到达城市至其他城市的火车路线，根据情况决定是否需要取用 1 升的血。
		for (int r = 0; r < edges[current.city].size(); r++)
		{
			int used = current.litres;
			// 若到达时间晚于该火车路线出发时间，则需在此车站停留一个中午，取血 1 升。
			if (current.time > edges[current.city][r].departure)
				used++;

			states.push(state(edges[current.city][r].to,edges[current.city][r].arrive, used));
		}

	}

	// 起始城市与目标城市无连通路线。
	return NO_ROUTE;
}

int main(int ac, char *av[])
{
	int test, routes, cases = 1;
	int from, to;
	string start, destination;
	int departure, traveling;

	cin >> test;
	while (test--)
	{
		map < string, int > cities;

		for (int i = 0; i < MAXN + 1; i++)
			edges[i].clear();

		cin >> routes;
		for (int i = 1; i <= routes; i++)
		{
			// 读入起始和终点城市、出发时间、旅行时间，并将其插入到 map 中。
			cin >> start >> destination >> departure >> traveling;

			if (cities.find(start) == cities.end())
			{
				from = cities.size();
				cities[start] = from;
			}
			else
				from = cities[start];

			if (cities.find(destination) == cities.end())
			{
				to = cities.size();
				cities[destination] = to;
			}
			else
				to = cities[destination];

			// 满足条件的路线则添加到有向图中。若出发时间为凌晨，则加上 24 小时
			// 以统一时间起点。
			departure += (departure <= LATER ? HOURS : 0);
			if (departure >= EARLIER
				&& (departure + traveling) <= (HOURS + LATER))
				edges[from].push_back(route(departure,
						(departure + traveling), to));
		}

		// 出发和到达城市。
		cin >> start >> destination;

		cout << "Test Case " << cases++ << "." << endl;

		// 处理特殊情况：起始和目标城市相同。
		if (start == destination)
		{
			cout << "Vladimir needs 0 litre(s) of blood." << endl;
			continue;
		}

		// 处理特殊情况：起始或目标城市不在输入数据中。
		if (cities.find(start) == cities.end()
			|| cities.find(destination) == cities.end())
		{
			cout << "There is no route Vladimir can take." << endl;
			continue;
		}

		// 取出起始和目标城市的序号。
		from = cities[start];
		to = cities[destination];

		// 遍历所有路线以找到从城市 from 到城市 to 所需的最少血量。
		int litres = travel(from, to);

		if (litres == NO_ROUTE)
			cout << "There is no route Vladimir can take." << endl;
		else
			cout << "Vladimir needs " << litres << " litre(s) of blood." << endl;
	}

	return 0;
}