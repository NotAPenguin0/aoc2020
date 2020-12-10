#include <fstream>
#include <vector>
#include <iostream>
#include <utility>
#include <chrono>
#include <cinttypes>
namespace ch = std::chrono;

using u64 = uint64_t;

bool sum_in_values(u64 const* begin, u64 const* end, u64 val) {
	for (u64 const* a = begin; a < end; ++a) {
		for (u64 const* b = a + 1; b < end; ++b) {
			if (val == *a + *b) return true;
		}
	}
	return false;
}

std::pair<size_t, u64> part1(std::vector<u64> const& nums) {
	constexpr int preamble_len = 25;
	for (int i = preamble_len; i < nums.size(); ++i) {
		// Check if nums[i] is the sum of any of the 25 previous numbers
		if (!sum_in_values(&nums[i - preamble_len], &nums[i], nums[i])) {
			return { i, nums[i] };
		}
	}
	return { -1, -1 };
}

u64 part2(std::vector<u64> const& nums, u64 target_idx) {
	u64 target = nums[target_idx];
	u64 const* window_begin = &nums[0];
	u64 const* window_end = &nums[1];
	u64 window_sum = *window_begin + *window_end;

	while (window_sum != target) {
		// 1. Window is too small (1 element is not enough). Move end pointer
		u64 distance = window_end - window_begin;
		if (distance < 1) {
			++window_end;
			++distance;
		}
		
		// recalculate sum
		window_sum = 0;
		for (int i = 0; i < distance; ++i) {
			window_sum += window_begin[i];
		}

		// If sum is too large, move window begin pointer
		if (window_sum > target) {
			window_begin++;
		}
		// If sum is too small, move end window pointer
		else if (window_sum < target) {
			window_end++;
		}
	}

	// Reached exact target, return the sum of *window_begin and *(window_end - 1)
	return *window_begin + *(window_end - 1);
}

int main() {
	auto start = ch::system_clock::now();
	for (int i = 0; i < 100; ++i) {
		std::ifstream file("input/day9.txt");
		std::vector<u64> nums{};
		nums.reserve(1000); // We know there are 1000 lines in the input file
		u64 val = 0;
		while (file >> val) { nums.push_back(val); }

		auto [index, p1] = part1(nums);
		u64 p2 = part2(nums, index);
		printf("%" PRIu64 " %" PRIu64"\n", p1, p2);
	}
	auto end = ch::system_clock::now();
	float ms = ch::duration_cast<ch::microseconds>(end - start).count() / 1000.0f;
	std::cout << "Time: " << ms << "ms\n";
	std::cout << "Average per run: " << ms / 100.0f << "\n";
}