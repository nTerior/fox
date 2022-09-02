#include "optparse.h"
#include "editor.h"
#include "ui.h"

#include <stdlib.h>
#include <unistd.h>

int quit(__attribute__((unused)) int _)
{
  return 0;
}

void close_fox()
{
  endwin();
  editor_cleanup();
}

int main(int argc, char **argv)
{
  atexit(close_fox);
  struct fox_options options;
  parse_opts(argc, argv, &options);


  struct fox_ui *ui = ui_init();
  ui_key_callback('q', quit, ui);

  editor_init(options.filename, options.buffer_size, ui);
  editor_render();

  ui_loop(ui);
  ui_cleanup(ui);

  free(options.filename);

  return 0;
}