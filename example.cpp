#include <Windows.h>
#include <iostream>

#include "lib/utf8.hpp"

int main(int argc, char** argv) {
	utf8::cout << "Input: ";

	utf8::string test;
	utf8::cin >> test;

	utf8::cout << "Output: " << test;
}