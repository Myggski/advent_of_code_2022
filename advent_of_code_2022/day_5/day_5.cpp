#include "day_5.h"

#include <deque>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace day_5
{
	struct InstructionData
	{
		InstructionData(int crates_to_move, int from_stack, int to_stack)
			: crates_to_move(crates_to_move), from_stack(from_stack), to_stack(to_stack) {}

		int crates_to_move;
		int from_stack;
		int to_stack;
	};

	auto add_only_numbers = [](std::vector<int>& numbers, const std::string& word)
	{
		numbers.push_back(std::stoi(word));
	};

	std::vector<std::string> get_words_from_string(std::string text)
	{
		std::vector<std::string> words;
		std::stringstream ss(text);
		std::string word{};

		while (ss >> word)
		{
			words.push_back(word);
		}

		return words;
	}

	void init()
	{
		std::ifstream file_input("day_5/day_5.txt");
		std::vector<std::string> crates{ "", "", "", "", "", "", "", "", "" };

		if (file_input.is_open())
		{
			std::vector<InstructionData> instructions;
			std::string text{};
			int index{ 0 };
			while (getline(file_input, text))
			{
				if (index > 9) {
					auto words = get_words_from_string(text);
					instructions.push_back({
						std::stoi(words[1]),
						std::stoi(words[3]),
						std::stoi(words[5])
						});
				}
				else if (index < 8) {
					for (int char_index = 1; char_index < text.size(); char_index += 4)
					{
						if (text[char_index] == ' ')
							continue;

						crates[char_index / 4].push_back(text[char_index]);
					}
				}

				index++;
			}

			std::vector<std::string> crates_for_crate_mover_9001 = crates;

			for (const auto& instruction : instructions)
			{
				auto& to_crate = crates[instruction.to_stack - 1];
				auto& from_crate = crates[instruction.from_stack - 1];
				auto& to_crate_mover_9001 = crates_for_crate_mover_9001[instruction.to_stack - 1];
				auto& from_crate_mover_9001 = crates_for_crate_mover_9001[instruction.from_stack - 1];

				for (int move = 0; move < instruction.crates_to_move; move++)
				{
					to_crate.insert(to_crate.begin(), from_crate[0]);
					from_crate.erase(0, 1);
				}


				std::string part_to_move = from_crate_mover_9001.substr(0, instruction.crates_to_move);
				from_crate_mover_9001.erase(0, instruction.crates_to_move);
				to_crate_mover_9001.insert(0, part_to_move);

			}

			for (auto crate : crates)
			{
				printf("%c", crate[0]);
			}

			printf("\n");

			for (auto crate : crates_for_crate_mover_9001)
			{
				printf("%c", crate[0]);
			}
		}
	}
}
