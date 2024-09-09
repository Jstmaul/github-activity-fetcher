#ifndef CLI_H
#define CLI_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "curl/curl.h"
#include "cjson/cJSON.h"

#define USER_AGENT "github-activity/1.0"

struct MemStruct {
    char* memory;
    size_t size;
};

size_t WriteMemCallBack(void* content, size_t size, size_t nmemb, void* userp);
void fetch_authentichated_user_github(const char* username);

#endif // CLI_H
