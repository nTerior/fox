#pragma once

#include "ui.h"

struct fox_editor
{
  char *filename;
  unsigned char *buffer;
  unsigned long buffer_size;
  unsigned long selected_byte;
  unsigned long scrolled;
};

/**
 * @brief Initializing the editor
 *
 * @param filename the file to read, if 0, a buffer_size bytes large buffer will be created
 * @param buffer_size
 * @return struct fox_editor*
 */
struct fox_editor *editor_init(char *filename, unsigned long buffer_size);
void editor_cleanup(struct fox_editor *editor);

/**
 * @brief Renders the editor on stdscr
 *
 * @param editor
 */
void editor_render(struct fox_editor *editor, struct fox_ui *ui);