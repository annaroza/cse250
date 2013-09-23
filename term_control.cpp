// ****************************************************************************
// file name : term_control.cpp
// author    : Hung Q. Ngo
// description: implementations of a few functions which return a string of 
//              terminal control escape sequences
// ****************************************************************************
#include <sstream>
#include <iostream>
#include "term_control.h"

/**
 * ----------------------------------------------------------------------------
 * output a terminal control code string that formats the text background 
 * ----------------------------------------------------------------------------
 */
std::string term_bg(term_colors_t bg) 
{
    std::ostringstream oss;
    oss << "\033[4" << char(bg) << 'm';
    return oss.str();
}

/**
 * ----------------------------------------------------------------------------
 * output a terminal control code string that formats the text foreground
 * ----------------------------------------------------------------------------
 */
std::string term_fg(term_colors_t fg) 
{
    std::ostringstream oss;
    oss << "\033[3" << char(fg) << 'm';
    return oss.str();
}

/**
 * ----------------------------------------------------------------------------
 * output a terminal control code string that formats the text attribute
 * ----------------------------------------------------------------------------
 */
std::string term_attrib(term_attrib_t attrib) 
{
    std::ostringstream oss;
    oss << "\033[" << char(attrib) << 'm';
    return oss.str();
}

/**
 * ----------------------------------------------------------------------------
 * output a terminal control code string which formats the text background 
 * & foreground colors & text attributes
 * ----------------------------------------------------------------------------
 */
std::string term_cc(term_colors_t fg, term_colors_t bg, term_attrib_t attr) 
{
    std::ostringstream oss;
    oss << "\033[" << char(attr) << ";3" << char(fg) << ";4" << char(bg) << 'm';
    return oss.str();
}

/**
 * ----------------------------------------------------------------------------
 * output a TCES which clears the screen
 * ----------------------------------------------------------------------------
 */
std::string term_clear() 
{
    return "\033[2J";
}
