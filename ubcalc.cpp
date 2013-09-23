// ubcalc.cpp
// ~~~~~~~~~~~~
// Hung Q. Ngo
// - simple driver program to test the infix evaluation routine
// - and to test the routine to validate an infix expression syntax
#include <iostream>
#include <map>
#include <cstdlib>
#include <stdexcept>

#include "Lexer.h"
#include "infix.h"
#include "term_control.h"
#include "error_handling.h"
using namespace std;

// ----------------------------------------------------------------------------
// prototypes and typedefs
// ----------------------------------------------------------------------------
typedef void (*cmd_t)(Lexer);
void eval_expr(Lexer);     // print the value of an expression
void assign(Lexer);        // assign a variable to be an exp
void validate_expr(Lexer); // reports whether an infix expression is valid
void bye(Lexer);           // simply quit
void prompt();

static map<string, double> sym_table; // global map of variables to values
extern const string usage_msg;

/**
 * ----------------------------------------------------------------------------
 * the body
 * ----------------------------------------------------------------------------
 */
int main() 
{
    Lexer lexer; string line; Token tok;
    map<string,cmd_t> cmd_map;
    cmd_map["exit"]     = &bye;
    cmd_map["bye"]      = &bye;
    cmd_map["eval"]     = &eval_expr;
    cmd_map["validate"] = &validate_expr;
    cmd_map["assign"]   = &assign;

    cout << term_cc(YELLOW) << usage_msg << endl;

    while (cin) {
        prompt(); getline(cin, line); lexer.set_input(line);
        if (!lexer.has_more_token()) continue;
        tok = lexer.next_token();
        if (tok.type != IDENT) { error_return("Syntax error\n"); continue; }   

        if (cmd_map.find(tok.value) != cmd_map.end())
            cmd_map[tok.value](lexer);
        else
            error_return("Unknown command");
    }
    return 0;
}

/**
 * -----------------------------------------------------------------------------
 * eval the expression if there's no error
 * -----------------------------------------------------------------------------
 */
void eval_expr(Lexer lexer) 
{
    double result;
    try {
        result = eval_infix_expr(lexer.tokenize(), sym_table);
        cout << term_cc(CYAN) << "= " << result << term_cc() << endl;
    } 
    catch (runtime_error &e) {
        error_return(e.what());
    }
}

/**
 * -----------------------------------------------------------------------------
 * check whether an infix expression is valid or not
 * this is regardless of whether the variables are defined
 * -----------------------------------------------------------------------------
 */
void validate_expr(Lexer lexer) 
{
    if (validate_infix_expr(lexer.tokenize()))
        cout << term_cc(CYAN) << "Valid expression" << endl;
    else
        cout << term_cc(RED) << "Invalid expression" << endl;
    return;
}

/**
 * -----------------------------------------------------------------------------
 * assign a variable to be equal to an expression
 * -----------------------------------------------------------------------------
 */
void assign(Lexer lexer) 
{
    double result;
    Token var_tok, assign_tok;

    // looking for the variable name
    if (!lexer.has_more_token() || 
        (var_tok = lexer.next_token()).type != IDENT) {
        error_return("Syntax error: assign var = expression");
        return;
    }

    // looking for the = sign
    if (!lexer.has_more_token() || 
        (assign_tok = lexer.next_token()).type != OPERATOR || 
        assign_tok.value[0] != '=') {
        error_return("Syntax error: assign var = expression");
        return;
    }

    try {
        result = eval_infix_expr(lexer.tokenize(), sym_table);
        sym_table[var_tok.value] = result;
        cout << term_cc(CYAN) << var_tok.value << " = " 
             << result << term_cc() << endl;
    } 
    catch (runtime_error &e) {
        error_return(e.what());
    }
}

/**
 * -----------------------------------------------------------------------------
 * terminates the program, ignores all parameters
 * -----------------------------------------------------------------------------
 */
void bye(Lexer lexer) 
{
    if (lexer.has_more_token()) {
        error_return("Syntax error: use bye/exit/quit\n");
    } else {
        exit(0);
    }   
}

/**
 * ----------------------------------------------------------------------------
 * just print a prompt.
 * ----------------------------------------------------------------------------
 */
void prompt() 
{ 
    cout << term_cc(BLUE) << "> " << term_cc() << flush; 
}

