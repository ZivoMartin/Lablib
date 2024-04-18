#include "../include/settings.h"
#include "assert.h"

Scene* create_scene(Button** buttons, int nb_buttons) {
    Scene* res = cp(malloc(sizeof(Scene)));
    res->buttons = buttons;
    res->nb_buttons = nb_buttons;
    res->background = NULL;
    return res;
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
