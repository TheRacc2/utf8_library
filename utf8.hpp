#ifndef LIB_UTF8_HPP
#define LIB_UTF8_HPP

#include <iostream>
#include <Windows.h>

#define INPUT_LENGTH 1024

namespace utf8 {
	using string = std::string;

	class ostream {
		public:
			ostream operator <<(string in) const {
				const unsigned int output_cp = GetConsoleOutputCP();
				const unsigned int input_cp = GetConsoleCP();

				SetConsoleOutputCP(CP_UTF8); // Output, UTF-8
				SetConsoleCP(CP_UTF8); //Input, UTF-8

				std::cout << in;

				SetConsoleOutputCP(output_cp);
				SetConsoleCP(input_cp);

				return *this;
			}
	};

	class istream {
		public:
			void operator >>(string& in) const {
				const unsigned int output_cp = GetConsoleOutputCP();
				const unsigned int input_cp = GetConsoleCP();

				SetConsoleOutputCP(CP_UTF8); // Output, UTF-8
				SetConsoleCP(CP_UTF8); //Input, UTF-8

				wchar_t wstr[INPUT_LENGTH];
				char mb_str[INPUT_LENGTH * 3 + 1];

				unsigned long read;
				void* con = GetStdHandle(STD_INPUT_HANDLE);

				ReadConsoleW(con, wstr, INPUT_LENGTH, &read, NULL); // Read console input buffer into a wstring

				int size = WideCharToMultiByte(CP_UTF8, 0, wstr, read, mb_str, sizeof(mb_str), NULL, NULL); // Convert wstring to string
				mb_str[size] = 0; // Zero termination

				SetConsoleOutputCP(output_cp);
				SetConsoleCP(input_cp);

				in = mb_str;
			}
	};

	istream cin;
	ostream cout;
}



#endif