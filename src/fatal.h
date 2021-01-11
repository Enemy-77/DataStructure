#include <stdio.h>
#include <stdlib.h>

#define ERROR(Str)      FatalError(Str)
#define FatalError(Str) fprintf(stderr, "%s\n", Str), exit(1)