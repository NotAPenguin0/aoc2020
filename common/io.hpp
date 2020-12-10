#pragma once

#include <iostream>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& out, std::vector<T> const& vec) {
	out << "{ ";
	for (size_t i = 0; i < vec.size(); ++i) {
		out << vec[i];
		if (i != vec.size() - 1) out << ", ";
	}
	out << " }";
	return out;
}