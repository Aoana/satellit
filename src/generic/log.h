#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <time.h>

#ifdef DEBUG
#define LOG(...) do { \
						fprintf(logfile,"%s %s: ", __DATE__, __TIME__); \
						fprintf(logfile, __VA_ARGS__); \
						fprintf(logfile," %s:%d", __FILE__, __LINE__); \
						fprintf(logfile, "\n"); \
						fflush(logfile); \
					} while (0) /**< Logging Macro. */
#else
#define LOG(...)
#endif

extern FILE *logfile;

/**
 * @brief Initialize logging.
 * @param log Path to logfile, read/write permission needed
 * @return Zero if initilization passed, 1 if failed.
 *
 */
int log_init(char *log);

/**
 * @brief Destroy logging.
 * @return Zero if initilization passed, 1 if failed.
 *
 */
int log_destroy();

#endif

