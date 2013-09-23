// ============================================================================ 
// Postfix_Evaluator.h
// ~~~~~~~~~~~~~~~~~~~
// Hung Q. Ngo
// - interface to the Postfix_Evaluator class
// ============================================================================ 


#ifndef _POSTFIX_EVALUATOR_H
#define _POSTFIX_EVALUATOR_H

#include <stack>
#include <vector>
#include "Lexer.h"

class Postfix_Evaluator {
    public:
    // constructors
    Postfix_Evaluator(std::vector<Token> tl=std::vector<Token>())
        : tok_list(tl), operand_stack() {}

    // set the postfix expression to be evaluated
    void set_expression(std::vector<Token>);

    // evaluate the expression, throw runtime_exeption()
    // "Syntax error" if the token list is not a proper postfix expr.
    // "Division by zero"
    // "Empty expression"
    double eval();

    private:
    // given an operator op, and two operands a and b, return (a op b)
    // throw "Division by zero" runtime_exception() when appropriate
    // or "Unknown Operator" if 
    double eval_op(char op, double a, double b);

    std::vector<Token> tok_list;
    std::stack<double> operand_stack;
};

#endif
