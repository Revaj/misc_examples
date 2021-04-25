#include <iostream>


bool replaced_one(const std::string &s, const std::string &t)
{
    if (abs(s.size() - t.size()) > 1) {
	return false;
    }

    auto it_s = s.begin();
    auto it_t = t.begin();
    
    int i = 0;
    while (it_s + 1 != s.end() || it_t + 1!= t.end()) {
	if (*it_s != *it_t) {
	    i++;

	    if (it_s + 1 != s.end() &&  s.size() != t.size()) {
		it_s++;
	        continue;
	    }
	}

	if (it_s + 1 != s.end()) {
	    it_s++;
	}

	if (it_t + 1 != t.end()) {
	    it_t++;
	}
    }

    return i <= 1;
}


int main() {
    std::cout << "One away\n";

    std::cout << "pale, ple -> " << std::boolalpha << replaced_one("pale", "ple") << "\n";
    std::cout << "pales, pale -> " << std::boolalpha << replaced_one("pales", "pale") << "\n";
    std::cout << "pale, bale -> " << std::boolalpha << replaced_one("pale", "bale") << "\n";
    std::cout << "pale, bae -> " << std::boolalpha << replaced_one("pale", "bae") << "\n";

    return 0;
}
