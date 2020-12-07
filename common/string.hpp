#include <string>
#include <vector>
#include <sstream>

inline std::vector<std::string> split(std::string const& s, char delim) {
	std::stringstream ss;
	ss << s;
	std::vector<std::string> result;
	std::string l;
	while (std::getline(ss, l, delim)) {
		result.push_back(std::move(l));
	}
	return result;
}