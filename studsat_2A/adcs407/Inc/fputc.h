#ifndef FPUTC_H
	#define FPUTC_H

#include "gps.h"

/*typedef struct __FILE {int handle;}FILE;
FILE __stdout;
FILE __stdin;
*/
int fputc(int c, FILE *stream);

#endif
