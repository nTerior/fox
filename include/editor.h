#pragma once
#include "ui.h"

struct fox_editor
{
  char *filename;
  unsigned char *buffer;
  long buffer_size;
  long selected_byte;
  long scrolled;

  unsigned char selected_nibble;
};

/**
 * @brief Initializing the editor
 *
 * @param filename the file to read, if 0, a buffer_size bytes large buffer will be created
 * @param buffer_size
 * @return struct fox_editor*
 */
void editor_init(char *filename, long buffer_size, struct fox_ui *ui);
void editor_cleanup();

/**
 * @brief Renders the editor on stdscr
 *
 * @param editor
 */
void editor_render();