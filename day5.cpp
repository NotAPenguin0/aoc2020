#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

int binary_search(const char* str, int len, int min, int max) {
	int half = (max - min) / 2;
	if (len == 0) { return min + half; }
	if (str[0] == 'F' || str[0] == 'L') {
		return binary_search(str + 1, len - 1, min, max - half - 1);
	}
	return binary_search(str + 1, len - 1, min + half + 1, max);
}

int seat_id(std::string const& seat) {
	int row = binary_search(seat.c_str(), 7, 0, 127);
	int col = binary_search(seat.c_str() + 7, 3, 0, 7);
	return row * 8 + col;
}

int part1(std::vector<std::string> const& passes) {
	int max = 0;
	for (std::string const& pass : passes) {
		max = std::max(max, seat_id(pass));
	}
	return max;
}

int part2(std::vector<std::string> const& passes) {
	std::vector<int> sids;
	for (auto const& pass : passes) {
		sids.push_back(seat_id(pass));
	}

	// find first missing seat id
	std::sort(sids.begin(), sids.end());
	int last = sids[0];
	for (int i = 1; i < sids.size(); ++i) {
		if (sids[i] != last + 1) { return last + 1; } // The missing seat ID is last + 1
		last = sids[i];
	}
	return -1;
}

int main() {
	std::vector<std::string> passes;
	std::string p;
	std::ifstream file("input/day5.txt");
	while (file >> p) {
		passes.push_back(std::move(p));
	}

	std::cout << "Answer to part 1: " << part1(passes) << "\n";
	std::cout << "Answer to part 2: " << part2(passes) << "\n";
}