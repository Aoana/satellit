#include "log.h"

FILE *logfile;

int log_init(char *log) {

	logfile = fopen(log, "a+"); 

	if(logfile == NULL) {
		return 1;
	}
	return 0;
}

int log_destroy() {

	if(fclose(logfile) != 0) {
		return 1;
	}
	return 0;

}
