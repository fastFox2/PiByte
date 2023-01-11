#include "PiByte.h"
#include <iostream>

int main() {
	pibyte::Log::init_console_log(pibyte::LogLevel::info);

	pibyte::lexing::lexer lexer;

	std::cout << "Please enter your equation: ";

	std::string userInputString;
	std::getline(std::cin, userInputString);

	std::vector<pibyte::lexing::lexeme>& lexemes = lexer.lex_string(userInputString);

	std::cout << "Lexing result is: ";

	for (auto& elem : lexemes)
	{
		std::cout << elem.original_string;
	}


}
