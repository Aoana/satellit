#include "log.h"

FILE *logfile;

int log_init(char *log) {

	logfile = fopen(log, "a+"); 

	if(logfile == NULL) {
		return 1;
	}
	return 0;
}
