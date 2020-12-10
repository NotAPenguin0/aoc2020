#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstddef>
#include <cmath>
#include <unordered_map>

#include "common/io.hpp"
#include "common/vec.hpp"


std::vector<int> make_chain(std::vector<int> const& adapters) {
	std::vector<int> v = adapters;
	std::sort(v.begin(), v.end());
	return v;
}

int part1(std::vector<int> const& chain) {
	int diff1 = 0;
	// One 3-differential for the output outlet into your device
	int diff3 = 1;
	// Process the chain with the starting zero outlet included
	std::vector<int> chain_with_zero = 0 + chain;
	for (int i = 0; i < chain_with_zero.size() - 1; ++i) {
		int diff = chain_with_zero[i + 1] - chain_with_zero[i];
		if (diff == 1) diff1 += 1;
		if (diff == 3) diff3 += 1;
	}
	return diff1 * diff3;
}

using u64 = uint64_t;

std::unordered_map<u64, u64> memo;

u64 combinations_for(int v, std::vector<int> const& adapters) {
	if (v == 0) return 1;

	auto it = std::find(adapters.begin(), adapters.end(), v);
	if (it == adapters.end()) return 0;

	if (auto i = memo.find(v); i != memo.end()) {
		return i->second;
	}

	auto combinations = combinations_for(v - 1, adapters) + combinations_for(v - 2, adapters) + combinations_for(v - 3, adapters);
	memo[v] = combinations;
	return combinations;
}

u64 part2(std::vector<int> const& adapters) {
	return combinations_for(adapters.back(), adapters);
}

int main() {
	std::ifstream file("input/day10.txt");
	std::vector<int> adapters{};
	int jolt;
	while (file >> jolt) adapters.push_back(jolt);

	// Part 1
	auto chain = make_chain(adapters);
	if (chain.empty()) std::cout << "No chain found\n";
	else {
		std::cout << chain << "\n";
	}
	std::cout << "Part 1: " << part1(chain) << "\n";
	std::sort(adapters.begin(), adapters.end());
	std::cout << "Part 2: " << part2(adapters) << "\n";
}