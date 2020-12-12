#pragma once

#include <chrono>
#include <iostream>

namespace ch = std::chrono;

template<typename F>
void timed(F&& f, size_t count = 1) {
	auto start = ch::system_clock::now();
	for (size_t i = 0; i < count; ++i) {
		f();
	}
	auto end = ch::system_clock::now();
	auto us = ch::duration_cast<ch::microseconds>(end - start).count();
	std::cout << "Total time: " << us / 1000.0f << "ms.\n";
	std::wcout << L"Average time per run: " << us / (float)count << L" microseconds\n";
}