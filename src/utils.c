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

long min(long a, long b)
{
  return a < b ? a : b;
}

long max(long a, long b)
{
  return a > b ? a : b;
}

char get_printable_char(char c)
{
  if (isprint(c) && c != ' ')
    return c;
  return '.';
}