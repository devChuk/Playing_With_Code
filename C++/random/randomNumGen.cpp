#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    srand(time(NULL));
    for (int i = 0; i < 10; i++) {
    	int random_number = std::rand() % 8 + 1; // rand() return a number between ​0​ and RAND_MAX
    	std::cout << random_number << " ";
    }
    return 0;
}