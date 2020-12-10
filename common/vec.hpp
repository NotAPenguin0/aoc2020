#pragma once

#include <vector>
#include <algorithm>

template<typename T>
std::vector<T> operator+(std::vector<T> v, T const& value) {
	v.push_back(value);
	return v;
}

template<typename T>
std::vector<T> operator+(T const& value, std::vector<T> v) {
	v.insert(v.begin(), value);
	return v;
}

template<typename T>
std::vector<T> operator-(std::vector<T> v, T const& value) {
	v.erase(std::remove(v.begin(), v.end(), value));
	return v;
}