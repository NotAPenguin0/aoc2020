#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstddef>
#include <cmath>
#include <unordered_map>
#include <chrono>
namespace ch = std::chrono;

#include "common/io.hpp"
#include "common/vec.hpp"
#include "common/timed.hpp"

int part1(std::vector<int> const& chain) {
	int diff1 = 0;
	// One 3-differential for the output outlet into your device
	int diff3 = 1;
	// Process the chain with the starting zero outlet included
	for (int i = 0; i < chain.size() - 1; ++i) {
		int diff = chain[i + 1] - chain[i];
		if (diff == 1) diff1 += 1;
		if (diff == 3) diff3 += 1;
	}
	return diff1 * diff3;
}

using u64 = uint64_t;

std::vector<u64> memo;

// v is the index
u64 combinations_for(int v, std::vector<int> const& adapters) {
	if (v == 0) return 1;

	if (memo[v] != 0) return memo[v];

	u64 combinations = 0;
	if (v > 0 && adapters[v - 1] >= adapters[v] - 3) {
		combinations += combinations_for(v - 1, adapters);
	}
	if (v > 1 && adapters[v - 2] >= adapters[v] - 3) {
		combinations += combinations_for(v - 2, adapters);
	}
	if (v > 2 && adapters[v - 3] >= adapters[v] - 3) {
		combinations += combinations_for(v - 3, adapters);
	}
	memo[v] = combinations;
	return combinations;
}

u64 part2(std::vector<int> const& adapters) {
	return combinations_for(adapters.size() - 1, adapters);
}

int main() {
	std::ifstream file("input/day10.txt");
	std::vector<int> adapters{};
	int jolt;
	while (file >> jolt) adapters.push_back(jolt);

	adapters.insert(adapters.begin(), 0);
	std::sort(adapters.begin(), adapters.end());
	memo.resize(adapters.size());
	// Part 1
	timed([&adapters]() {
		memset(memo.data(), 0, memo.size() * sizeof(u64));
		volatile int p1 = part1(adapters);
		volatile u64 p2 = part2(adapters);
	}, 1000);
	std::cout << "Part 1: " << part1(adapters) << "\n";
	std::cout << "Part 2: " << part2(adapters) << "\n";
}