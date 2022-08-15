#include <iostream>

constexpr int size_array = 8;


void print_array(int array[], int len)
{
    std::cout << "[ ";
    for(int i = 0; i < len; i++)
        std::cout << array[i] << " ";
    std::cout << "]\n";
}

//k are numbers from 0-5
void counting_sort(int array[], int array_result[], int k)
{
    int tmp_array[k] = {0};
    for(int j = 0; j < size_array; j++)
        tmp_array[array[j]] = tmp_array[array[j]] + 1;

    //already counted the numbers of the array
    for(int i = 1; i < k; i++) {
        tmp_array[i] = tmp_array[i] + tmp_array[i - 1];
    }


    //here we have an order now, we can substract and going
    //on with the counters to show where should go the numbers location
    for(int j = 0; j < size_array; j++) {
        array_result[tmp_array[array[j]] - 1] = array[j];
	tmp_array[array[j]] -= 1;
    }
    //tmp_array is more like a pointer or references that maps the location
    //of the position of numbers by using the counters, this should help
    //to track where should go the next number
}

int main() {
    int array[size_array] = {2, 5, 3, 0, 2, 3, 0, 3};
    print_array(array, size_array);
    int array_result[size_array] = {};
    counting_sort(array, array_result, 6);
    print_array(array_result, size_array);
    return 0;
}
