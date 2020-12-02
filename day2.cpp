#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

bool is_valid(std::string const& pw, int min, int max, char contains) {
	int count = std::count(pw.begin(), pw.end(), contains);
	return min <= count && count <= max;
}

bool is_valid_pt2(std::string const& pw, int pos1, int pos2, char contains) {
	char a = pw[pos1 - 1]; // indices start at 1 here
	char b = pw[pos2 - 1];

	return (a == contains || b == contains) && !(a == contains && b == contains);
}

int part1() {
	int count = 0;

	char dummy;
	std::ifstream input("input/day2.txt");

	int min = 0, max = 0;
	char contains = '\0';
	std::string pw{};
	while (input >> min >> dummy >> max >> contains >> dummy >> pw) {
		if (is_valid(pw, min, max, contains)) {
			++count;
		}
	}

	return count;
}

int part2() {
	int count = 0;

	char dummy;
	std::ifstream input("input/day2.txt");

	int min = 0, max = 0;
	char contains = '\0';
	std::string pw{};
	while (input >> min >> dummy >> max >> contains >> dummy >> pw) {
		if (is_valid_pt2(pw, min, max, contains)) {
			++count;
		}
	}

	return count;
}

int main() {
	std::cout << "Answer to part 1: " << part1() << "\n";
	std::cout << "Answer to part 2: " << part2() << "\n";
}