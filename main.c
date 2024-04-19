#include "include/lablib.h"
#include "include/button.h"
#include "include/scene.h"
#include <SDL2/SDL.h>

void print_hello(Button* b) {
	printf("Hello, World !\n");
}

int main() {
	SDL_Window* win;
	SDL_Renderer* ren;
	SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_RESIZABLE, &win, &ren);
	Lablib* lablib = lablib_init(win, ren, 1);
	Scene* scene = create_scene(lablib, 2);
	scene_add_button(scene, 0.2, 0.2, 0.2, 0.2, "test", false, print_hello);
	scene_add_button(scene, 0.8, 0.2, 0.2, 0.2, "test2", false, NULL);
	SDL_Event e;
	bool running = 1;
	while (running) {
		while (Lablib_PollEvent(lablib, &e)) if (e.type == SDL_QUIT) running = 0;
		SDL_SetRenderDrawColor(ren, 0, 0, 0, 0xFF);
        SDL_RenderClear(ren);
		lablib_render(lablib);
		SDL_RenderPresent(ren);
        SDL_Delay(15);
	}
}

