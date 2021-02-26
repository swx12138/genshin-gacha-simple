#include <iostream>
#include <string>
#include <random>
#include <unordered_set>
#include <sstream>
#include <Windows.h>

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

class console
{
public:
	static BOOL SetTextWhite()
	{
		return SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
	static BOOL SetTextRed()
	{
		return SetConsoleTextAttribute(hStdOut, FOREGROUND_INTENSITY | FOREGROUND_RED);
	}
	static BOOL SetTextGreen()
	{
		return SetConsoleTextAttribute(hStdOut, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	}
	static BOOL SetTextBlue()
	{
		return SetConsoleTextAttribute(hStdOut, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	}
	static BOOL SetTextPink()
	{
		return SetConsoleTextAttribute(hStdOut, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
	}
	static BOOL SetTextGreenBlue()
	{
		return SetConsoleTextAttribute(hStdOut, FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
	static BOOL SetTextGolden()
	{
		return SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN);
	}
private:
	static HANDLE hStdOut;
};

HANDLE console::hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

class Gacha
{
	using xx = pair<string, short>;
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
		write_name(roll_main());
		output_debug_msg();
		return nT5;
	}

	short roll_ten_x()
	{
		nCount += 10;

		for(int i = 0; i < 10; i++)
			write_name(roll_main());
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
			write_name(roll_main());
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
			static xx ret;
			static int i = 0;

			nCount++;
			ret = roll_main();
			write_name(ret);

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
			<< "\n�ܼƳ�����" << nCount
			<< "\tǮ��" << res.money
			<< endl;
	}

private:
	void write_name(const xx &r)
	{
		if(3 == r.second) console::SetTextGreenBlue();
		else if(4 == r.second) console::SetTextPink();
		else if(5 == r.second) console::SetTextGolden();
		cout << r.first << "\t";
		console::SetTextWhite();
	}

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

	xx roll_main()
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

					debugMsg << "��ɫ��[" << first << (da ? "],��" : ",����") << "�󱣵�,�ܼƵ�" << nCount << "��" << endl;
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
	console::SetTextWhite();
	Gacha *pGacha = new Gacha{};

	system("cls");
	//gacha.roll_x(200);
	//gacha.roll_x("����", 7);
	//gacha.roll_ten_x();

	int nCode = 1145;
	while(nCode)
	{
		console::SetTextPink();
		cout << "\t\t/\\** ** ** ** �� �� ģ �� �� ** ** ** **/\\\n";
		cout << "�����Ӧ����ѡ����:" << endl;
		console::SetTextRed();
		cout << "\t[0]�˳�" << endl;
		console::SetTextGreen();
		cout << "\t[1]��ɫup����" << endl;
		console::SetTextBlue();
		cout << "\t[2]��ɫupʮ��" << endl;
		console::SetTextRed();
		cout << "\t[3]��ɫup��n��" << endl;
		console::SetTextGreen();
		cout << "\t[4]ǿȢģʽ" << endl;
		console::SetTextBlue();
		cout << "\t[5]��λ" << endl;
		console::SetTextPink();
		cout << "/\\* * * * * * * * * * * * * * * * * * * * * * * * * * */\\\n";
		console::SetTextWhite();

		cin >> nCode;
		switch(nCode)
		{
			case 0:
				break;
			case 1:
				pGacha->roll_once_x();
				break;
			case 2:
				pGacha->roll_ten_x();
				break;
			case 3:
			{
				int n = 0;
				cout << "�鿨������";
				cin >> n;
				pGacha->roll_x(n);
			}
			break;
			case 4:
				[pGacha] {
					string name = ""; int nCo = 0;
					cout << "���ǽ�ɫ�����֣�";
					cin >> name;
					cout << "��鼸����";
					cin >> nCo;

					while(++nCo < 0)
					{
						cout << "???��˵һ�鼸��?" << endl;
						cin >> nCo;
					}

					if(pool::char5up == name)
					{
						pGacha->roll_x(name, nCo);
						return;
					}

					for(const auto e : pool::char5)
					{
						if(e == name)
						{
							pGacha->roll_x(e, nCo);
							return;
						}
					}

					cout << "��ѡ��ɫĿǰ�޷���ȡ" << endl;
				}();
				break;
			case 5:
			{
				delete pGacha;
				pGacha = new Gacha{ };
				system("cls");
				pGacha->get_res();
			}
		}
		continue;
	}

	return 0;
}