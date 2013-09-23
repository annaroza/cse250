// *****************************************************************************
// error_handling.h
// ~~~~~~~~~~~~~~~~
// author      : Hung Ngo
// description : error reporting functions
// *****************************************************************************
#ifndef ERROR_HANDLING_H_
#define ERROR_HANDLING_H_

#include <string>

void error_quit(std::string);
void error_return(std::string);
void print_warning(std::string);
void note(std::string);

#endif
