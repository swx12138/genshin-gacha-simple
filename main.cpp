#include <iostream>
#include <iomanip>

#include "console.hpp"
#include "gacha.hpp"

int main()
{
	console::SetTextWhite();
	GachaX *pGacha = new GachaX{};

	int nCode = 1145;
	while(nCode)
	{
		console::SetTextPink();
		std::cout << "\t\t/** ** ** ** �� �� ģ �� �� ** ** ** **\\\n";
		std::cout << "�����Ӧ����ѡ����:" << std::endl;
		console::SetTextRed();
		std::cout << "\t[0]�˳�" << std::endl;
		console::SetTextGreen();
		std::cout << "\t[1]��ɫup����" << std::endl;
		console::SetTextBlue();
		std::cout << "\t[2]��ɫupʮ��" << std::endl;
		console::SetTextRed();
		std::cout << "\t[3]��ɫup��n��" << std::endl;
		console::SetTextGreen();
		std::cout << "\t[4]ǿȢģʽ" << std::endl;
		console::SetTextBlue();
		std::cout << "\t[5]��λ" << std::endl;
		console::SetTextPink();
		std::cout << "/* * * * * * * * * * * * * * * * * * * * * * * * * * *\\\n";
		console::SetTextWhite();


		if(![&pGacha, &nCode] {
			std::cin >> nCode;
				switch(nCode)
				{
					case 0:
						return false;
					case 1:
						gacha::write_name(pGacha->roll());
							break;
					case 2:
						gacha::write_name(pGacha->roll(10));
							break;
					case 3:
						gacha::write_name(pGacha->roll([] {
							int n = 0;
							std::cout << "�鿨������";
							std::cin >> n;
							return n;
						}()));
						break;
					case 4:
						[pGacha] {
							std::string name = "";
							int nCo = 0;

							for(auto &e : pGacha->get_char_list())
							{
								static int a = 0;
								if(e.second == 4) console::SetTextPink();
								else if(e.second == 5)console::SetTextGolden();
								std::cout << e.first << "  ";
								console::SetTextWhite();
								if(!(++a % 10)) std::cout << std::endl;
							}

							std::cout << "���ǽ�ɫ�����֣�";
							std::cin >> name;
							std::cout << "��鼸����";
							std::cin >> nCo;

							while(++nCo < 0)
							{
								std::cout << "???��˵һ�鼸��?" << std::endl;
								std::cin >> nCo;
							}

							if(pGacha->inPool(name))
							{
								gacha::write_name(pGacha->iwant(name, nCo));
								return;
							}

							std::cout << "��ѡ��ɫĿǰ�޷���ȡ" << std::endl;
							return;
						}();
						break;
					case 5:
					{
						delete pGacha;
						pGacha = new GachaX{ };
						system("cls");
					}
				}
			return true;
		}()) break;
	}

	return 0;
}