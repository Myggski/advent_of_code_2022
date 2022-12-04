#include "day_4.h";

#include <cassert>
#include <fstream>
#include <string>

namespace day_4
{
	struct RangeData
	{
		RangeData(int min_value, int max_value)
		: min_value(min_value), max_value(max_value) { }

		int min_value;
		int max_value;
	};

	RangeData convert_to_range_data(const std::string& elf_string)
	{
		const size_t range_separator = elf_string.find('-');

		const int min_value = std::stoi(elf_string.substr(0, range_separator));
		const int max_value = std::stoi(elf_string.substr(range_separator + 1));

		assert(min_value <= max_value, "Min value should be smaller than max value.");

		return RangeData{ min_value, max_value };
	}

	bool is_overlapped(RangeData a, RangeData b)
	{
		return std::max(a.min_value, b.min_value) <= std::min(a.max_value, b.max_value);
	}

	bool is_fully_overlapped(RangeData a, RangeData b)
	{
		return a.min_value >= b.min_value && a.max_value <= b.max_value
				|| b.min_value >= a.min_value && b.max_value <= a.max_value;
	}

	void init()
	{
		std::ifstream file_input("day_4/day_4.txt");
		std::string text{};
		int number_of_fully_overlaps{ 0 }, number_of_overlaps{ 0 };

		if (file_input.is_open())
		{
			while (getline(file_input, text)) {
				const size_t comma_index = text.find(',');

				std::string first_elf_string = text.substr(0, comma_index);
				std::string second_elf_string = text.substr(comma_index + 1);

				RangeData first_elf_data = convert_to_range_data(first_elf_string);
				RangeData second_elf_data = convert_to_range_data(second_elf_string);

				if (is_fully_overlapped(first_elf_data, second_elf_data))
				{
					number_of_fully_overlaps++;
				}

				if (is_overlapped(first_elf_data, second_elf_data))
				{
					number_of_overlaps++;
				}
			}

			printf("%d\n", number_of_fully_overlaps);
			printf("%d\n", number_of_overlaps);
		}
	}
}
