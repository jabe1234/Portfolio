//  CSCIx239 library
//  Willem A. (Vlakkies) Schreuder
#include "CSCIx229.h"

//
//  Check for OpenGL errors and print to stderr
//  Taken from class example 13
//
void ErrCheck(const char* where)
{
   int err = glGetError();
   if (err) fprintf(stderr,"ERROR: %s [%s]\n",gluErrorString(err),where);
}
