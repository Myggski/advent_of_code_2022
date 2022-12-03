#include <fstream>
#include <iostream>
#include <map>
#include "day_2.h"

namespace day_2
{
	enum class Weapon {
		none = 0,
		rock = 1,
		paper = 2,
		scissor = 3
	};

	enum class WinCondition
	{
		none,
		loose = 'X',
		draw = 'Y',
		win = 'Z'
	};

	std::map<Weapon, Weapon> winning_conditions{
		{ Weapon::rock, Weapon::paper },
		{ Weapon::paper, Weapon::scissor },
		{ Weapon::scissor, Weapon::rock },
	};

	std::map<Weapon, Weapon> losing_conditions{
		{ Weapon::rock, Weapon::scissor },
		{ Weapon::paper, Weapon::rock },
		{ Weapon::scissor, Weapon::paper },
	};

	int get_game_score(Weapon enemy_weapon, Weapon player_weapon)
	{
		// won
		if (player_weapon == winning_conditions[enemy_weapon]) { return 6; }

		// draw
		if (player_weapon == enemy_weapon) { return 3; }

		// lost
		return 0;
	}

	Weapon get_weapon_type(char character)
	{
		switch (character)
		{
		case 'A':
		case 'X':
			return Weapon::rock;
		case 'B':
		case 'Y':
			return Weapon::paper;
		case 'C':
		case 'Z':
			return Weapon::scissor;
		default:
			return Weapon::none;
		}
	}

	Weapon get_weapon_by_condition(Weapon enemy_weapon, WinCondition win_condition)
	{
		if (win_condition == WinCondition::draw)
		{
			return enemy_weapon;
		}

		if (win_condition == WinCondition::win)
		{
			return winning_conditions[enemy_weapon];
		}

		return losing_conditions[enemy_weapon];
	}

	void init() {
		std::ifstream file_input("day_2/day_2.txt");
		int total_score{ 0 };

		if (file_input.is_open())
		{
			int challange = 2;
			char enemy_input{}, player_input{};
			WinCondition win_condition{ WinCondition::none };
			Weapon enemy_weapon{ Weapon::none }, player_weapon { Weapon::none };

			while (file_input >> enemy_input >> player_input) {
				enemy_weapon = get_weapon_type(enemy_input);

				// Get weapon depending on challenge
				player_weapon = challange == 1
				? get_weapon_type(player_input)
				: get_weapon_by_condition(enemy_weapon, static_cast<WinCondition>(player_input));

				total_score += static_cast<int>(player_weapon) + get_game_score(enemy_weapon, player_weapon);
			}

			file_input.close();
		}

		printf("%d", total_score);
	}
}
