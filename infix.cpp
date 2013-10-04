// ============================================================================ // infix.cpp
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
                                "  Author: ANNA ROZANSKY\n"
                                "  Report bugs to annaroza@buffalo.edu";

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
        int opCounter = 0;
        int numCounter = 0;
        bool valid;
        stack<string> delimStack;
        for (unsigned int i =0; i<ie.size(); i++){
                if((ie.at(i).value==("(")) || (ie.at(i).value==("[")) || (ie.at(i).value==("{"))){
                        string val = ie.at(i).value;
                        delimStack.push(val);
                }
                if(delimStack.empty() && ((ie.at(i).value==")")||(ie.at(i).value=="]")||(ie.at(i).value=="}"))){
                        return false;
                        break;
                }
                else if((ie.at(i).value==(")")) && (delimStack.top() == "(")){
                        valid = true;
                        delimStack.pop();
                }
                else if((ie.at(i).value==("]")) && (delimStack.top() == "[")){
                        valid = true;
                        delimStack.pop();
                }
                else if((ie.at(i).value==("}")) && (delimStack.top() == "{")){
                        valid = true;
                        delimStack.pop();
                }
                else if((ie.at(i).type == NUMBER) || (ie.at(i).type == IDENT)){
                        numCounter++;
                        if((numCounter >= 2) && (opCounter == 0)){
                                return false;
                                break;
                        }
                        else{
                                valid = true;
                        }
                }
                else if(ie.at(i).type == OPERATOR){
                        if(numCounter == 1){
                                opCounter++;
                                numCounter--;
                        }
                        else{
                                cerr << "Cannot start with an operator" << endl;
                                return false;
                                break;
                        }
                        if((ie.at(i).value == "/") && (ie.at(i+1).value == "0")){
                                cerr << "Cannot divide by zero" << endl;
                                return false;
                                break;
                        }
                        if(ie.at(ie.size()-1).type == OPERATOR){
                                cerr << "Cannot evaluate an expression ending with an operator" << endl;
                                return false;
                                break;
                        }
                }
                if((ie.at(i).type == OPERATOR)&&(ie.at(i+1).type == OPERATOR)){
                        cerr << "Cannot have two operators next to each other" << endl;
                        return false;
                        break;
                }
                if(ie.at(i).type==ERRTOK){
                        cerr << "Invalid tokens used" << endl;
                        return false;
                        break;
                }
                else{
                        valid = false;
                }
        }
        if(numCounter==opCounter){                      //CHECK
                valid = true;
        }
        if((numCounter==0)&&(opCounter==1)){
                cerr << "Cannot evaluate one number with one operator" << endl;
                return false;
        }
        if(numCounter==0){
                cerr << "Enter an expression that contains numbers" << endl;
                return false;
        }
        if(delimStack.empty()){
                valid = true;
        }
        else{
                valid = false;
        }
        return valid;
}


/**     
                if(opCounter > (numCounter/2)){
                        return false;
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

int precedence(Token tok){
        int precedence = 0;
        if(tok.type == DELIM){
                precedence = 3;
        }
        if(tok.value == "*"){
                precedence = 2;
        }
        if(tok.value == "/"){
                precedence = 2;
        }
        if(tok.value == "+"){
                precedence = 1;
        }
        if(tok.value == "-"){
                precedence = 1;
        }
        return precedence;
}


double eval_infix_expr(vector<Token> ie, map<string,double> sym_tab){
        vector<Token> postfix_expr;
        stack<Token> opStack;
        validate_infix_expr(ie);
        for(int i = 0; i<ie.size(); i++){
                Token tok = ie.at(i);
                if(tok.type == OPERATOR){
                        if((!opStack.empty()) && (opStack.top().type == OPERATOR)){
                                if(precedence(tok) > (precedence(opStack.top()))){      //when token precedence is higher than top of stack 
                                        //opStack.push(tok);
                                }
                                else if(precedence(tok) == precedence(opStack.top())){  //when token precedence == precedence of top of stack
                                        postfix_expr.push_back(opStack.top());
                                        opStack.pop();
                                }
                                else{                                           //when token has lower precedence than the top of the stack     
                                        while(!opStack.empty() && (precedence(tok) <= (precedence(opStack.top())))){
                                                postfix_expr.push_back(opStack.top());
                                                opStack.pop();
                                        }
                                }
                        }
                        opStack.push(tok);
                }
                else if(tok.type == NUMBER){
                        postfix_expr.push_back(tok);
                }
                else if(tok.type == IDENT){
                        if(sym_tab.count(tok.value)==1){
                                ostringstream oss;
                                oss << sym_tab.at(tok.value);
                                Token strTok = Token(NUMBER, oss.str());
                                postfix_expr.push_back(strTok);
                        }
                        else{
                                cerr << "Variable has not been defined" << endl;
                        }
                        //account for if undefined in the map
                }
                else if((tok.value == "(") || (tok.value == "[") || (tok.value == "{")){
                        validate_infix_expr(ie);
                        opStack.push(tok);
                }
                else if((tok.value == ")") || (tok.value == "]") || (tok.value == "}")){
                        while(opStack.top().type != DELIM){
                                postfix_expr.push_back(opStack.top());
                                opStack.pop();
                        }
                        if((opStack.top().value == "(") || (opStack.top().value == "[") || (opStack.top().value == "{")){
                                opStack.pop();
                        }
                }
        }
        while(!opStack.empty()){
                postfix_expr.push_back(opStack.top());
                opStack.pop();
        }
        // call the postfix evaluator to evaluate it
        Postfix_Evaluator pe(postfix_expr);
        return pe.eval();
}
