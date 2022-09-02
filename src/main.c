#include "optparse.h"
#include "ui.h"

int quit(int key)
{
  return 0;
}

int main(int argc, char **argv)
{
  struct fox_options options;
  parse_opts(argc, argv, &options);

  struct fox_ui *ui = ui_init();
  ui_key_callback('q', quit, ui);

  ui_loop(ui);

  endwin();
  free(ui);

  return 0;
}