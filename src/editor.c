#include "editor.h"

#include "io.h"
#include "ui.h"
#include "utils.h"
#include "log.h"

#include <stdlib.h>
#include <string.h>

#include <ncurses.h>

struct fox_editor *editor_init(char *filename, unsigned long buffer_size)
{
  struct fox_editor *editor = malloc(sizeof(struct fox_editor));

  if (filename != 0)
  {
    editor->filename = malloc(strlen(filename));
    strcpy(editor->filename, filename);
  }
  else
    editor->filename = 0;

  editor->buffer_size = buffer_size;
  editor->selected_byte = 0;
  editor->scrolled = 0;

  if (editor->filename != 0)
    read_file(filename, &editor->buffer, &editor->buffer_size);
  else
    editor->buffer = calloc(buffer_size, 1);

  return editor;
}

void editor_cleanup(struct fox_editor *editor)
{
  free(editor->buffer);
  free(editor->filename);
  free(editor);
}

void editor_render(struct fox_editor *editor)
{
  unsigned long printable_bytes = min(editor->buffer_size, get_printable_lines() * 16);
  unsigned long byte_offset = editor->scrolled * 16;
  int line = 0;
  const int ascii_print_x = 9 + 16 * 2 + 16 + 2;

  for (unsigned long i = byte_offset; i < printable_bytes + byte_offset; i++)
  {
    // hex representation
    if (i >= editor->buffer_size)
      break;
    if (i % 16 == 0)
    {
      attron(A_BOLD);
      ui_print_clear_line(line++, "%08lx: ", i);
      attroff(A_BOLD);
    }
    if (i == editor->selected_byte)
      attrset(COLOR_PAIR(SELECTED_BYTE_COLOR_PAIR));
    printw("%02hhx", editor->buffer[i]);

    // advance cursor to skip 2x attrset
    int _y;
    int _x;
    getyx(stdscr, _y, _x);
    move(_y, _x++);

    // ascii representation
    mvprintw(i / 16, ascii_print_x + i % 16, "%c", get_printable_char(editor->buffer[i]));
    move(_y, _x);
    attrset(COLOR_PAIR(0));
  }
}