#include "include/lablib.h"
#include <SDL2/SDL.h>

int main() {
	printf("Hello, World !\n");
	SDL_Window* win;
	SDL_Renderer* ren;
	SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_RESIZABLE, &win, &ren);
	Lablib* lablib = lablib_init(win, ren, 0);
	while(1) {
		
	}
}
