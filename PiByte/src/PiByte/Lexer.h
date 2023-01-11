#pragma once

#include "Core.h"
#include <vector>
#include <string>


namespace pibyte::lexing
{
	enum tokens
	{
		// Basic Operators
		PLUS, MINUS, TIMES, DIVIDED, // 0, 1, 2, 3

		// Brackets
		L_BRACKET, R_BRACKET, // 4, 5

		// Of course Numbers
		NUMBER,                      // 6

		// More Complex mathematical operations
		SQRT, SIN, COS, TAN,       // 7, 8, 9, 10

		// Special Tokens
		TOK_EOF                   // 11

	};

	PIBYTE_API struct lexeme
	{
		tokens token;
		std::string original_string;
	};

	class lexer
	{
	private:
		const int max_operator_lenght = 4;
		const std::string *m_expr;

		std::string::const_iterator m_expr_begin;
		std::string::const_iterator m_expr_end;
		std::string::const_iterator m_current_pos;

		bool is_invalid;

		char m_current_char;

		std::vector<lexeme> m_lexemes;
		void advance();
		void add_lexeme(tokens t_token,const std::string& t_original_string);   //Implemented
		void add_lexeme(tokens t_token);   //Implemented
		int handle_simple_operation();   //Implemented
		void handle_number(std::locale t_locale);   //Implemented
		int handle_complex_operation(std::locale t_locale);   //TODO
	public:
		PIBYTE_API std::vector<lexeme>& lex_string(std::string& t_expression);
	};
}
	