#include "cli.h"

size_t WriteMemCallBack(void* contents, size_t size, size_t nmemb,
                        void* userp) {
  size_t rsize = size * nmemb;
  struct MemStruct* mem = (struct MemStruct*)userp;

  char* ptr = realloc(mem->memory, mem->size + rsize + 1);
  if (ptr == NULL) {
    printf("Error: Not enough memory\n");
    return 0;
  }

  mem->memory = ptr;
  memcpy(&(mem->memory[mem->size]), contents, rsize);
  mem->size += rsize;
  mem->memory[mem->size] = 0;

  return rsize;
}

void fetch_authentichated_user_github(const char* username) {
  CURL* curl;
  CURLcode res;
  char url[256];
  struct MemStruct chunk;

  chunk.memory = malloc(1);
  chunk.size = 0;

  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();
  if (curl) {
    snprintf(url, sizeof(url), "https://api.github.com/users/%s/events",
             username);

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, USER_AGENT);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemCallBack);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    } else {
      cJSON* json = cJSON_Parse(chunk.memory);
      if (json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
      } else {
        cJSON* event;
        cJSON_ArrayForEach(event, json) {
          cJSON* type = cJSON_GetObjectItemCaseSensitive(event, "type");
          cJSON* repo = cJSON_GetObjectItemCaseSensitive(event, "repo");
          if (type && repo && cJSON_IsString(type) && cJSON_IsObject(repo)) {
            cJSON* name = cJSON_GetObjectItemCaseSensitive(repo, "name");
            if (name && cJSON_IsString(name)) {
              printf("- %s %s\n", type->valuestring, name->valuestring);
            }
          }
        }
        cJSON_Delete(json);
      }
    }

    curl_easy_cleanup(curl);
    free(chunk.memory);
  } else {
    fprintf(stderr, "Error initializing CURL\n");
  }

  curl_global_cleanup();
}