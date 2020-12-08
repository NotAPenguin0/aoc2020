#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <chrono>

namespace ch = std::chrono;

#include "common/string.hpp"

struct RuleEntry {
	struct Bag {
		std::string color;
		int amount = 0;
	};
	std::vector<Bag> bags;
};

struct Rules {
	std::unordered_map<std::string, RuleEntry> forward;
	std::unordered_map<std::string, std::vector<std::string>> reverse;
};

void build_reverse(Rules& rules) {
	for (auto const& [k, v] : rules.forward) {
		for (auto const& bag : v.bags) {
			rules.reverse[bag.color].push_back(k);
		}
	}
}

void indirect_contains(std::unordered_set<std::string>& contains, std::string const& key, Rules const& rules) {
	if (auto it = rules.reverse.find(key); it == rules.reverse.end()) return;
	else {
		for (auto const& parent : it->second) {
			contains.insert(parent);
			indirect_contains(contains, parent, rules);
		}
	}
}

int part1(Rules const& rules) {
	std::unordered_set<std::string> contains{};
	indirect_contains(contains, "shiny gold", rules);
	return contains.size();
}

int bags_inside(std::string const& key, Rules const& rules) {
	int total = 1; // Default to one, since every bag "contains itself"
	if (auto it = rules.forward.find(key); it == rules.forward.end()) return total;
	else {
		for (auto const& child : it->second.bags) {
			total += child.amount * bags_inside(child.color, rules);
		}
	}
	return total;
}

int part2(Rules const& rules) {
	return bags_inside("shiny gold", rules) - 1;
}

int main() {
	Rules rules;
	std::ifstream file("input/day7.txt");
	std::string line;
	while (std::getline(file, line)) {
		// Parse line into rule
		size_t first_bag_index = line.find("bag");
		std::string base_color = line.substr(0, first_bag_index - 1);
		std::string content_rules = line.substr(line.find("contain", first_bag_index) + strlen("contain") + 1);
		// No contents
		if (content_rules == "no other bags.") {
			rules.forward[base_color] = {};
			continue;
		}

		auto content = split(content_rules, ',');
		RuleEntry entry{};
		for (auto const& val : content) {
			RuleEntry::Bag bag{};
			size_t last_digit_index = val.find_last_of("0123456789");
			bag.amount = std::stoi(val.substr(0, last_digit_index + 1));
			bag.color = val.substr(last_digit_index + 2, val.find("bag") - last_digit_index - 3);
			entry.bags.push_back(std::move(bag));
		}
		rules.forward[base_color] = std::move(entry);
	}
	build_reverse(rules);
	auto start = ch::system_clock::now();
	std::cout << "Answer to part 1: " << part1(rules) << "\n";
	auto end = ch::system_clock::now();
	float ms = ch::duration_cast<ch::microseconds>(end - start).count() / 1000.0f;
	std::cout << "Took: " << ms << "ms\n";
	std::cout << "Answer to part 2: " << part2(rules) << "\n";
}