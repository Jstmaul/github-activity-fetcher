#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cli.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <username>\n", argv[0]);
    return 1;
  }

  fetch_authentichated_user_github(argv[1]);

  return 0;
}
