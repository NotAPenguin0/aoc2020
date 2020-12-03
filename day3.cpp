#include "common/point.hpp"

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

// good old cp tricks
#define int uint64_t

// Coordinate system:
// Top-left = (0, 0)

using Map = std::vector<std::string>;

int pattern_edge(Map const& map) {
	return map[0].size();
}

int map_height(Map const& map) {
	return map.size();
}

bool is_tree(Map const& map, Point pt) {
	return map[pt.y][pt.x] == '#';
}


int trees_on_slope(Map const& map, Point slope) {
	int tree_count = 0;
	Point cur{ 0, 0 };
	while (cur.y < map_height(map)) {
		if (is_tree(map, cur)) ++tree_count;
		cur = cur + slope;
		cur.x %= pattern_edge(map);
	}
	return tree_count;
}

int part1(Map const& map) {
	return trees_on_slope(map, { 3, 1 });
}

int part2(Map const& map) {
	int answer = 1;
	std::vector<Point> slopes{ {1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2} };
	for (auto slope : slopes) {
		answer *= trees_on_slope(map, slope);
	}
	return answer;
}


// mAiN mUsT rEtUrN iNt
signed main() {
	Map map;
	std::ifstream file("input/day3.txt");
	std::string line;
	while (std::getline(file, line)) {
		map.push_back(std::move(line));
	}

	std::cout << "Answer to part 1: " << part1(map) << "\n";
	std::cout << "Answer to part 2: " << part2(map) << "\n";
}
