#include <stdio.h>
#include <iostream>
#include <stdarg.h>

// print out the steps and errors
void logging(const char *fmt, ...) {
  va_list args;
  fprintf( stderr, "LOG: " );
  va_start( args, fmt );
  vfprintf( stderr, fmt, args );
  va_end( args );
  fprintf( stderr, "\n" );
}
