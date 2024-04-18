#include "util.h"
#include <stdlib.h>
#include <string.h>

char *copied_string(char *str) {
  unsigned len = strlen(str) + 1;
  char *new = (char *)malloc(len);
  if(!new) {
    return NULL;
  }
  memcpy(new, str, len);
  return new;
}
