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
		std::cout << "\t\t/** ** ** ** 抽 卡 模 拟 器 ** ** ** **\\\n";
		std::cout << "输入对应数字选择功能:" << std::endl;
		console::SetTextRed();
		std::cout << "\t[0]退出" << std::endl;
		console::SetTextGreen();
		std::cout << "\t[1]角色up单抽" << std::endl;
		console::SetTextBlue();
		std::cout << "\t[2]角色up十连" << std::endl;
		console::SetTextRed();
		std::cout << "\t[3]角色up抽n次" << std::endl;
		console::SetTextGreen();
		std::cout << "\t[4]强娶模式" << std::endl;
		console::SetTextBlue();
		std::cout << "\t[5]复位" << std::endl;
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
							std::cout << "抽卡次数：";
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

							std::cout << "心仪角色的名字：";
							std::cin >> name;
							std::cout << "想抽几命：";
							std::cin >> nCo;

							while(++nCo < 0)
							{
								std::cout << "???再说一遍几命?" << std::endl;
								std::cin >> nCo;
							}

							if(pGacha->inPool(name))
							{
								gacha::write_name(pGacha->iwant(name, nCo));
								return;
							}

							std::cout << "所选角色目前无法获取" << std::endl;
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