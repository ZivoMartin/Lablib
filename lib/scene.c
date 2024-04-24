#include "../include/settings.h"
#include "assert.h"

Scene* create_scene(Lablib* lablib, int nb_button) {
    Scene* res = cp(malloc(sizeof(Scene)));
	res->lablib = lablib;
	res->buttons = malloc(sizeof(Button*)*nb_button);
    res->nb_buttons = nb_button;
    res->background = NULL;
	res->current_nb_button = 0;
	res->id = lablib_add_scene(lablib, res);
    return res;
}

SceneI scene_id(Scene* scene) {
	return scene->id;
}

int scene_current_nb_button(Scene* scene) {
	return scene->current_nb_button;
}

Button* scene_add_button(Scene* scene, float rx, float ry, float rw, float rh, const char* path, void(*act)(Button* b)) {
	if (scene_current_nb_button(scene) == scene_nb_buttons(scene)) {
		fprintf(stderr, "To much button for a scene.");
		exit(1);
	}
	Button* b = create_button(scene->lablib, rx, ry, rw, rh, path, act);
	scene->buttons[scene_current_nb_button(scene)] = b;
	scene->current_nb_button += 1;
	return b;
}


int scene_nb_buttons(Scene* scene) {
    return scene->nb_buttons;
}

void set_scene_background(Lablib* lablib, Scene* scene, const char* path){
    SDL_Surface* image = cp(IMG_Load(path));
    assert(image);
    SDL_Texture* textSurf = cp(SDL_CreateTextureFromSurface(lablib_get_ren(lablib), image));
    assert(textSurf);
    scene->background = textSurf;
    SDL_FreeSurface(image);
}

SDL_Texture* scene_get_background(Scene* scene){
    if (scene != NULL && scene->background != NULL){
        return scene->background;
    }
    return NULL;
}


Button* scene_get_button(Scene* scene, int i) {
    if (i >= scene_nb_buttons(scene)) {
        fprintf(stderr, "button index out of range, %d buttons in this scene but the index is %d\n", scene_nb_buttons(scene), i);
        exit(1);
    }
    return scene->buttons[i];
}


void destroy_scene(Scene* scene) {
    for(int i=0; i<scene_nb_buttons(scene); i++) {
        destroy_button(scene_get_button(scene, i));
    }
    SDL_DestroyTexture(scene->background);
    free(scene->buttons);
    free(scene);
}
