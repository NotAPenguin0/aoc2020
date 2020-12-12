#include <vector>
#include <fstream>
#include <iostream>
#include <cmath>

#include "common/timed.hpp"

struct Instruction {
	char type = ' ';
	int arg = 0;
};

void move_in_direction(int& e, int& n, char dir, int amt) {
	if (dir == 'N') {
		n += amt;
	}
	else if (dir == 'E') {
		e += amt;
	}
	else if (dir == 'S') {
		n -= amt;
	}
	else if (dir == 'W') {
		e -= amt;
	}
}

char next(char dir) {
	if (dir == 'N') return 'E';
	if (dir == 'E') return 'S';
	if (dir == 'S') return 'W';
	if (dir == 'W') return 'N';
}

// Rotates dir by degrees to the right
void rotate(char& dir, int degrees) {
	degrees %= 360;
	while (degrees != 0) {
		dir = next(dir);
		degrees -= 90;
	}
}

void nav_step(int& e, int& n, char& direction, Instruction instr) {
	switch (instr.type) {
	case 'F': {
		move_in_direction(e, n, direction, instr.arg);
	} break;
	case 'N':
	case 'E':
	case 'W':
	case 'S':
		move_in_direction(e, n, instr.type, instr.arg);
		break;
	case 'L': {
		rotate(direction, 360 - instr.arg);
	} break;
	case 'R': {
		rotate(direction, instr.arg);
	} break;
	}
}

int part1(std::vector<Instruction> const& nav) {

	int e = 0, n = 0;
	char direction = 'E';

	for (auto const& instr : nav) {
		nav_step(e, n, direction, instr);
	}

	// We represent south and west positions as negative values for north and east respectively.
	
	return abs(e) + abs(n);
}

void move_to_waypoint_n(int& e, int& n, int& wpe, int& wpn, int amount) {
	int de = wpe - e;
	int dn = wpn - n;

	e += amount * de;
	n += amount * dn;

	wpe = e + de;
	wpn = n + dn;
}

void move_waypoint(int& wpe, int& wpn, char dir, int amt) {
	if (dir == 'N') {
		wpn += amt;
	}
	else if (dir == 'E') {
		wpe += amt;
	}
	else if (dir == 'S') {
		wpn -= amt;
	}
	else if (dir == 'W') {
		wpe -= amt;
	}
}

// Coordinates (e, n) relative to the ship's position
std::pair<int, int> rotate_waypoint_90(int e, int n) {
	return { n, -e }; // maffs
}

void rotate_waypoint(int e, int n, int& wpe, int& wpn, int degrees) {
	int rele = wpe - e;
	int reln = wpn - n;

	degrees = degrees % 360;
	while (degrees != 0) {
		auto [newe, newn] = rotate_waypoint_90(rele, reln);
		rele = newe;
		reln = newn;
		degrees -= 90;
	}

	wpe = e + rele;
	wpn = n + reln;
}

void nav_step2(int& e, int& n, int& wpe, int& wpn, Instruction const& instr) {
	switch (instr.type) {
	case 'F': {
		move_to_waypoint_n(e, n, wpe, wpn, instr.arg);
	} break;
	case 'N':
	case 'E':
	case 'W':
	case 'S':
		move_waypoint(wpe, wpn, instr.type, instr.arg);
		break;
	case 'L': {
		rotate_waypoint(e, n, wpe, wpn, 360 - instr.arg);
	} break;
	case 'R': {
		rotate_waypoint(e, n, wpe, wpn, instr.arg);
	} break;
	}
}

int part2(std::vector<Instruction> const& nav) {
	int e = 0, n = 0;

	int wpe = 10, wpn = 1;
	for (auto const& instr : nav) {
		nav_step2(e, n, wpe, wpn, instr);
	}

	return abs(e) + abs(n);
}

int main() {
	std::vector<Instruction> nav;
	std::ifstream file("input/day12.txt");
	Instruction i;
	while (file >> i.type >> i.arg) {
		nav.push_back(i);
	}
	
	timed([&nav]() {
		volatile int p1 = part1(nav);
		volatile int p2 = part2(nav);
		std::cout << p1 << '\n';
		std::cout << p2 << '\n';
	}, 1);
}