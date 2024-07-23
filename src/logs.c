#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#include "../include/loggers.h"

// Function to write log messages to file
void logMessage(LogLevel level, const char *message, ...) {
    // Open log file in append mode
    FILE *logFile = fopen("/home2/user16/Sprint-13th-july/logs/logfile.txt", "a");
    if (logFile == NULL) {
        fprintf(stderr, "Error opening log file.\n");
        return;
    }

    // Get current time
    time_t rawTime;
    struct tm *timeInfo;
    char timeString[80];

    time(&rawTime);
    timeInfo = localtime(&rawTime);
    strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", timeInfo);

    // Get log level string
    const char *levelString;
    switch (level) {
        case DEBUG:
            levelString = "DEBUG";
            break;
        case INFO:
            levelString = "INFO ";
            break;
        case WARN:
            levelString = "WARN ";
            break;
        case FATAL:
            levelString = "FATAL";
            break;
        default:
            levelString = "UNKNOWN";
    }

    // Print log message to file
    fprintf(logFile, "[%s] [%s] ", timeString, levelString);

    va_list args;
    va_start(args, message);
    vfprintf(logFile, message, args);
    va_end(args);

    fprintf(logFile, "\n");

    // Close log file
    fclose(logFile);
}
