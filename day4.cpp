#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <regex>

using Pw = std::string;

int part1(std::vector<Pw> const& passwords) {
	int count = 0;

	std::vector<std::string> req_fields = { "ecl", "pid", "eyr", "hcl", "byr", "iyr", "hgt" };
	for (auto const& pw : passwords) {
		bool match = true;
		for (auto const& field : req_fields) {
			if (pw.find(field) == std::string::npos) {
				match = false;
				break;
			}
		}
		if (match) ++count;
	}

	return count;
}

int part2(std::vector<Pw> const& passwords) {
	const char* regex_string = R"((((iyr:\d\d\d\d)|(ecl:(amb|blu|brn|gry|grn|hzl|oth))|(cid:\d+)|(eyr:\d\d\d\d)|(pid:\d{9})|(hcl:#[\da-f]{6})|(byr:\d{4})|(hgt:(\d+)(?:cm|in)))\s?){7,8})";
	std::regex regex(regex_string);

	int count = 0;

	// 1. Check if regex matches
	// 2. Validate fields
	for (auto const& pw : passwords) {
		// Check if all required fields are present
		std::vector<std::string> req_fields = { "ecl", "pid", "eyr", "hcl", "byr", "iyr", "hgt" };
		bool has_fields = true;
		for (auto const& field : req_fields) {
			if (pw.find(field) == std::string::npos) {
				has_fields = false;
				break;
			}
		}
		if (!has_fields) continue;

		if (std::regex_match(pw, regex)) {
			int byr_index = pw.find("byr");
			if (byr_index == std::string::npos) continue;
			int byr = std::stoi(pw.substr(byr_index + 4, 4));
			if (byr < 1920 || byr > 2002) continue;

			int iyr_index = pw.find("iyr");
			if (iyr_index == std::string::npos) continue;
			int iyr = std::stoi(pw.substr(iyr_index + 4, 4));
			if (iyr < 2010 || iyr > 2020) continue;

			int eyr_index = pw.find("eyr");
			if (eyr_index == std::string::npos) continue;
			int eyr = std::stoi(pw.substr(eyr_index + 4, 4));
			if (eyr < 2020 || eyr > 2030) continue;

			int hgt_index = pw.find("hgt");
			if (hgt_index == std::string::npos) continue;
			int hgt_end = hgt_index + 4;
			int hgt_data_end = pw.find_first_of("mn", hgt_end) + 1;
			std::string height_str = pw.substr(hgt_end, hgt_data_end - hgt_end);
			std::string hgt_unit = height_str.substr(height_str.size() - 2, 2);
			int height = std::stoi(height_str.substr(0, height_str.size() - 2));
			if (hgt_unit == "cm") {
				if (height < 150 || height > 193) continue;
			}
			else if (hgt_unit == "in") {
				if (height < 59 || height > 76) continue;
			}
			else continue;

			++count;
		}
	}
	return count;
}

int main() {
	std::ifstream file("input/day4.txt");
	std::string line{};
	std::vector<Pw> passwords{};
	while (std::getline(file, line)) {
		Pw password;
		do {
			password += line;
		} while (std::getline(file, line) && line != "");
		passwords.push_back(std::move(password));
	}

	std::cout << "Answer to part 1: " << part1(passwords) << "\n";
	std::cout << "Answer to part 2: " << part2(passwords) << "\n";

	return 0;
}