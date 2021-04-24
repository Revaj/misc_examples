#include <algorithm>
#include <iostream>
#include <map>

bool permutation(std::string s, std::string t)
{
    if (s.size() != t.size()) {
        return false;
    }

    std::sort(s.begin(), s.end());
    std::sort(t.begin(), t.end());

    return s.compare(t) == 0;
}

bool permutation_2(std::string s, std::string t)
{
    if (s.size() != t.size()) {
        return false;
    }

    std::map<char, int> count{};

    for (int i = 0; i < s.size(); i++)
    {
        count[s[i]]++;
    }

    for(int i = 0; i < t.size(); i++)
    {
        count[t[i]]--;
        if (count[t[i]] < 0) {
            return false;
	}
    }

    return true;
}


int main() {
    std::cout << "Test permutation\n";

    std::cout << "god dog == " << std::boolalpha << permutation("god", "dog");

    std::cout << "\n";

    std::cout << "Test permutation 2\n";

    std::cout << "god dog == " << std::boolalpha << permutation_2("god", "dog");


    std::cout << "\n";

    return 0;
}
