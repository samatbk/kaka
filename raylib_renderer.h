#ifndef __RAYLIB_RENDERER_H__
#define __RAYLIB_RENDERER_H__

#include <stdlib.h>
#include <raylib.h>

#include "input.h"
#include "renderer.h"

static void (*event_callback)(void* context, Event event) = NULL;
static void* callback_context = NULL;

static void raylib_init(unsigned int width, unsigned int height, char* title) {
	InitWindow(width, height, title);
}

static void raylib_draw_text(const char *text, int x, int y, unsigned int font_size) {
	DrawText(text, x, y, font_size, RAYWHITE);
}

static void raylib_clear(void) {
	BeginDrawing();
	ClearBackground(BLACK);
}

static void raylib_present(void) {
	EndDrawing();
}

static void raylib_shutdown(void) { CloseWindow(); }

static void raylib_register_event_callback(void* context, void (*cb)(void* context, Event event)) {
  event_callback = cb;
  callback_context = context;
}

static void raylib_poll_events(void) {
  int ch = 0;
  Event event;
  while ((ch = GetCharPressed()) != 0) {
    event.type = KEY_EVENT;
    event.keycode = ch;
	event_callback(callback_context, event);
  }          
}        

Renderer* create_raylib_renderer(void) {
	Renderer* renderer = (Renderer*) malloc(sizeof(Renderer));
	
	if (!renderer) {
		return NULL;
	}
	
	renderer->init = raylib_init;
	renderer->draw_text = raylib_draw_text;
	renderer->clear = raylib_clear;
	renderer->present = raylib_present;
	renderer->shutdown = raylib_shutdown;
    renderer->register_event_callback = raylib_register_event_callback;
	renderer->poll_events = raylib_poll_events;
	return renderer;
}

#endif
