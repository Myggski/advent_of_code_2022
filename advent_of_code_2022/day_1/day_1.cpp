#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

void day_1()
{
	std::ifstream file_input("day_1/day_1.txt");
	std::string text;
	std::vector<int> elf_inventories { 0 };

	if (file_input.is_open())
	{
		{
			while (getline(file_input, text)) {
				if (!text.empty())
				{
					elf_inventories[elf_inventories.size() - 1] += std::stoi(text);
				}
				else
				{
					elf_inventories.push_back(0);
				}
			}

			file_input.close();
		}

		const auto max_value_iterator = std::max_element(elf_inventories.begin(), elf_inventories.end());
		const auto max_index = std::distance(elf_inventories.begin(), max_value_iterator);
		printf("The Max Value Is: %d and has index: %llu\n", *max_value_iterator, max_index);

		// Ascending sort to get the last 3 highest values
		std::sort(elf_inventories.begin(), elf_inventories.end());
		const int top_three = std::accumulate(elf_inventories.end() - 3, elf_inventories.end(), 0);
		printf("Top three total calories: %d", top_three);
	}
}
