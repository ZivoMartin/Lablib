#include "../include/settings.h"


void lablib_kpress(Lablib* lablib, char c) {
  for(int i=0; i<lablib_nb_button(lablib); i++) {
    Input* inp = button_get_input(lablib_get_button(lablib, i));
    if (input_is_active(inp)) {
      input_new_char(inp, c);
    }
  }
}

void lablib_mouse_move(Lablib* lablib, SDL_Point mp) {
  button_move_cursor(lablib_get_active_cursor(lablib), mp);
}

void lablib_click_release(Lablib* lablib) {
  button_desactivate_cursor(lablib_get_active_cursor(lablib));
}

Lablib* lablib_init(SDL_Window *win, SDL_Renderer *ren, int nb_scene) {
	Lablib *lablib = malloc(sizeof(struct Lablib_t));
	SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
	lablib->ren = ren;
	lablib->win = win;
	TTF_Init();
	lablib->font = cp(TTF_OpenFont(FONT, FONTSIZE));
	TTF_SetFontStyle(lablib->font, TTF_STYLE_NORMAL);
	lablib->nb_scene = nb_scene;
	lablib->scene_arr = malloc(sizeof(Scene*)*nb_scene);
	return lablib;
}

void lablib_new_click(Lablib* lablib) {
  int n = lablib_nb_button(lablib);
  for(int i=0; i<n; i++) {
      Scene* previous_scene = lablib_get_current_scene(lablib);
      try_to_click(lablib_get_button(lablib, i), lablib_get_last_coordinate(lablib));
      if (previous_scene != lablib_get_current_scene(lablib)) break;  // We stop only if there is a scene change, otherwise we continue to try to click.
  }
}

void lablib_destroy(Lablib* lablib){
	for(SceneIndex i=0; i<lablib_nb_scene(lablib); i++) {
		destroy_scene(lablib_get_scene(lablib, i));
	}
	free(lablib->scene_arr);
	free(lablib);
}

TTF_Font* lablib_get_font(Lablib* lablib) {
	return lablib->font;
}

SDL_Window* lab_lib_win(Lablib* lablib) {
	return lablib->win;
}

SDL_Renderer* lablib_ren(Lablib* lablib) {
	return lablib->ren;
}

SDL_Point lablib_get_last_coordinate(Lablib* lablib) {
	SDL_Point res = {lablib->last_x, lablib->last_y};
	return res;
}

void set_last_coordinate(Lablib* lablib, SDL_Point mouse) {
	lablib->last_x = mouse.x;
	lablib->last_y = mouse.y;
}

// Check if the given scene index is valid
void lablib_check_scene(Lablib* lablib, SceneIndex i) {
	if (i == lablib_nb_scene(lablib)) {
    fprintf(stderr, "Scene index out of range\n");
    exit(EXIT_FAILURE);
  }
}

void change_scene(Lablib* lablib, SceneIndex new_scene) {
  lablib_check_scene(lablib, new_scene);
  lablib->current_scene = new_scene;
}

Scene* lablib_get_scene(Lablib* lablib, SceneIndex i) {
  lablib_check_scene(lablib, i);
  return lablib->scene_arr[i];
}

SceneIndex lablib_get_scene_index(Lablib* lablib)  {
  return lablib->current_scene;
}

Scene* lablib_get_current_scene(Lablib* lablib) {
  return lablib->scene_arr[lablib_get_scene_index(lablib)];
}


int lablib_w_height(Lablib* lablib) {
  return lablib->h;
}

int lablib_w_width(Lablib* lablib) {
  return lablib->w;
}

Button* lablib_get_button(Lablib* lablib, int index) {
  return scene_get_button(lablib_get_current_scene(lablib), index);
}

Button* lablib_get_active_input(Lablib* lablib) {
  for(int i = 0; i<lablib_nb_button(lablib); i++) {
    Button* b = lablib_get_button(lablib, i);
    if (input_is_active(button_get_input(b))) return b;
  }
  return NULL;
}

Button* lablib_get_active_cursor(Lablib* lablib) {
  for(int i = 0; i<lablib_nb_button(lablib); i++) {
    Button* b = lablib_get_button(lablib, i);
    if (cursor_is_active(button_get_cursor(b))) return b;
  }
  return NULL;
}

void activate_input(Lablib* lablib) {
  Button* b = lablib_get_active_input(lablib);
  if(b) {
    Input* inp = button_get_input(b);
    input_set_activity(inp, false);
    (*inp->action)(b);
  }
}

int lablib_nb_button(Lablib* lablib) {
  return scene_nb_buttons(lablib_get_current_scene(lablib));
}


void* cp(void* p) {
  if (!p) {
    exit(1);
  }
  return p;
}


SDL_Color create_color(int r, int g, int b, int a) {
  return (SDL_Color) {r, g, b, a};
}


SDL_Rect init_rect(int x, int y, int w){
  return (SDL_Rect){.h = w-1, .w = w-1, .x = x, .y = y};
}



void display_current_scene(Lablib* lablib){
  SDL_RenderCopy(lablib_ren(lablib), scene_get_background(lablib_get_current_scene(lablib)), NULL, NULL);
}


void display_scenes(Lablib* lablib) {
  display_current_scene(lablib);
  for(int i = 0; i<lablib_nb_button(lablib); i++) 
      display_button(lablib_get_button(lablib, i));  
}


void lablib_render(Lablib *lablib) {
  SDL_GetWindowSize(lablib_win(lablib), &lablib->w, &lablib->h);
  display_scenes(lablib);
}


void lablib_process(Lablib *lablib, SDL_Event *e) {
	int w, h;
	SDL_GetWindowSize(lablib_win(lablib) , &w, &h);
	if (e->type == SDL_MOUSEBUTTONUP) 
		lablib_click_release(lablib);
	else if (e->type == SDL_MOUSEMOTION){
		SDL_Point mouse;
		SDL_GetMouseState(&mouse.x, &mouse.y);
		lablib_mouse_move(lablib, mouse);
	}else if (e->type == SDL_TEXTINPUT) 
		lablib_kpress(lablib, e->text.text[0]);
	else if (e->type == SDL_MOUSEBUTTONDOWN) {
		SDL_Point mouse;
		SDL_GetMouseState(&mouse.x, &mouse.y);
		set_last_coordinate(lablib, mouse);
		lablib_new_click(lablib);
	} else if (e->type == SDL_KEYDOWN) {
		switch (e->key.keysym.sym) {
		case SDLK_RETURN:
			lablib_activate_input(lablib);
			break;
		case SDLK_BACKSPACE:
			input_delete_char(button_get_input(lablib_get_active_input(lablib)));
			break;
		}
	}

}
