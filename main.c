#include "editor.h"
#include "renderer.h"
#include "raylib_renderer.h"

#define WIDTH 800
#define HEIGHT 600

int main(void) {
	Editor *editor = malloc(sizeof(Editor));		
	Renderer *renderer = create_raylib_renderer();

	editor_init(editor, renderer, WIDTH, HEIGHT);

	while(1) {
		editor_render(editor);	
	}

	editor_cleanup(editor);
	free(renderer);
	free(editor);
	return 0;
}
