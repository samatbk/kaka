#ifndef __INPUT_H__
#define __INPUT_H__

typedef enum {
  NONE,
  KEY_EVENT,
  MOUSE_EVENT
} EventType;

typedef enum {
  ED_KEY_Q,
} Key;

typedef int KeyCode;
typedef struct {
  EventType type;
  KeyCode keycode;
} Event; 

#endif
