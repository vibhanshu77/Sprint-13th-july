#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

#include "../include/loggers.h"
#include "../include/server_functions.h"

void searchInDirectory(const char* dirPath, const char* searchString, char* result) {
    DIR* directory = opendir(dirPath);
    if (directory == NULL) {
        LOG_FATAL("Unable to open %s", "directory");
	logMessage(FATAL, "Unable to open %s","directory");
        return;
    }
    struct dirent* entry;
    while ((entry = readdir(directory)) != NULL) {
        if (entry->d_name[0] != '.' && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            char fullPath[PATH_MAX];
            snprintf(fullPath, sizeof(fullPath), "%s/%s", dirPath, entry->d_name);
            if (entry->d_type == DT_DIR) {
                if (strcmp(entry->d_name, "/") == 0 || strcmp(entry->d_name, "/proc") == 0 ||
                    strcmp(entry->d_name, "/sys") == 0 || strcmp(entry->d_name, "/dev") == 0)
                    continue;
                searchInDirectory(fullPath, searchString, result);
            } else if (entry->d_type == DT_REG) {
                searchInFile(fullPath, searchString, result);
            }
        }
    }
    closedir(directory);
}
