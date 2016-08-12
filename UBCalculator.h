// ============================================================================ 
// Calculator.h
// ~~~~~~~
// author    : Tamal T. Biswas
// - a simple calculator class
// - The class can evaluate any infix expression. 
// ============================================================================ 

#ifndef _UBCALCULATOR_H_
#define _UBCALCULATOR_H_

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include "Lexer.h"
#include "error_handling.h"
using namespace std;


/**
 * -----------------------------------------------------------------------------
 * the Calculator class:
 * - take a string to be scanned
 * - scan for tokens and return one at a time
 * -----------------------------------------------------------------------------
 */
class UBCalculator {
public:
	// constructor
	UBCalculator(){};
	bool check_for_element_vector(vector<Token>, Token);
	void print_stack_testing(stack<Token> s);

	bool check_well_formed(string q);
	// a couple of modifiers
	void setLine(std::string);
	vector<Token> infix2postfix( vector<Token> p);
	vector<Token> multiple_operators(string l);

	bool is_operator(char a);

	int get_priority(char ch);

	float evaluate_postfix(vector<Token> u);

	bool syntax_err(string s);

	//string multiple_ops(string s);

	bool IsNumericDigit(char C);

	float perform_Operation(float x, float y, char z);

private:
/*
	stack<Token> mainStack;
	map<Token, Token> mapStore;
	vector<Token> variables;*/
   static std::map<char, char> createDelimMatch()
	{
		std::map<char, char> m;
		m[')'] = '(';
		m['}'] = '{';
		m[']'] = '[';
		return m;
	}
	static std::map<char, int> createPrecedenceMap()
	{
		std::map<char, int> m;
		m['+'] = 0;
		m['-'] = 0;
		m['*'] = 1;
		m['/'] = 1;
		m['('] = -1;
		m['{'] = -1;
		m['['] = -1;

		return m;
	}

   const static std::map<char, int> precedenceMap;
	const static std::map<char, char> delimMatch;
	const static std::string openDelims; 
	const static std::string closeDelims;
	const static string OPERATORS;
};

#endif
