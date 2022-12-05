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
		std::vector<std::deque<char>> crates;

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
				else {

				}

				index++;
			}
		}
	}
}
