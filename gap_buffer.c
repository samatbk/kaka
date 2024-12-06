#include "gap_buffer.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

GapBuffer *gapbuffer_init(unsigned int size) {
  GapBuffer *buffer = (GapBuffer *)malloc(sizeof(GapBuffer));
  assert(buffer != NULL);

  buffer->size = size;
  buffer->gap_start = 0;
  buffer->gap_end = size - 1;
  buffer->content = malloc(sizeof(char) * size);
  assert(buffer->content != NULL);

  return buffer;
}

void gapbuffer_left(GapBuffer *buffer) {
  if (buffer->gap_start == 0)
    return;

  buffer->gap_start--;
  buffer->content[buffer->gap_end] = buffer->content[buffer->gap_start];
  buffer->gap_end--;
}

void gapbuffer_right(GapBuffer *buffer) {
  if (buffer->gap_end == buffer->size - 1)
    return;

  buffer->content[buffer->gap_start] = buffer->content[buffer->gap_end + 1];
  buffer->gap_start++;
  buffer->gap_end++;
}

void gapbuffer_grow(GapBuffer *buffer) {
  unsigned int new_size = buffer->size * 2;
  char *new_content = (char *)malloc(sizeof(char) * new_size);
  assert(new_content != NULL);

  memcpy(new_content, buffer->content, buffer->gap_start);

  unsigned int new_gap_end = new_size - (buffer->size - buffer->gap_end);
  memcpy(new_content + new_gap_end + 1, buffer->content + buffer->gap_end + 1,
         buffer->size - buffer->gap_end - 1);

  buffer->gap_end = new_gap_end;
  free(buffer->content);
  buffer->content = new_content;
  buffer->size = new_size;
}

void gapbuffer_move_cursor(GapBuffer *buffer, int position) {
  if (position < 0 || position > buffer->size)
    return;

  while (position < buffer->gap_start) {
    gapbuffer_left(buffer);
  }
  while (position > buffer->gap_start) {
    gapbuffer_right(buffer);
  }
}

void gapbuffer_insert(GapBuffer *buffer, char ch, int position) {
  if (buffer->gap_start == buffer->gap_end) {
    gapbuffer_grow(buffer);
  }

  gapbuffer_move_cursor(buffer, position);

  buffer->content[buffer->gap_start] = ch;
  buffer->gap_start++;
}

void gapbuffer_delete(GapBuffer *buffer, int position) {
  if (position < 0 || position >= buffer->size)
    return;

  gapbuffer_move_cursor(buffer, position);

  if (buffer->gap_start > 0) {
    buffer->gap_start--;
  }
}

void gapbuffer_cleanup(GapBuffer *buffer) {
  free(buffer->content);
  free(buffer);
}
