#include "ui.h"

#include <stdlib.h>
#include <time.h>

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
  while (1)
  {
    clock_t c0 = clock();

    int c = wgetch(stdscr);
    if (c != ERR)
      if ((*ui->key_callbacks[c])(c) == 0)
        return;

    clock_t c1 = clock();
    double delta_ms = (c1 - c0) * 1000. / CLOCKS_PER_SEC;
  }
}