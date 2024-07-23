#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../include/loggers.h"
#include "../include/server_functions.h"

void searchForFile(char* filePath, char* result) {
    LOG_INFO("Searching for a file in filesystem with filePath - %s", filePath);
    logMessage(INFO, "Searching for a file in filesystem with filePath - ", filePath);
    FILE* file = fopen(filePath, "r");
    if (file != NULL) {
        fclose(file);
        strcat(result, "Yes, the file exists!");
        LOG_INFO("File exists - %s", "TRUE");
	logMessage(INFO, "File exists - %s", "TRUE");
    } else {
        strcat(result, "No, the file does not exist!");
        LOG_FATAL("File exists - %s", "FALSE");
	logMessage(FATAL, "File exists - %s", "FALSE");
    }
}
