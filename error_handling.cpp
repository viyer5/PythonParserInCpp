// *****************************************************************************
// error_handling.cpp
// ~~~~~~~~~~~~~~~~~~
// description : error reporting functions
// *****************************************************************************
#include <string>
#include <iostream>
#include <stdlib.h>  // for exit()
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
    cerr << "** FATAL ERROR: " << msg 
         << endl ;
    exit(1); // exit on error
}

/**
 * -----------------------------------------------------------------------------
 * report an error and return
 * -----------------------------------------------------------------------------
 */
void error_return(string msg) {
	cerr <<  "** ERROR **\n" << msg << endl;
}

/**
 * -----------------------------------------------------------------------------
 * report a warning
 * -----------------------------------------------------------------------------
 */
void print_warning(string msg) {
    cerr  << "== Warning ==\n" << msg 
         << endl;
}

/**
 * -----------------------------------------------------------------------------
 * print a note to myself
 * -----------------------------------------------------------------------------
 */
void note(string msg) {
    cerr  << "-- Note --\n" << msg << endl ;
}
