#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void day_1()
{
	std::ifstream file_input("day_1.txt");
	std::string text;
	std::vector<int> elf_inventories { 0 };

	while (getline(file_input, text)) {
		if (text.empty())
		{
			elf_inventories.push_back(0);
		} else
		{
			elf_inventories[elf_inventories.size() - 1] += std::stoi(text);
		}
	}
	
	const int max_value = *std::max_element(elf_inventories.begin(), elf_inventories.end());
	const std::vector<int>::iterator iterator = std::find(elf_inventories.begin(), elf_inventories.end(), max_value);
	const auto max_index = std::distance(elf_inventories.begin(), iterator);

	std::sort(elf_inventories.begin(), elf_inventories.end(), std::greater<>());

	int top_three = 0;
	for (int index = 0; index < 3; index++)
	{
		top_three += elf_inventories[index];
	}
	
	printf("The Max Value Is: %d and has index: %llu\n", max_value, max_index);
	printf("Top three total calories: %d", top_three);
}
