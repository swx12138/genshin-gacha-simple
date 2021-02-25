#include <iostream>
#include <string>
#include <random>
#include <unordered_set>
#include <sstream>

using namespace std;

namespace pool {
	const unordered_set<string> char5 = {
		"迪卢克","琴","莫娜","七七","刻晴"
	};

	const unordered_set<string> char4 = {
		"芭芭拉","班尼特","迪奥娜","菲谢尔","丽莎","雷泽","诺艾尔","凯亚","安柏","砂糖",
		"凝光","重云","北斗","香菱","行秋","辛焱"
	};

	const unordered_set<string> char5x = {
		"温迪","可莉","达达利亚","钟离","阿贝多","甘雨","魈"
	};

	const string char5up = *char5.find("刻晴");

	const unordered_set<string> weapon5 = {
		"五星"
	};

	const unordered_set<string> weapon4{
		"四星"
	};
}

class Gacha
{
public:
	Gacha()
	{
		cout << "初始纠缠之缘："; cin >> res.pink;
		cout << "初始相遇之缘："; cin >> res.blue;
		cout << "初始原石："; cin >> res.stone;
		cout << "氪金原石："; cin >> res.stone_x;
	}

	short roll_once_x()
	{
		nCount++;
		cout << roll_main().first << endl;
		output_debug_msg();
		return nT5;
	}

	short roll_ten_x()
	{
		nCount += 10;

		for(int i = 0; i < 10; i++)
			cout << roll_main().first << "\t";
		cout << endl;

		output_debug_msg();
		return nT5;
	}

	short roll_x(int t)
	{
		cout << t << "抽：" << endl;

		for(auto i = 0; i < t;)
		{
			nCount++;
			cout << roll_main().first << "\t";
			if(!(++i % 10)) cout << endl;
		}
		cout << endl;

		output_debug_msg();
		return nT5;
	}

	int roll_x(const string &want, int nC = 1)
	{
		cout << "强娶：" << want << "\t数量：" << nC << endl;

		while(nC)
		{
			static pair<string, short> ret;
			static int i = 0;

			nCount++;
			ret = roll_main();
			cout << ret.first << "\t";

			if(!(++i % 10)) cout << endl;
			if(want == ret.first) nC--;
		}
		cout << endl;

		output_debug_msg();
		return nCount;
	}

	void get_res() const
	{
		cout << "相遇之缘：" << res.blue
			<< "\t纠缠之缘：" << res.pink
			<< "\t原石：" << res.stone
			<< "\t氪金原石：" << res.stone_x
			<< "\n钱：" << res.money
			<< endl;
	}

private:
	void buy_stone_x()
	{
		res.money -= 648;
		res.stone_x += 8048;
	}

	void buy_stone(int n)
	{
		if(res.stone_x < n) buy_stone_x();
		res.stone_x -= n;
		res.stone += n;
	}

	void buy_pink(int n)
	{
		if(res.stone < n * 160) buy_stone(1600 - res.stone);
		res.stone -= 160 * n;
		res.pink += n;
	}

	static string rand(const unordered_set<string> &names)
	{
		vector<string> temp(names.begin(), names.end());
		return move(temp[random_device{}() % temp.size()]);
	}

	int roll_base()
	{
		static uniform_int_distribution<> dist(0, 999);
		mt19937 gen(random_device{}());
		int dg = dist(gen);

		if((dg -= (6 + (nT5 > 70 ? nT5 - 70 : 0) * 50)) < 0)
		{
			debugMsg << "第" << nT5 << "抽抽出了五星";
			nT5 = 0;
			return 5;
		}
		else
		{
			nT5++;
		}

		if((dg -= (51 + (nT4 > 5 ? nT4 - 5 : 0) * 250)) < 0)
		{
			nT4 = 0;
			return 4;
		}
		else
		{
			nT4++;
		}

		return 3;
	}

	pair<string, short> roll_main()
	{
		while(res.pink <= 0) buy_pink(1);
		res.pink--;

		string first = "";
		short second = roll_base();

		switch(second)
		{
			case 5:
			{
				if(da || random_device{}() % 2)
				{
					first = pool::char5up;

					debugMsg << "角色：" << first << (da ? ",是" : ",不是") << "大保底,总计第" << nCount << "抽" << endl;
					da = false;
				}
				else
				{
					second = -second;
					first = rand(pool::char5);

					debugMsg << "角色：" << first << ",不是" << "大保底,总计第" << nCount << "抽" << endl;
					da = true;
				}
			}
			break;
			case 4:
			{
				first = random_device{}() % 2 ? rand(pool::char4) : rand(pool::weapon4);
			}
			break;
			case 3:
			{
				first = "三星";
			}
		}
		return { first,second };
	}

	void output_debug_msg()
	{
		cout << debugMsg.str() << endl;
		debugMsg.str("");
		get_res();
	}

private:
	struct __RES
	{
		int pink = 0;
		int blue = 0;
		int stone = 0;
		int stone_x = 0;
		int money = 0;
	}res;
	unsigned int nCount = 0;	// 抽卡次数
	unsigned short nT5 = 0;		// 五星保底
	unsigned short nT4 = 0;		// 四星保底
	bool da = false;			// 大保底
	stringstream debugMsg;		// 抽卡信息
};

int main()
{
	Gacha gacha;

	system("cls");
	//gacha.roll_x(200);
	//gacha.roll_x("刻晴", 7);
	//gacha.roll_ten_x();

	int nCode = 1145;
	while(nCode)
	{
		cout << "\n\t\t/\\**** 抽 卡 模 拟 器 -- 简 约 ****/\\\n"
			<< "输入对应数字选择功能:\n"
			<< "\t[0]退出\n"
			<< "\t[1]角色up单抽\n"
			<< "\t[2]角色up十连\n"
			<< "\t[3]角色up抽n次\n"
			<< "\t[4]强娶模式"
			<< endl;

		cin >> nCode;
		switch(nCode)
		{
			case 0:
				break;
			case 1:
				gacha.roll_once_x();
				break;
			case 2:
				gacha.roll_ten_x();
				break;
			case 3:
			{
				int n = 0;
				cout << "抽卡次数：";
				cin >> n;
				gacha.roll_x(n);
			}
			break;
			case 4:
			{
				string name = ""; int nCo = 0;
				cout << "心仪角色的名字：";
				cin >> name;
				cout << "想抽几命：";
				cin >> nCo;

				if(++nCo < 0)
				{
					cout << "???" << endl;
					break;
				}

				if(pool::char5up == name)
				{
					gacha.roll_x(name, nCo);
					break;
				}

				for(const auto e : pool::char5)
				{
					if(e == name) gacha.roll_x(e, nCo);
					break;
				}

				cout << "所选角色目前无法获取" << endl;
			}
			break;
		}
		continue;
	}

	return 0;
}