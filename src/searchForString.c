#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

#include "../include/loggers.h" 
#include "../include/server_functions.h"

void searchForString(const char* searchString, char* result) {
    LOG_INFO("Searching for the string ' %s ' in the filesystem", searchString);
    logMessage(INFO, "Searching for the string '%s' in the filesystem", searchString);
    searchInDirectory("/home2/user16", searchString, result);
}


