#pragma once


#include <random>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <ostream>
#include <sstream>

#include <jsonxx/json.hpp>

class gacha
{
protected:
	constexpr static const int POOL_5 = 5;
	constexpr static const int POOL_4 = 4;
	constexpr static const int POOL_3 = 3;
	constexpr static const int POOL_UP_5 = 2;
	constexpr static const int POOL_UP_4 = 1;
	virtual std::string im() const = 0;
protected:
	using json_t = jsonxx::json;
	using name_star = std::pair<std::string, unsigned short>;
	using ret_list = std::vector<name_star>;
	using pool_t = std::map<int, std::set<name_star>>;

protected:
	inline void buy_stone_x()
	{
		res.money -= 648;
		res.stone_x += 8048;
	}

	inline void buy_stone(int n)
	{
		if(res.stone_x < n) buy_stone_x();
		res.stone_x -= n;
		res.stone += n;
	}

	inline void buy_pink(int n)
	{
		if(res.stone < 160 * n) buy_stone(160 * n - res.stone);
		res.stone -= 160 * n;
		res.pink += n;
	}

public:
	inline ret_list roll(int nTimes = 1)
	{
		if(res.pink < nTimes) buy_pink(nTimes - res.pink);
		ret_list rl(nTimes);
		for(auto &e : rl)
		{
			e = roll_main();
		}
		return std::move(rl);
	}

	inline ret_list iwant(const std::string &who, int nHowMany)
	{
		ret_list rl;
		while(!who.empty() && nHowMany > 0)
		{
			rl.push_back(roll_main());
			if(who == rl.rbegin()->first) nHowMany--;
		}
		return std::move(rl);
	}

	static void write_name(const ret_list &ret)
	{
		std::stringstream ss;
		int n = 0;
		int m = 0;
		for(auto &e : ret)
		{
			static int o = 0;
			if(3 == e.second) console::SetTextGreenBlue();
			else if(4 == e.second) console::SetTextPink();
			else if(5 == e.second)
			{
				m++;
				ss << "第" << n << "次获得  " << e.first << " ,距离上次" << o << "抽。" << std::endl;
				console::SetTextGolden();
				o = 0;
			}
			std::cout << e.first << "\t";
			if(!(++n % 10)) std::cout << std::endl;
			o++;
		}

		console::SetTextGreen();
		if(m > 0) std::cout << "\n" << ss.str() << std::endl;
		std::cout << "\n共计" << n << "次,获得五星" << m << "个" << std::endl;

		console::SetTextWhite();
	}
private:
	name_star roll_main()
	{
		while(res.pink <= 0) buy_pink(1);
		res.pink--;
		nCount++;

		static auto rand = [](const pool_t::mapped_type &which) ->name_star {
			std::vector<name_star> temp(which.begin(), which.end());
			return std::move(temp[std::random_device{}() % temp.size()]);
		};

		static auto roll_base = [this]() {
			static std::uniform_int_distribution<> dist(0, 999);
			std::mt19937 gen(std::random_device{}());
			int dg = dist(gen);

			if((dg -= (6 + (nT5 > 70 ? nT5 - 70 : 0) * 50)) < 0)
			{
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
		};
		auto i = roll_base();
		switch(i)
		{
			case 5:
				if(pool.count(POOL_UP_5) && (da || std::random_device{}() % 2))
				{
					da = false;
					return std::move(rand(pool[POOL_UP_5]));
				}
				else
				{
					da = true;
					return std::move(rand(pool[POOL_5]));
				}
				break;
			case 4:
				if(pool.count(POOL_UP_4) && std::random_device{}() % 2)
					return std::move(rand(pool[POOL_UP_4]));
				else
					return std::move(rand(pool[POOL_4]));
				break;
			case 3:
				return std::move(rand(pool[POOL_3]));
		}
		return { "",0 };
	}

protected:
	pool_t pool;

	struct __RES
	{
		int pink = 0;
		int stone = 0;
		int stone_x = 0;
		int money = 0;
	}res;

	unsigned int nCount = 0;	// 抽卡次数
	unsigned short nT5 = 0;		// 五星保底
	unsigned short nT4 = 0;		// 四星保底
	bool da = false;			// 大保底
};

// up池
class GachaX :virtual public gacha
{
public:
	std::string im() const
	{
		return "GachaX";
	}

	GachaX()
	{
		json_t json;
		{
			std::ifstream ifs("config.json");
			if(!ifs.is_open()) throw;
			ifs >> json;
		}

		for(auto &e : json["卡池"]["常驻"]["角色"]["五星"].as_array())
		{
			pool[5].insert({ e.as_string(),5 });
		}

		for(auto &e : json["卡池"]["常驻"]["角色"]["四星"].as_array())
		{
			pool[4].insert({ e.as_string(),4 });
		}

		for(auto &e : json["卡池"]["常驻"]["武器"]["四星"].as_array())
		{
			pool[4].insert({ e.as_string(),4 });
		}

		for(auto &e : json["卡池"]["常驻"]["武器"]["三星"].as_array())
		{
			pool[3].insert({ e.as_string(),3 });
		}

		for(auto &e : json["卡池"]["up"]["角色"]["五星"].as_array())
		{
			pool[2].insert({ e.as_string(),5 });
		}

		for(auto &e : json["卡池"]["up"]["角色"]["四星"].as_array())
		{
			pool[1].insert({ e.as_string(),4 });
		}

	}

public:
	ret_list get_char_list() const
	{
		ret_list list;
		for(auto e : { POOL_5,POOL_4,POOL_UP_5,POOL_UP_4 })
		{
			if(pool.count(e))
			{
				for(auto &ee : pool.at(e))
				{
					list.push_back(ee);
				}
			}
		}
		return std::move(list);
	}

	bool inPool(const name_star::first_type &name) const
	{
		for(auto &e : pool)
		{
			for(auto &ee : e.second)
			{
				if(name == ee.first)
					return true;
			}
		}
		return false;
	}

};