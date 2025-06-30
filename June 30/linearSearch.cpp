#include <iostream>
#include <vector>

int linearSearch(std::vector<int> &arr, int v) {

    int index = -1;
    for (size_t i = 0; i < arr.size(); i++) {
        if (arr[i] == v) {
            index = i;
            return index;
        }
    }

    return index;
}


int main() {

    std::vector<int> arr(100);
    int x;

    for (size_t i = 0; i < arr.size(); i++) {
        arr[i] = i;
    }

    std::cout << "Enter a number:\n";
    std::cin >> x;

    // x = 49;

    int index = linearSearch(arr, x);

    if (index == -1) {
        std::cout << "NOT FOUND\n";
    } else {
        std::cout << "Element " << x << " found at position " << index << std::endl;
    }
    

    return 0;
}
