/**
 * *****************************************************************************
 * file name : Postfix_Evaluator.cpp
 * author    : Hung Ngo
 * description : implement the Postfix_Evaluator interface
 * *****************************************************************************
 */
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "Lexer.h"
#include "error_handling.h"
#include "Postfix_Evaluator.h"
using namespace std;

/**
 * -----------------------------------------------------------------------------
 *  lex will provide the input tokens
 * -----------------------------------------------------------------------------
 */
void Postfix_Evaluator::set_expression(vector<Token> tl) 
{
    tok_list = tl;
}

/**
 * -----------------------------------------------------------------------------
 *  lex will provide the input tokens
 * -----------------------------------------------------------------------------
 */
double Postfix_Evaluator::eval_op(char op, double a, double b) 
{
    switch (op ) {
        case '+': return a+b;
        case '-': return a-b;
        case '*': return a*b;
        case '/':
                  if (b == 0)
                      throw runtime_error("Divide by zero");
                  return a/b;
        default:
                  throw runtime_error("Unknown operator");
    }
}

/**
 * -----------------------------------------------------------------------------
 *  evaluate the expression provided by lexer
 * -----------------------------------------------------------------------------
 */
double Postfix_Evaluator::eval() 
{
    while (!operand_stack.empty()) 
        operand_stack.pop(); // empty it out from a previous eval(), or error
    Token tok;
    double a, b;

    if (tok_list.size() == 0)
        throw runtime_error("Empty expression");

    for (size_t i=0; i<tok_list.size(); i++) {    
        tok = tok_list[i];
        switch (tok.type) {
            case NUMBER:
            {
                istringstream buffer(tok.value); 
                buffer >> a;
                operand_stack.push(a);
                break;
            }
            case OPERATOR:
                if (operand_stack.size() < 2) {
                    throw runtime_error(string("Syntax Error: operator " ) +
                                        tok.value + " needs more operand");
                } else {
                    b = operand_stack.top(); operand_stack.pop();
                    a = operand_stack.top(); operand_stack.pop();
                    operand_stack.push(eval_op(tok.value[0], a, b));
                }
                break;
            default:
                throw runtime_error("Syntax error report from Postfix Eval: \
                                    unknown token");
        }
    }

    if (operand_stack.size() != 1)
        throw runtime_error("Syntax error: > 1 operand left on stack");
    else 
        return operand_stack.top();
}
