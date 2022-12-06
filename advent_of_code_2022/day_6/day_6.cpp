#include "day_6.h"

#include <algorithm>
#include <fstream>
#include <set>
#include <string>

namespace day_6
{
	void init()
	{
		std::ifstream file_input("day_6/day_6.txt");

		if (file_input.is_open())
		{
			size_t number_of_chars_part1 { 0 };
			size_t number_of_chars_part2 { 0 };
			std::string text { };
			getline(file_input, text);
			int unique_character_size_part1 = 4;
			int unique_character_size_part2 = 14;

			for (size_t index = 0; index < text.size(); index++)
			{
				std::string chunk_part1 = text.substr(index, unique_character_size_part1);
				std::string chunk_part2 = text.substr(index, unique_character_size_part2);
				std::set<char> unique_characters_part1(chunk_part1.begin(), chunk_part1.end());
				std::set<char> unique_characters_part2(chunk_part2.begin(), chunk_part2.end());

				// all unique
				if (unique_characters_part1.size() == unique_character_size_part1 && number_of_chars_part1 == 0)
				{
					number_of_chars_part1 = index + unique_character_size_part1;
				}

				if (unique_characters_part2.size() == unique_character_size_part2 && number_of_chars_part2 == 0)
				{
					number_of_chars_part2 = index + unique_character_size_part2;
				}

			}

			printf("Part 1: %llu and Part 2: %llu", number_of_chars_part1, number_of_chars_part2);
		}
	}
}
