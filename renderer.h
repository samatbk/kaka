#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "input.h"

typedef struct {
	void (*init)(unsigned int width, unsigned int height, char* title);
	void (*draw_text)(const char* text, int x, int y, unsigned int font_size);
	void (*present)(void);
	void (*clear)(void);
    void (*shutdown)(void);
    void (*poll_events)(void);
    void (*register_event_callback)(void* context, void (*cb)(void* context, Event event));
} Renderer;

#endif
