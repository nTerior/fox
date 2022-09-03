#include "editor.h"

#include "io.h"
#include "utils.h"
#include "log.h"
#include "timer.h"

#include <stdlib.h>
#include <string.h>

#include <ncurses.h>

static struct fox_editor *editor;

void delayed_kb_info()
{
  DEFAULT_LOG;
}

void save(__attribute__((unused)) int _)
{
  char *name = ui_get_string("Enter filename", 255, editor->filename);

  if (name == 0)
  {
    delayed_kb_info();
    return;
  }

  int res = write_file(name, editor->buffer, editor->buffer_size);
  if (res == IO_MISSING_PERMS)
    err("You don't have the required permissions to save to %s!", name);
  else if (res == IO_DIRECTORY)
    err("%s is actually a directory", name);
  else if (res == IO_FAIL)
    critical("Cannot write to %s!", name);
  else
  {
    editor->filename = realloc(editor->filename, strlen(name));
    strcpy(editor->filename, name);
    info("File saved to: %s", name);
  }
  add_timer(5000, delayed_kb_info);
  free(name);
}

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

  editor->scrolled = min(editor->scrolled, editor->buffer_size / 16 - printable_lines + 1);
  editor->scrolled = max(editor->scrolled, 0);
  editor_render();

  editor->selected_nibble = 0;
}

void do_cursor_click(__attribute__((unused)) int _)
{
  MEVENT event;

  if (getmouse(&event) != OK)
    return;

  if (event.bstate == BUTTON4_PRESSED)
  {
    do_scroll(-3);
    return;
  }

  if (event.bstate == BUTTON5_PRESSED)
  {
    do_scroll(3);
    return;
  }

  // Click event
  if (event.bstate != BUTTON1_PRESSED)
    return;

  int clicked_x = -1;
  int clicked_y = event.y;

  // outside of clickable area
  if (clicked_y >= get_printable_lines())
    return;

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
    editor->selected_nibble = 0;
  }
}

void do_cursor_move(int key)
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
}

void edit_nibble(int key)
{
  unsigned char mask = 0;
  if (key <= '9')
    mask = key - '0';
  else
    mask = key - 'a' + 0xa;

  unsigned char *byte = &editor->buffer[editor->selected_byte];

  if (editor->selected_nibble == 0)
  {
    mask <<= 4;
  }
  else
  {
    if (editor->selected_byte != editor->selected_byte - 1)
      editor->selected_byte++;
  }
  *byte = (0xff & mask) | (*byte & ~mask);

  editor->selected_nibble = !editor->selected_nibble;
  editor_render();
}

void insert_byte()
{
  int pos = editor->selected_byte + 1;
  editor->buffer = realloc(editor->buffer, editor->buffer_size + 1);
  memmove(editor->buffer + pos + 1, editor->buffer + pos, editor->buffer_size - pos);
  editor->buffer[pos] = 0;
  editor->buffer_size++;
  editor->selected_byte++;
  editor_render();
}

void delete_byte()
{
  long len = editor->buffer_size;
  if (len <= 0)
  {
    err("You cannot delete anything from an empty file!");
    add_timer(5000, delayed_kb_info);
    return;
  }
  long pos = editor->selected_byte;

  int size = len - pos - 1;
  unsigned char tmp[size];

  memcpy(tmp, editor->buffer + pos + 1, size);
  memcpy(editor->buffer + pos, tmp, size);
  editor->buffer_size--;
  editor->buffer = realloc(editor->buffer, editor->buffer_size);

  if (editor->selected_byte >= editor->buffer_size)
    editor->selected_byte--;

  editor_render();
}

void editor_init(char *filename, long buffer_size, struct fox_ui *ui)
{
  editor = malloc(sizeof(struct fox_editor));

  if (filename != 0)
  {
    editor->filename = malloc(strlen(filename) + 1);
    strcpy(editor->filename, filename);
  }
  else
    editor->filename = 0;

  editor->buffer_size = buffer_size;
  editor->selected_byte = 0;
  editor->selected_nibble = 0;
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

  // editing nibbles
  ui_key_callback('0', edit_nibble, ui);
  ui_key_callback('1', edit_nibble, ui);
  ui_key_callback('2', edit_nibble, ui);
  ui_key_callback('3', edit_nibble, ui);
  ui_key_callback('4', edit_nibble, ui);
  ui_key_callback('5', edit_nibble, ui);
  ui_key_callback('6', edit_nibble, ui);
  ui_key_callback('7', edit_nibble, ui);
  ui_key_callback('8', edit_nibble, ui);
  ui_key_callback('9', edit_nibble, ui);
  ui_key_callback('a', edit_nibble, ui);
  ui_key_callback('b', edit_nibble, ui);
  ui_key_callback('c', edit_nibble, ui);
  ui_key_callback('d', edit_nibble, ui);
  ui_key_callback('e', edit_nibble, ui);
  ui_key_callback('f', edit_nibble, ui);

  // extra
  ui_key_callback('s', save, ui);
  ui_key_callback('i', insert_byte, ui);
  ui_key_callback(KEY_DC, delete_byte, ui);
}

void editor_cleanup()
{
  if (!editor)
    return;
  free(editor->buffer);
  free(editor->filename);
  free(editor);
}

void editor_render()
{
  long printable_bytes = min(editor->buffer_size, get_printable_lines() * 16);

  // clear lines
  for (int line = 0; line <= printable_bytes / 16; line++)
  {
    move(line, 0);
    clrtoeol();
  }
  move(0, 0);

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
  refresh();
}