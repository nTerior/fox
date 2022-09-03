#include "ui.h"
#include "log.h"
#include "timer.h"
#include "utils.h"

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

struct fox_ui *ui_init()
{
  initscr();
  raw();
  keypad(stdscr, TRUE);
  noecho();
  set_escdelay(0);
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

void ui_key_callback(int key, void (*callback)(int), struct fox_ui *ui)
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
        (*ui->key_callbacks[c])(c);
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

char *ui_get_string(char *prompt, int maxlen, char *initial)
{
  char *res;
  if (initial)
  {
    res = calloc(max(maxlen, strlen(initial)), 1);
    strcpy(res, initial);
  }
  else
  {
    res = calloc(maxlen, 1);
  }

  while (1)
  {
    info("%s: %s|", prompt, res);
    int c = wgetch(stdscr);

    // extra keys
    if (c < ' ' || c > '~')
    {
      // submit
      if ((c == KEY_ENTER || c == 10) && strlen(res) != 0)
      {
        res = realloc(res, strlen(res));
        return res;
      }
      else if (c == KEY_BACKSPACE)
      {
        res[strlen(res) - 1] = 0;
      }
      // esc or alt
      else if (c == 27)
      {

        nodelay(stdscr, TRUE);

        int w = wgetch(stdscr);
        // esc key
        if (w == ERR)
        {
          free(res);
          return 0;
        }

        nodelay(stdscr, FALSE);
      }
    }
    else
    {
      if (strlen(res) >= maxlen)
        continue;
      char tmp[] = {c, 0};
      strcat(res, tmp);
    }
  }
}