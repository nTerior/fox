#include "optparse.h"
#include "ui.h"

#include <stdlib.h>

int quit(int _)
{
  return 0;
}

void close()
{
  endwin();
}

int main(int argc, char **argv)
{
  atexit(close);

  struct fox_options options;
  parse_opts(argc, argv, &options);

  struct fox_ui *ui = ui_init();
  ui_key_callback('q', quit, ui);

  ui_loop(ui);
  ui_cleanup(ui);

  free(options.filename);

  return 0;
}