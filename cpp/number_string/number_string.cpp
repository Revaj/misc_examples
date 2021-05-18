#include<iostream>


std::string digit_to_char(int number){
    std::string result = "";
    result += char(number + 48);
    return result;
}

std::string itoa(int number){
    int first = number / 10;
    int second = number % 10;

    if (first == 0)
	return digit_to_char(second);
    std::string result = "";

    first = number;

    while(first / 10 > 0){
	second = first % 10;
	first = first / 10;

	result = digit_to_char(second) + result;
    }
    second = first % 10;
    result = digit_to_char(second) + result;
    return result;

    //std::string result = digits_to_char(second);
    //while(first / 10 > 0)
}


int main(){
    std::cout << itoa(123) << std::endl;
    return 0;
}
