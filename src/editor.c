#include "editor.h"

#include "io.h"
#include "utils.h"
#include "log.h"

#include <stdlib.h>
#include <string.h>

#include <ncurses.h>

static struct fox_editor *editor;

void do_scroll(int scroll)
{
  editor->scrolled += scroll;
  editor->selected_byte += scroll * 16;

  int printable_lines = get_printable_lines();

  // clamping selection
  editor->selected_byte = max(editor->selected_byte, 0);
  editor->selected_byte = min(editor->selected_byte, editor->buffer_size - 1);

  // scrolling the display
  long index_on_screen = editor->selected_byte - editor->scrolled * 16;
  if (index_on_screen >= printable_lines * 16)
    editor->scrolled++;
  else if (index_on_screen < 0)
    editor->scrolled--;

  editor->scrolled = min(editor->scrolled, editor->buffer_size / 16 - printable_lines);
  editor->scrolled = max(editor->scrolled, 0);
  editor_render();
}

int do_cursor_click(__attribute__((unused)) int _)
{
  MEVENT event;

  if (getmouse(&event) != OK)
    return 1;

  if (event.bstate == BUTTON4_PRESSED)
  {
    do_scroll(-3);
    return 1;
  }

  if (event.bstate == BUTTON5_PRESSED)
  {
    do_scroll(3);
    return 1;
  }

  // Click event
  if (event.bstate != BUTTON1_PRESSED)
    return 1;

  int clicked_x = -1;
  int clicked_y = event.y;

  // outside of clickable area
  if (clicked_y >= get_printable_lines())
    return 1;

  if (event.x > 9 && event.x < 57)
    clicked_x = (event.x - 10 - (event.x - 10) / 3) / 2;

  // clicked on ascii display
  else if (event.x > 58 && event.x <= 58 + 16)
    clicked_x = event.x - 59;

  if (clicked_x != -1)
  {
    int byte_index = clicked_y * 16 + clicked_x;
    editor->selected_byte = byte_index + editor->scrolled * 16;
    editor_render();
  }

  return 1;
}

int do_cursor_move(int key)
{
  switch (key)
  {
  case KEY_UP:
    editor->selected_byte -= 16;
    break;

  case KEY_LEFT:
    editor->selected_byte--;
    break;

  case KEY_DOWN:
    editor->selected_byte += 16;
    break;

  case KEY_RIGHT:
    editor->selected_byte++;
    break;

  default:
    break;
  }

  do_scroll(0);
  return 1;
}

void editor_init(char *filename, long buffer_size, struct fox_ui *ui)
{
  editor = malloc(sizeof(struct fox_editor));

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

  // do hotkeys
  ui_key_callback(KEY_UP, do_cursor_move, ui);
  ui_key_callback(KEY_DOWN, do_cursor_move, ui);
  ui_key_callback(KEY_LEFT, do_cursor_move, ui);
  ui_key_callback(KEY_RIGHT, do_cursor_move, ui);
  ui_key_callback(KEY_MOUSE, do_cursor_click, ui);
}

void editor_cleanup()
{
  free(editor->buffer);
  free(editor->filename);
  free(editor);
}

void editor_render()
{
  long printable_bytes = min(editor->buffer_size, get_printable_lines() * 16);
  long byte_offset = editor->scrolled * 16;
  int line = 0;
  const int ascii_print_x = 9 + 16 * 2 + 16 + 2;

  for (long i = byte_offset; i < printable_bytes + byte_offset; i++)
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
    _x++;

    // ascii representation
    mvprintw((i - byte_offset) / 16, ascii_print_x + (i - byte_offset) % 16, "%c", get_printable_char(editor->buffer[i]));
    move(_y, _x);
    attrset(COLOR_PAIR(0));
  }
}