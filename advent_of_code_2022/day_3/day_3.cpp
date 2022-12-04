#include "day_3.h"

#include <fstream>
#include <string>
#include "unordered_set"
#include <numeric>
#include <array>

namespace day_3
{
	constexpr auto EMPTY_CHAR = '0';
	const std::string alphabet = "0abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

	struct elf_team
	{
		std::array<std::string, 3> rucksack_items;
	};

	// Find characcter in string
	char find_character(std::string text, char character)
	{
		const auto string_iterator = std::find(text.begin(), text.end(), character);
		if (string_iterator != text.end())
		{
			return *string_iterator;
		}

		return EMPTY_CHAR;
	}

	// Get list of duplicate characters
	std::unordered_set<char> get_duplicates(const std::string& a, const std::string& b)
	{
		std::unordered_set<char> unique_characters{};

		// Change to ranges::views filters(?)
		for (const auto character : b)
		{
			char found_character = find_character(a, character);

			if (found_character != EMPTY_CHAR)
			{
				unique_characters.insert(found_character);
			}
		}

		return unique_characters;
	}

	// Find duplicate character in elf team
	char get_team_duplicate(elf_team team)
	{
		const auto duplicates = get_duplicates(team.rucksack_items[0], team.rucksack_items[1]);

		for (const auto duplicate : duplicates)
		{
			const char found_character = find_character(team.rucksack_items[2], duplicate);

			if (found_character != EMPTY_CHAR)
			{
				return found_character;
			}
		}

		return EMPTY_CHAR;
	}

	auto calculate_total_character_value = [](auto row_total, char character)
	{
		const auto alphabet_iterator = std::find(alphabet.begin(), alphabet.end(), character);
		return row_total + (alphabet_iterator - alphabet.begin());
	};

	auto calculate_total_team_value = [](auto team_total_value, elf_team team)
	{
		const char team_duplicate = get_team_duplicate(team);
		return calculate_total_character_value(team_total_value, team_duplicate);
	};


	void init()
	{
		std::ifstream file_input("day_3/day_3.txt");

		int row_index{ 0 }, elf_index{ 0 };
		size_t total_value{ 0 };
		std::string text{}, first_half{}, second_half{};
		std::unordered_set<char> duplicate_characters {};
		std::vector<elf_team> elf_teams{};

		if (file_input.is_open())
		{
			while (getline(file_input, text)) {
				elf_index = row_index % 3;

				// If it's the first elf in the team, create new team
				if (elf_index == 0)
				{
					elf_teams.push_back(elf_team{});
				}

				// get the latest team and add current text to the current elf of the team
				auto& current_team = elf_teams[elf_teams.size() - 1];
				current_team.rucksack_items[elf_index] = text;

				first_half = text.substr(0, text.length() / 2);
				second_half = text.substr(text.length() / 2);

				// Get all the duplicate characters and calculate the total value of the duplicate letters
				duplicate_characters = get_duplicates(first_half, second_half);
				total_value += std::accumulate(duplicate_characters.begin(), duplicate_characters.end(), 0, calculate_total_character_value);

				row_index++;
			}

			file_input.close();
		}

		// Calculating the total value of the teams
		const size_t team_total_value = std::accumulate(elf_teams.begin(), elf_teams.end(), 0, calculate_total_team_value);

		printf("Total value: %llu\n", total_value);
		printf("Team total value: %llu\n", team_total_value);
	}
}
