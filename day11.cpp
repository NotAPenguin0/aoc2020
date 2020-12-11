#include "common/timed.hpp"
#include "common/point.hpp"

#include <fstream>
#include <string>
#include <vector>
#include <array>

using Seats = std::vector<std::string>;

int surrounding(Seats const& seats, int r, int c, char x) {
	int count = 0;
	static std::array<Point, 8> offsets{ {
		{1, 0}, {1, 1}, {1, -1}, {0, 1}, {0, -1}, {-1, 0}, {-1, 1}, {-1, -1}
	} };
	for (Point offset : offsets) {
		int newr = r + offset.y;
		int newc = c + offset.x;
		if (newr >= 0 && newr < seats.size() && newc >= 0 && newc < seats[0].size()) {
			if (seats[newr][newc] == x) ++count;
		}
	}
	return count;
}

int surrounding_free(Seats const& seats, int r, int c) {
	return surrounding(seats, r, c, 'L') + surrounding(seats, r, c, '.');
}

int surrounding_occupied(Seats const& seats, int r, int c) {
	return surrounding(seats, r, c, '#');
}

void print_step(Seats const& seats) {
	for (auto const& row : seats) {
		std::cout << row << std::endl;
	}
}

bool sim_step(Seats& seats) {
	std::vector<char*> to_swap;
	for (int r = 0; r < seats.size(); ++r) {
		for (int c = 0; c < seats[r].size(); ++c) {
			// 1. All surrounding seats empty
			if (seats[r][c] == 'L' && surrounding_occupied(seats, r, c) == 0) {
				to_swap.push_back(&seats[r][c]);
			}
			else if (seats[r][c] == '#' && surrounding_occupied(seats, r, c) >= 4) {
				to_swap.push_back(&seats[r][c]);
			}
		}
	}
	if (to_swap.empty()) return false;
	for (char* c : to_swap) {
		if (*c == 'L') *c = '#';
		else *c = 'L';
	}
	return true;
}

// returns true if there is an occupied seat in specified direction
bool occupied_in_direction(Seats const& seats, int r, int c, Point direction) {
	while (true) {
		r += direction.y;
		c += direction.x;
		if (r >= 0 && r < seats.size() && c >= 0 && c < seats[0].size()) {
			// valid coord
			if (seats[r][c] == '#') return true; // occupied seat found in direction
			if (seats[r][c] == 'L') return false; // free seat found in direction
		}
		else {
			// invalid coord, break (no seat found)
			break;
		}
	}
	return false;
}

int surrounding_occupied2(Seats const& seats, int r, int c) {
	int count = 0;
	static std::array<Point, 8> offsets{ {
		{1, 0}, {1, 1}, {1, -1}, {0, 1}, {0, -1}, {-1, 0}, {-1, 1}, {-1, -1}
	} };

	for (Point offset : offsets) {
		if (occupied_in_direction(seats, r, c, offset)) ++count;
	}
	return count;
}

bool sim_step2(Seats& seats) {
	std::vector<char*> to_swap;
	for (int r = 0; r < seats.size(); ++r) {
		for (int c = 0; c < seats[r].size(); ++c) {
			// 1. All surrounding seats empty
			if (seats[r][c] == 'L' && surrounding_occupied2(seats, r, c) == 0) {
				to_swap.push_back(&seats[r][c]);
			}
			else if (seats[r][c] == '#' && surrounding_occupied2(seats, r, c) >= 5) {
				to_swap.push_back(&seats[r][c]);
			}
		}
	}
	if (to_swap.empty()) return false;
	for (char* c : to_swap) {
		if (*c == 'L') *c = '#';
		else *c = 'L';
	}
	return true;
}

int part1(Seats seats) {
	while (sim_step(seats)) {
		// Simulate
	}
	// Count occupied seats.
	int count = 0;
	for (auto const& row : seats) {
		count += std::count(row.begin(), row.end(), '#');
	}
	return count;
}

int part2(Seats seats) {
	while (sim_step2(seats)) {
		// Simulate
	}
	// Count occupied seats.
	int count = 0;
	for (auto const& row : seats) {
		count += std::count(row.begin(), row.end(), '#');
	}
	return count;
}

int main() {
	std::ifstream file("input/day11.txt");
	Seats seats;
	std::string row;
	while (file >> row) {
		seats.push_back(std::move(row));
	}

	timed([&seats]() {
		volatile int p1 = part1(seats);
		volatile int p2 = part2(seats);
		std::cout << p1 << "\n";
		std::cout << p2 << "\n";
	}, 1);
}