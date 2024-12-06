#ifndef __EDITOR_H__
#define __EDITOR_H__

#include "gap_buffer.h"
#include "renderer.h"

typedef struct {
  unsigned int cursor_x;
  unsigned int cursor_y;

  unsigned int current_line;

  unsigned int width;
  unsigned int height;

  Renderer *renderer;

  GapBuffer *buffer;
} Editor;

void editor_init(Editor *editor, Renderer *renderer, unsigned int width,
                 unsigned int height);
void editor_render(Editor *editor);
void editor_cleanup(Editor *editor); // TODO: Implement

#endif
