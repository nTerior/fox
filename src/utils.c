#include "utils.h"

#include <ctype.h>
#include <string.h>

int is_number(char *str)
{
  for (size_t i = 0; i < strlen(str); i++)
  {
    if (!isdigit(str[i]))
      return 0;
  }
  return 1;
}