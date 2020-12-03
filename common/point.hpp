#pragma once

struct Point {
	int x = 0, y = 0;
};

inline Point operator+(Point const& lhs, Point const& rhs) {
	return { lhs.x + rhs.x, lhs.y + rhs.y };
}