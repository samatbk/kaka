#include <stdlib.h>

#include "editor.h"
#include "gap_buffer.h"
#include "input.h"

void editor_on_event(Editor *editor, Event event) {
  if (event.keycode == 'q') {
	exit(0);
  } else if (event.keycode == 'h') {
	if (editor->cursor_x > 0) {
            gapbuffer_delete(editor->buffer, editor->cursor_x - 1);
            editor->cursor_x--;
    }
  } else {
	if (editor->cursor_x > editor->buffer->size - 1) {
            editor->cursor_x = editor->buffer->size - 1;
    }

    gapbuffer_insert(editor->buffer, event.keycode, editor->cursor_x);
    editor->cursor_x++;
  }        
}

void editor_init(Editor *editor, Renderer *renderer, unsigned int width, unsigned int height) {
	editor->renderer = renderer;

	editor->width = width;
	editor->height = height;
	
	editor->current_line = 0;
	editor->cursor_x = 0;
	editor->cursor_y = 0;

	editor->buffer = gapbuffer_init(20);

    renderer->init(width, height, "kaka");

	renderer->register_event_callback(editor, editor_on_event);
}

void editor_render(Editor *editor) {
	editor->renderer->clear();	
    editor->renderer->poll_events();

	unsigned int cursor_x = 0;
    for (unsigned int i = 0; i < editor->buffer->size; i++) {
        // Skip gap region
        if (i >= editor->buffer->gap_start && i <= editor->buffer->gap_end) {
            continue;
        }

		// FIX: More efficient rendering
        char ch = editor->buffer->content[i];
        if (ch != ' ') { // Avoid rendering spaces
            char text[2] = {ch, '\0'};
            editor->renderer->draw_text(text, cursor_x * 12, 10, 20);
        }
        cursor_x++;
    }
    editor->renderer->present();

}

void editor_cleanup(Editor *editor) {
	if (editor->renderer) {
		editor->renderer->shutdown();
    }

    free(editor->renderer);
	gapbuffer_cleanup(editor->buffer);
}
