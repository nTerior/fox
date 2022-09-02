#include "log.h"
#include "ui.h"

#include <ncurses.h>
#include <stdarg.h>

void _log(char *format, va_list farg, int urgency)
{
  ui_print_clear_line(LINES - LOG_RESERVED_SPACE, "---");

  attrset(COLOR_PAIR(urgency));
  ui_vprint_clear_line(LINES - LOG_RESERVED_SPACE + 1, format, farg);
  attrset(COLOR_PAIR(0));
}

void info(char *format, ...)
{
  va_list farg;
  va_start(farg, format);
  _log(format, farg, URGENCY_NORMAL);
  va_end(farg);
}

void warn(char *format, ...)
{
  va_list farg;
  va_start(farg, format);
  _log(format, farg, URGENCY_WARN);
  va_end(farg);
}

void err(char *format, ...)
{
  va_list farg;
  va_start(farg, format);
  _log(format, farg, URGENCY_ERR);
  va_end(farg);
}

void critical(char *format, ...)
{
  va_list farg;
  va_start(farg, format);
  _log(format, farg, URGENCY_CRITICAL);
  va_end(farg);
}