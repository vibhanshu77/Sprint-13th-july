#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../include/loggers.h"
#include "../include/server_functions.h"

void displayFileContent(char* filePath, char* result) {
    LOG_INFO("Reading contents of file - %s", filePath);
    logMessage(INFO, "Reading contents of file - %s", filePath);
    FILE* file = fopen(filePath, "r");
    if (file != NULL) {
        LOG_INFO("File exists - %s", "TRUE");
	logMessage(INFO, "File exists - %s", "TRUE");
        strcat(result, "File exists, content of file:-\n");
        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            strcat(result, buffer);
        }
        fclose(file);
    } else {
        strcpy(result, "File does not exist\n");
        LOG_FATAL("File exists - %s", "FALSE");
	logMessage(FATAL, "File exists - %s", "FALSE");
    }
}
