// ============================================================================ 
// infix.h
// ~~~~~~~
// Hung Q. Ngo
// ============================================================================ 

#ifndef INFIX_H_
#define INFIX_H_

#include <map>
#include <string>
#include <vector>
#include "Lexer.h"

// returns true if the expr is a valid infix expression
bool validate_infix_expr(std::vector<Token> ie);

// evaluate the infix expression, variables' values are given in the symbol
// table. This function converts the infix expression into postfix, then
// call the postfix expression evaluator
double eval_infix_expr(std::vector<Token> ie, 
                       std::map<std::string, double> symbol_table);

#endif // INFIX_H_
