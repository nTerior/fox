#include "ui.h"
#include "log.h"
#include "timer.h"

#include <stdlib.h>
#include <stdarg.h>

struct fox_ui *ui_init()
{
  initscr();
  raw();
  keypad(stdscr, TRUE);
  noecho();
  nodelay(stdscr, TRUE);

  curs_set(0);

  mouseinterval(0);
  mousemask(BUTTON1_PRESSED | BUTTON4_PRESSED | BUTTON5_PRESSED, NULL);

  if (has_colors() && can_change_color())
  {
    start_color();
  }

  init_pair(URGENCY_WARN, COLOR_YELLOW, COLOR_BLACK);
  init_pair(URGENCY_ERR, COLOR_RED, COLOR_BLACK);
  init_pair(URGENCY_CRITICAL, COLOR_WHITE, COLOR_RED);

  init_pair(SELECTED_BYTE_COLOR_PAIR, COLOR_BLACK, COLOR_WHITE);

  struct fox_ui *ui = malloc(sizeof(struct fox_ui));
  for (int i = 0; i < KEY_MAX; i++)
  {
    ui->key_callbacks[0] = 0;
  }
  return ui;
}

void ui_cleanup(struct fox_ui *ui)
{
  free(ui);
}

void ui_key_callback(int key, int (*callback)(int), struct fox_ui *ui)
{
  if (key >= KEY_MAX)
    return;

  ui->key_callbacks[key] = callback;
}

void ui_loop(struct fox_ui *ui)
{
  ui_print_clear_line(LINES - 2, "---");
  while (1)
  {
    int c = wgetch(stdscr);
    if (c != ERR)
    {
      if (ui->key_callbacks[c] != 0)
        if ((*ui->key_callbacks[c])(c) == 0)
          return;
    }
  }
}

void ui_print_line(int line, char *format, ...)
{
  va_list arg;
  va_start(arg, format);
  ui_print_clear_line(line, format, arg);
  va_end(arg);
}

void ui_print_clear_line(int line, char *format, ...)
{
  va_list arg;
  va_start(arg, format);
  ui_vprint_clear_line(line, format, arg);
  va_end(arg);
}

void ui_vprint_line(int line, char *format, va_list arg)
{
  move(line, 0);
  vw_printw(stdscr, format, arg);
}
void ui_vprint_clear_line(int line, char *format, va_list arg)
{
  move(line, 0);
  clrtoeol();
  vw_printw(stdscr, format, arg);
}

int get_printable_lines()
{
  return LINES - LOG_RESERVED_SPACE;
}