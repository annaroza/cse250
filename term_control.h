// ****************************************************************************
// term_control.h
// ~~~~~~~~~~~~~~
// author    : Hung Q. Ngo
// description: a few functions which output terminal control escape sequences
// ****************************************************************************

#ifndef TERM_CONTROL_H_
#define TERM_CONTROL_H_

#include <string>

// the attributes
enum term_attrib_t {
    DEFAULT_ATTRIB = '0',
    BRIGHT    = '1',
    DIM       = '2',
    UNDERLINE = '4',
    BLINK     = '5',
    REVERSE   = '7',
    HIDDEN    = '8'
};

// the colors, background or foreground
enum term_colors_t {
    BLACK   = '0',
    RED     = '1',
    GREEN   = '2',
    YELLOW  = '3',
    BLUE    = '4',
    MAGENTA = '5',
    CYAN    = '6',
    WHITE   = '7',
    DEFAULT_COLOR = '9'
};


/**
 * ----------------------------------------------------------------------------
 * term_cc() outputs the corresponding terminal control escape sequence (TCES)
 *
 * usage:
 * cout << term_cc(YELLOW) << "This text is yellow\n" << term_cc();
 * cout << term_cc(BLUE, YELLOW, BLINK) << "I'm blinking blue on yellow!\n"    
 * cout << term_fg(YELLOW) << "This text is yellow\n" << term_cc();
 *
 * term_clear() outputs the TCES which clears the screen
 * ----------------------------------------------------------------------------
 */
std::string term_cc(term_colors_t fg=DEFAULT_COLOR, 
                    term_colors_t bg=DEFAULT_COLOR, 
                    term_attrib_t attr=DEFAULT_ATTRIB);
std::string term_bg(term_colors_t bg=DEFAULT_COLOR);
std::string term_fg(term_colors_t fg=DEFAULT_COLOR);
std::string term_attrib(term_attrib_t attrib=DEFAULT_ATTRIB);
std::string term_clear();

#endif // TERM_CONTROL_H_
