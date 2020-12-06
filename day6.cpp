#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

struct Group {
	std::vector<std::string> answers;
};

int part1(std::vector<Group> const& groups) {
	int total = 0;
	for (auto const& group : groups) {
		std::unordered_set<char> answer_set;
		for (auto const& person : group.answers) {
			answer_set.insert(person.begin(), person.end()); // Insert this person's answers into the set
		}
		total += answer_set.size();
	}
	return total;
}

int part2(std::vector<Group> const& groups) {
	int total = 0;
	for (auto const& group : groups) {
		std::unordered_map<char, int> answer_counts;
		for (auto const& person : group.answers) {
			for (auto answer : person) {
				answer_counts[answer] += 1;
			}
		}
		total += std::count_if(answer_counts.begin(), answer_counts.end(), [&group](auto it) {
			return it.second == group.answers.size();
		});
	}
	
	return total;
}

int main() {
	std::vector<Group> groups;
	std::string line;
	std::ifstream file("input/day6.txt");
	while (std::getline(file, line)) {
		Group group;
		group.answers.push_back(std::move(line));
		while (std::getline(file, line) && line != "") {
			group.answers.push_back(std::move(line));
		}
		groups.push_back(std::move(group));
	}

	std::cout << "Answer to part 1: " << part1(groups) << std::endl;
	std::cout << "Answer to part 2: " << part2(groups) << std::endl;
}