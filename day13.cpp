#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>

#include "common/timed.hpp"

using u64 = uint64_t;
using i64 = int64_t;

struct BusLine {
	u64 id = 0;
	// Offset from t
	u64 index = 0;
};


int part1(int arrival, std::vector<BusLine> const& buslines) {
	int lowest_wait_line = 0;
	int lowest_wait_time = std::numeric_limits<int>::max();

	for (auto line : buslines) {
		int time = ((arrival + line.id - 1) / line.id) * line.id - arrival;
		if (time < lowest_wait_time) {
			lowest_wait_line = line.id;
			lowest_wait_time = time;
		}
	}

	return lowest_wait_line * lowest_wait_time;
}

bool busline_comp(BusLine const& a, BusLine const& b) {
	return a.id > b.id;
}

i64 mul_inv(i64 a, i64 b)
{
	i64 b0 = b, t, q;
	i64 x0 = 0, x1 = 1;
	if (b == 1) return 1;
	while (a > 1) {
		q = a / b;
		t = b, b = a % b, a = t;
		t = x0, x0 = x1 - q * x0, x1 = t;
	}
	if (x1 < 0) x1 += b0;
	return x1;
}

i64 chinese_remainder(i64* n, i64* a, u64 len)
{
	i64 p, i, prod = 1, sum = 0;

	for (i = 0; i < len; i++) prod *= n[i];

	for (i = 0; i < len; i++) {
		p = prod / n[i];
		sum += a[i] * mul_inv(p, n[i]) * p;
	}

	return sum % prod;
}

i64 part2(std::vector<BusLine> buslines) {
	// https://en.wikipedia.org/wiki/Chinese_remainder_theorem
	std::vector<i64> n, a;

	// We implement search by sieving. This method is faster when the moduli (n) are sorted in descending order, so we sort the buslines
//	std::sort(buslines.begin(), buslines.end(), busline_comp);

	for (auto line : buslines) {
		n.push_back(line.id);
		a.push_back((line.id - line.index));
	}
	
	return chinese_remainder(n.data(), a.data(), n.size());
}

int main() {
	std::ifstream file("input/day13.txt");
	int arrival = 0;
	std::vector<BusLine> buslines;
	
	file >> arrival;
	std::string entry;
	int index = 0;
	while (std::getline(file, entry, ',')) {
		if (entry != "x") {
			buslines.push_back({ (u64)std::stoi(entry), (u64)index });
		}
		++index;
	}

	timed([arrival, &buslines]() {
		volatile int p1 = part1(arrival, buslines);
		volatile i64 p2 = part2(buslines);
		std::cout << p1 << "\n";
		std::cout << p2 << "\n";
	});
}