// *****************************************************************************
// error_handling.h
// ~~~~~~~~~~~~~~~~
// description : error reporting functions
// *****************************************************************************
#ifndef ERROR_HANDLING_H_
#define ERROR_HANDLING_H_

#include <string>
#include <stdexcept>

struct Undefined_Variable_Exception : public std::runtime_error {
	Undefined_Variable_Exception() :
	std::runtime_error("Undefined variable") {}
	Undefined_Variable_Exception(std::string var) :
		std::runtime_error(std::string("Varible ") + var + " undefined") {}
};

struct Undefined_Operator_Exception : public std::runtime_error {
	Undefined_Operator_Exception() :
	std::runtime_error("Undefined operator") {}
	Undefined_Operator_Exception(std::string op) :
		std::runtime_error(std::string("Operator ") + op + " undefined") {}
};

struct DBZ_Exception : public std::runtime_error {
	DBZ_Exception() : std::runtime_error("Divide by zero") {}
};

struct Syntax_Error_Exception : public std::runtime_error {
	Syntax_Error_Exception() : std::runtime_error("Syntax Error") {}
	Syntax_Error_Exception(std::string reason) : std::runtime_error("Syntax Error: " + reason) {}
};


void error_quit(std::string);
void error_return(std::string);
void print_warning(std::string);
void note(std::string);

#endif
