#include "../include/settings.h"

#define CLOCK_LIMIT 14
#define INPUT_DISPLAY_CURSOR CLOCK_LIMIT/2

Input* create_input(Button* b, char* placeholder) {
    Input* res = cp(malloc(sizeof(Input)));
    res->b = b;
    res->nb_char = 0;
    res->is_active = false;
    if (strcmp(placeholder, "") == 0) placeholder = " ";
    res->placeholder = placeholder;
    res->placeholder_color = lablib_create_color(DEFAULT_PLACEHOLDER_COLOR, PLACEHOLDER_OPPACITY);
    res->clock = 0;
    for(int i = 0; i<INPUT_MAX_LEN-1; i++) {
        res->text[i] = ' ';
    }
    res->text[INPUT_MAX_LEN-1] = '\0';
    return res;
}

bool input_is_active(Input* inp) {
    return inp && inp->is_active;
}

void input_set_activity(Input* inp, bool act) {
    if(inp) inp->is_active = act;
}

Lablib* input_lablib(Input* inp) {
    if (!inp) return NULL;
    return button_lablib(input_get_button(inp));
}

Button* input_get_button(Input* inp) {
    if (!inp) return NULL;
    return inp->b;
}

char* input_get_text(Input* inp) {
    if (!inp) return "";
    return inp->text;
}

void incr_number_char(Input* inp, int x) {
    if (inp) inp->nb_char += x;
}

int input_get_nb_char(Input* inp) {
    if (!inp) return 0;
    return inp->nb_char;
}

void reset_txt(Input* inp) {
    if (!inp) return;
    int nb_char = input_get_nb_char(inp);
    for(int i = 0; i<=  nb_char; i++) {
        input_get_text(inp)[i] = ' ';
    }
    inp->nb_char = 0;
    input_actualise_texture(inp);
}

void destroy_input(Input* inp, bool dest_button) {
    if (!inp) return;
    if (dest_button) destroy_button(input_get_button(inp));
    free(inp);
}

void input_new_char(Input* inp, char c) {
    if (!inp) return;
        int nb_char = input_get_nb_char(inp);
        if (nb_char < INPUT_MAX_LEN-1) {
            input_get_text(inp)[input_get_nb_char(inp)] = c;
            incr_number_char(inp, 1);
        }
        input_actualise_texture(inp);
}

void input_delete_char(Input* inp){
    if (!inp) return;
    int nb_char = input_get_nb_char(inp);
    if (nb_char > 0) {
        input_get_text(inp)[input_get_nb_char(inp)] = ' ';
        input_get_text(inp)[input_get_nb_char(inp)-1] = ' ';
        incr_number_char(inp, -1);
    }
    input_actualise_texture(inp);
}

char* input_get_placeholder(Input* inp) {
    return inp->placeholder;
}

SDL_Color input_get_paceholder_color(Input* inp) {
    return inp->placeholder_color;
}


void input_change_placeholder(Input* inp, char *new_txt) {
    input_change_placeholder_color(inp, lablib_create_color(DEFAULT_PLACEHOLDER_COLOR, PLACEHOLDER_OPPACITY));
    inp->placeholder = new_txt;
}

void input_change_placeholder_color(Input* inp, SDL_Color new_c) {
    inp->placeholder_color = new_c;
}

void input_actualise_texture(Input* inp) {
    if (!inp) return;
    char *txt = input_get_text(inp);
    Lablib* lablib = input_lablib(inp);
    SDL_Renderer* ren = lablib_get_ren(lablib);
    Button* button = input_get_button(inp);
    SDL_Color txt_color = lablib_create_color(BLACK_TEXT_COLOR, DEFAULT_TEXT_OPPACITY);
    if (!input_is_active(inp) && input_get_nb_char(inp) == 0) {
        txt = input_get_placeholder(inp);
        txt_color = input_get_paceholder_color(inp);
    }
    SDL_Surface* surf = TTF_RenderText_Blended(lablib_get_font(lablib), txt, txt_color);  
    SDL_Texture* new_texture = SDL_CreateTextureFromSurface(ren, surf);
    SDL_FreeSurface(surf);
    button_change_texture(button, new_texture);
}

int input_clock(Input* inp) {
    return inp->clock;
}

void input_inc_clock(Input* inp) {
    if (input_clock(inp) == CLOCK_LIMIT) inp->clock = 0;
    else inp->clock += 1;
}

void display_input(Input* inp) {
    if (!inp) return;
    if (input_is_active(inp) && input_clock(inp) > INPUT_DISPLAY_CURSOR) {
        input_get_text(inp)[input_get_nb_char(inp)] = '|';
    }else{
        input_get_text(inp)[input_get_nb_char(inp)] = ' ';
    }
    input_actualise_texture(inp);
    input_inc_clock(inp);
}

void input_set_placeholder_error(Input* inp, char* err) {
    input_change_placeholder(inp, err);
    input_change_placeholder_color(inp, lablib_create_color(PLACEHOLDER_ERROR_COLOR, PLACEHOLDER_OPPACITY));
}
