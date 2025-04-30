#include "globals.h"

/* Global variables */
char tokenString[MAXTOKENLEN+1];
FILE* source;
FILE* listing;
int TraceScan = FALSE;
int lineno = 0; 