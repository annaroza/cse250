// ============================================================================ 
// infix.cpp
// ~~~~~~~~~
// ANNA ROZANSKY
// - implement two functions, one to verify whether an infix expression is valid
//   and the other one evaluate the given infix expression
// ============================================================================ 
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <stack>

#include "Lexer.h"
#include "Postfix_Evaluator.h"
#include "error_handling.h"
#include "infix.h"

using namespace std; // BAD practice

extern const string usage_msg = "UB Calculator Program. Version 0.1\n"
                                "  Author: YOUR NAME\n"
                                "  Report bugs to YOURID@buffalo.edu";

/**
 * -----------------------------------------------------------------------------
 * return true if the infix expression given by the token vector 'ie' is valid
 * false if it is invalid
 * we don't care whether the variables are defined in the expressions, thus
 * (a+0.4)*bcd - [(4+4.5)/2 - x]/3.0 is valid
 * even if the variables a, bcd, and x are not assigned previously
 * -----------------------------------------------------------------------------
 */
bool validate_infix_expr(vector<Token> ie){
    // YOUR CODE GOES HERE
	int opCounter = 0;
	int numCounter = 0;	
	stack<char> delimStack;						//type for stack??
	for (unsigned int i =0; i<ie.size(); i++){
		if((ie.at(i).value.equals('(')) || (ie.at(i).value.equals('[')) || (ie.at(i).value.equals('{'))){
			delimStack.push(ie.at(i));
		}
		else if((ie.at(i).value.equals(')')) || (ie.at(i).value.equals(']')) || (ie.at(i).value.equals('}'))){
			if(delimStack.empty()){
				return false;
			}
			if(delimStack.top().type != ie.at(i).type){
				return false;
			}
			delimStack.pop();
		}
	}
	if(delimStack.empty()){
		return true;
	}
	else{
		return false;
	}	
	return false;
}



/**		if(ie.at(i).type==DELIM){				//if the token is a delimiter
			while(!delimStack.empty()){			//while the stack is not empty
				if(ie.at(i) != delimStack.top()){	//if the current token is not the same as the top token on the stack
					delimStack.push(ie.at(i));	//then add it to the stack
				}
				else if(ie.at(i) == delimStack.top()){	//if the current token matches the top token on the stack
					delimStack.pop();		//take the token off the stack -- match
				}
			}
			while(delimStack.empty()){			//while the stack is empty
				delimStack.push(ie.at(i));		//push the current token onto the stack
			}
			return true;
		}

		if(ie.at(i).type == OPERATOR){
			opCounter++;
		}
		if(ie.at(i).type==NUMBER){
			numCounter++;
		}
	 	if((ie.at(i).type == OPERATOR)&&(ie.at(i+1).type == OPERATOR)){
			return false;
		}
		if(opCounter > (numCounter/2)){
			return false;
		}
	}
*/


/**
 * -----------------------------------------------------------------------------
 * convert an infix expression into postfix using the Shunting Yard algo
 * evaluate it and return, using the postfix evaluator
 * - ie is a token list of tokens forming the expression
 * - sym_tab is a symbol table, holding the values of variables already defined
 * - when anything goes not as expected, throw a runtime_error exception
 *   + undefined identifier (i.e. can't find it in sym_tab)
 *   + wrong infix expression (syntax error)
 *   + etc.
 * -----------------------------------------------------------------------------
 */
double eval_infix_expr(vector<Token> ie, map<string,double> sym_tab){
    vector<Token> postfix_expr;
    
    // convert ie in to a postfix expression, stored in postfix_expr
    
    // YOUR CODE GOES HERE

    // call the postfix evaluator to evaluate it
    Postfix_Evaluator pe(postfix_expr);
    return pe.eval();
}
