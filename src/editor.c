#include "editor.h"

#include "io.h"

#include <stdlib.h>
#include <string.h>

struct fox_editor *editor_init(char *filename, unsigned long buffer_size)
{
  struct fox_editor *editor = malloc(sizeof(struct fox_editor));

  editor->filename = malloc(strlen(filename));
  strcpy(editor->filename, filename);

  editor->buffer_size = buffer_size;
  editor->selected_byte = 0;
  editor->scrolled = 0;

  if (editor->filename != 0)
  {
    read_file(filename, &editor->buffer, &editor->buffer_size);
  }
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

void editor_render(struct fox_editor *editor, struct fox_ui *ui)
{
}