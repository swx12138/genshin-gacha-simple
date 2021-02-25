#include <iostream>
#include <string>
#include <random>
#include <unordered_set>
#include <sstream>

using namespace std;

namespace pool {
	const unordered_set<string> char5 = {
		"��¬��","��","Ī��","����","����"
	};

	const unordered_set<string> char4 = {
		"�Ű���","������","�ϰ���","��л��","��ɯ","����","ŵ����","����","����","ɰ��",
		"����","����","����","����","����","����"
	};

	const unordered_set<string> char5x = {
		"�µ�","����","�������","����","������","����","��"
	};

	const string char5up = *char5.find("����");

	const unordered_set<string> weapon5 = {
		"����"
	};

	const unordered_set<string> weapon4{
		"����"
	};
}

class Gacha
{
public:
	Gacha()
	{
		cout << "��ʼ����֮Ե��"; cin >> res.pink;
		cout << "��ʼ����֮Ե��"; cin >> res.blue;
		cout << "��ʼԭʯ��"; cin >> res.stone;
		cout << "봽�ԭʯ��"; cin >> res.stone_x;
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
		cout << t << "�飺" << endl;

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
		cout << "ǿȢ��" << want << "\t������" << nC << endl;

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
		cout << "����֮Ե��" << res.blue
			<< "\t����֮Ե��" << res.pink
			<< "\tԭʯ��" << res.stone
			<< "\t봽�ԭʯ��" << res.stone_x
			<< "\nǮ��" << res.money
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
			debugMsg << "��" << nT5 << "����������";
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

					debugMsg << "��ɫ��" << first << (da ? ",��" : ",����") << "�󱣵�,�ܼƵ�" << nCount << "��" << endl;
					da = false;
				}
				else
				{
					second = -second;
					first = rand(pool::char5);

					debugMsg << "��ɫ��" << first << ",����" << "�󱣵�,�ܼƵ�" << nCount << "��" << endl;
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
				first = "����";
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
	unsigned int nCount = 0;	// �鿨����
	unsigned short nT5 = 0;		// ���Ǳ���
	unsigned short nT4 = 0;		// ���Ǳ���
	bool da = false;			// �󱣵�
	stringstream debugMsg;		// �鿨��Ϣ
};

int main()
{
	Gacha gacha;

	system("cls");
	//gacha.roll_x(200);
	//gacha.roll_x("����", 7);
	//gacha.roll_ten_x();

	int nCode = 1145;
	while(nCode)
	{
		cout << "\n\t\t/\\**** �� �� ģ �� �� -- �� Լ ****/\\\n"
			<< "�����Ӧ����ѡ����:\n"
			<< "\t[0]�˳�\n"
			<< "\t[1]��ɫup����\n"
			<< "\t[2]��ɫupʮ��\n"
			<< "\t[3]��ɫup��n��\n"
			<< "\t[4]ǿȢģʽ"
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
				cout << "�鿨������";
				cin >> n;
				gacha.roll_x(n);
			}
			break;
			case 4:
			{
				string name = ""; int nCo = 0;
				cout << "���ǽ�ɫ�����֣�";
				cin >> name;
				cout << "��鼸����";
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

				cout << "��ѡ��ɫĿǰ�޷���ȡ" << endl;
			}
			break;
		}
		continue;
	}

	return 0;
}