#include "optparse.h"
#include "editor.h"
#include "ui.h"
#include "log.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static struct fox_options options;
static struct fox_ui *ui;

void quit(__attribute__((unused)) int _)
{
  exit(0);
}

void close_fox()
{
  endwin();
  editor_cleanup();
  if(ui)
    ui_cleanup(ui);
  if(options.filename)
    free(options.filename);
}

int main(int argc, char **argv)
{
  atexit(close_fox);

  parse_opts(argc, argv, &options);

  ui = ui_init();
  ui_key_callback('q', quit, ui);

  editor_init(options.filename, options.buffer_size, ui);
  editor_render();

  DEFAULT_LOG;

  ui_loop(ui);

  return 0;
}