#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

#include "../include/loggers.h"
#include "../include/server_functions.h"

void searchInFile(const char* filePath, const char* searchString, char* result) {
    FILE* file = fopen(filePath, "r");
    if (file != NULL) {
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            if (strstr(buffer, searchString) != NULL) {
                LOG_INFO("String found in file - %s", filePath);
		logMessage(INFO,"String found in file - %s", filePath);
                strcat(result, filePath);
                strcat(result, "\n");
                break;
            }
        }
        fclose(file);
    } else {
        LOG_FATAL("Unable to open %s", "file");
	logMessage(FATAL, "Unable to open %s", "file");
    }
}
