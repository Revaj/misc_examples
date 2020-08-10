#include <iostream>

bool is_unique_chars(const std::string &str) {
    if (str.size() > 128)
        return false;

    bool char_set[128] {};

    for (int i = 0; i < str.size(); i++) {
        int val = str.at(i);
        if (char_set[val]) {
            return false;
        }
        char_set[val] = true;
    }
    return true;
}


bool alternative_unique(const std::string &str) {
    int checker = 0;
    for (int i = 0; i < str.size(); i++) {
        int val = str.at(i) - 'a';
        if ((checker & (1 << val)) > 0) {
            return false;
        }
        checker |= (1 << val);
    }
    return true;
}


int main() {
    std::cout << "UNIQUE" << std::endl;
    std::cout << "thiscstringisunique: " << is_unique_chars("thiscstringisunique") << std::endl;
    std::cout << "unic: " << is_unique_chars("unic") << std::endl;

    std::cout << "ALTERNATIVE UNIQUE" << std::endl;
    std::cout << "thiscstringisunique: " << alternative_unique("thiscstringisunique") << std::endl;
    std::cout << "unic: " << alternative_unique("unic") << std::endl;
    return 0;
}
