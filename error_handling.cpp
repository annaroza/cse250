// *****************************************************************************
// error_handling.cpp
// ~~~~~~~~~~~~~~~~~~
// author    : Hung Ngo
// description : error reporting functions
// *****************************************************************************
#include <string>
#include <iostream>
#include <stdlib.h>  // for exit()

#include "term_control.h"
#include "error_handling.h"

using std::cerr;
using std::endl;
using std::string;

/**
 * -----------------------------------------------------------------------------
 * report an error and quit
 * -----------------------------------------------------------------------------
 */
void error_quit(string msg) {
    cerr << term_cc(RED) << "** FATAL ERROR: " << msg 
         << endl << term_cc();
    exit(1); // exit on error
}

/**
 * -----------------------------------------------------------------------------
 * report an error and return
 * -----------------------------------------------------------------------------
 */
void error_return(string msg) {
    cerr << term_cc(RED) << "** ERROR **\n" << msg << endl
         << term_cc();
}

/**
 * -----------------------------------------------------------------------------
 * report a warning
 * -----------------------------------------------------------------------------
 */
void print_warning(string msg) {
    cerr << term_cc(YELLOW) << "== Warning ==\n" << msg 
         << endl << term_cc();
}

/**
 * -----------------------------------------------------------------------------
 * print a note to myself
 * -----------------------------------------------------------------------------
 */
void note(string msg) {
    cerr << term_cc(MAGENTA) << "-- Note --\n" << msg 
         << endl << term_cc();
}
