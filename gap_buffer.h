#ifndef __GAP_BUFFER_H__
#define __GAP_BUFFER_H__

typedef struct {
  char *content;
  int gap_start;
  int gap_end;
  unsigned int size;

} GapBuffer;

GapBuffer* gapbuffer_init(unsigned int size);

void gapbuffer_left(GapBuffer *buffer);
void gapbuffer_right(GapBuffer *buffer);

void gapbuffer_grow(GapBuffer *buffer);

void gapbuffer_insert(GapBuffer *buffer, char ch, int position);
void gapbuffer_delete(GapBuffer *buffer, int position);

void gapbuffer_move_cursor(GapBuffer *buffer, int position);

void gapbuffer_cleanup(GapBuffer *buffer);
#endif
