#include "Lexer.h"

#include <string>

#include "Log.h"

namespace pibyte::lexing{

	std::vector<lexeme>& lexer::lex_string(std::string& t_expression)
	{
		lexer::m_expr = &t_expression;

		//lexer::stripUnicode(*lexer::m_expr);


		PB_LOGINFO("Starting to lex the input string: {}", *lexer::m_expr);
		m_lexemes.clear();


		lexer::m_expr_begin = lexer::m_expr->begin();
		lexer::m_expr_end = lexer::m_expr->end();

		lexer::m_current_pos = lexer::m_expr_begin;
		lexer::m_current_char = *lexer::m_current_pos;

		std::locale loc{""};
		lexer::is_invalid = false;

		while (lexer::m_current_pos != m_expr_end)
		{
			if (is_invalid)
			{
				PB_LOGERROR("The equation is invalid, please check it again! Maybe you used uppercase?");
				break;
			}

			if (lexer::m_current_pos == m_expr_end)
			{
				PB_LOGINFO("End of File");
				lexer::add_lexeme(TOK_EOF);
				break;
			}

			if (std::isdigit(lexer::m_current_char, loc))
			{
				PB_LOGINFO("We found a Number!");
				lexer::handle_number(loc);
				continue;
			}

			// Check if it's a simple operation and handle it
			if (lexer::handle_simple_operation())
				continue;

			// Now do the same thing for more complex operations
			if (lexer::handle_complex_operation(loc))
				continue;

			advance();

			//if (lexer::m_current_pos == m_expr_end)
			//{
			//	PB_LOGINFO("End of File");
			//	lexer::add_lexeme(TOK_EOF);
			//	break;
			//}

		}

		lexer::add_lexeme(TOK_EOF);

		return m_lexemes;
	}

	void lexer::advance()
	{
		++lexer::m_current_pos;

		// Only assign the current char if there is one!
		if (lexer::m_current_pos == lexer::m_expr_end)
			return;

		lexer::m_current_char = *lexer::m_current_pos;

		if (isspace(lexer::m_current_char)) advance();

	}

	int lexer::handle_simple_operation()
	{
		switch (lexer::m_current_char)
		{
		case '+':
			add_lexeme(PLUS, std::string{ lexer::m_current_char });
			break;
		case '-':
			add_lexeme(MINUS, std::string{ lexer::m_current_char });
			break;
		case '*':
			add_lexeme(TIMES, std::string{ lexer::m_current_char });
			break;
		case '/':
			add_lexeme(DIVIDED, std::string{ lexer::m_current_char });
			break;
		case '(':
			add_lexeme(L_BRACKET, std::string{ lexer::m_current_char });
			break;
		case ')':
			add_lexeme(R_BRACKET, std::string{ lexer::m_current_char });
			break;
		default:
			// Everything else will be handled by the main lex function
			return 0;
		}

		advance();
		return 1;
	}

	int lexer::handle_complex_operation(std::locale t_locale)
	{
		std::string operation_substring;

		while (isalpha(lexer::m_current_char, t_locale) && lexer::m_current_pos != lexer::m_expr_end)
		{
			operation_substring += m_current_char;
			
			advance();
			
			// Check if we have an operator
			if (operation_substring == std::string("sqrt"))
			{
				add_lexeme(SQRT, operation_substring);
				return 1;
			}
			else if (operation_substring == std::string("sin"))
			{
				add_lexeme(SIN, operation_substring);
				return 1;
			}
			else if (operation_substring == std::string("cos"))
			{
				add_lexeme(COS, operation_substring);
				return 1;
			}
			else if (operation_substring == std::string("tan"))
			{
				add_lexeme(TAN, operation_substring);
				return 1;
			}
			
			if (operation_substring.length() > lexer::max_operator_lenght)
			{
				lexer::is_invalid = true;
				break;
			}

			

		}
		return 0;
	}
	
	void lexer::handle_number(std::locale t_locale)
	{
		std::string number_substring;
		bool has_dot = false;

		while ((isdigit(lexer::m_current_char, t_locale) || lexer::m_current_char == '.') && lexer::m_current_pos != lexer::m_expr_end)
		{
			if (lexer::m_current_char == '.' && has_dot)
			{
				lexer::is_invalid = true;
				return;
			}
			has_dot = lexer::m_current_char == '.';
			number_substring += lexer::m_current_char;
			advance();
		}

		add_lexeme(NUMBER, number_substring);
	}

	void lexer::add_lexeme(tokens t_token, const std::string& t_original_string)
	{
		lexeme current_lexeme;
		current_lexeme.token = t_token;
		current_lexeme.original_string = t_original_string;

		lexer::m_lexemes.push_back(current_lexeme);

		PB_LOGINFO("Added Token of type: {}, please note that this is the 0 indexed number "
			"in the enum of all tokens and with the string {}", t_token, t_original_string);
	}

	void lexer::add_lexeme(tokens t_token)
	{
		lexeme current_lexeme;
		current_lexeme.token = t_token;
		lexer::m_lexemes.push_back(current_lexeme);

		PB_LOGINFO("Added Token of type: {}, please note that "
			"this is the 0 indexed number in the enum of all tokens", t_token);
	}
}

