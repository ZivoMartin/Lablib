#include "../include/settings.h"

Button* create_button(Lablib* lablib, float rx, float ry, float rw, float rh, char* text, bool is_path, 
                      void (*act)(Button* b)) {
    Button* res = malloc(sizeof(Button));
    res->color = lablib_create_color(DEFAULT_COLOR_BG_BUTTON, DEFAULT_BUTTON_OPPACITY);
    res->lablib = lablib;
    res->rx = rx;
    res->ry = ry;
    res->rw = rw;
    res->rh = rh;
    res->display = default_display_button;
    res->action = act;
    res->input = NULL;
    res->cur = NULL;
    SDL_Surface* surf;
    res->text = text;
    if (strcmp(text,"") == 0) text = EMPTY_TEXT;
    if(!is_path){
        surf = TTF_RenderText_Blended(lablib_get_font(lablib), text, lablib_create_color(WHITE_TEXT_COLOR, DEFAULT_TEXT_OPPACITY));  
    } else {
        res->color.a = NO_OPACITY;
        surf = cp(IMG_Load(text));
    }
    res->texture = SDL_CreateTextureFromSurface(lablib_get_ren(lablib), surf);
    SDL_FreeSurface(surf);
    return res;
}

void set_display(Button* b, void (*dis)(Button* b)) {
    b->display = dis;
}

void make_as_input(Button* b, Input* inp){
    b->input = inp;
    inp->action = b->action;
    b->action = button_set_inp_active;
    input_actualise_texture(inp);
}

void make_as_cursor(Button* b, float rh, void (*move_cursor_action)(Button* b), 
                                         void (*release_cursor_action)(Button* b)) {
    b->cur = create_cursor(b, rh, move_cursor_action, release_cursor_action);
    SDL_DestroyTexture(b->texture);
    button_change_color(b, lablib_create_color(CURSOR_DEFAULT_COLOR, DEFAULT_OPPACITY));
    b->texture = NULL;
    b->action = button_set_cursor_active;
}

Input* button_get_input(Button* b) {
    if (!b) return NULL;
    return b->input;
}

bool is_input(Button* b) {
    return button_get_input(b);
}


Lablib* button_lablib(Button* b) {
    return b->lablib;
}

SDL_Texture* button_get_texture(Button* b) {
    return b->texture;
}


void destroy_button(Button* b) {
    destroy_input(button_get_input(b), false);
    destroy_cursor(button_get_cursor(b));
    SDL_DestroyTexture(button_get_texture(b));
    free(b);
}

void button_set_height(Button* b, int h) {
    b->h = h;
}

void button_set_width(Button* b, int w) {
    b->w = w;
}

int button_get_win_w(Button* b) {
    return lablib_w_width(button_lablib(b));
}

int button_get_win_h(Button* b) {
    return lablib_w_height(button_lablib(b));
}

void button_set_rw(Button* b, float rw) {
    b->rw = rw; 
}

void button_set_rh(Button* b, float rh) {
    b->rh = rh; 
}

float button_rx(Button* b) {
    return b->rx;
}

float button_ry(Button* b) {
    return b->ry;
}

float button_rwidth(Button* b) {
    return b->rw;
}

float button_rheight(Button* b) {
    return b->rh;
}

int button_width(Button* b) {
    if (is_input(b)) return INPUT_WIDTH;
    return b->w;
}

int button_height(Button* b){
    return b->h;
}

SDL_Color* button_color(Button* b) {
    return &b->color;
}


void compute_button_decal(Button* b, int* decalWidth, int* decalHeight) {
  *decalWidth = button_get_win_w(b)*button_rx(b);
  *decalHeight = button_ry(b) * button_get_win_h(b);
}


bool try_to_click(Button* b, SDL_Point c) {
    input_set_activity(button_get_input(b), false);
    int decalWidth, decalHeight;
    compute_button_decal(b, &decalWidth, &decalHeight);
    if (c.x > decalWidth && c.x < decalWidth+button_width(b) && 
         c.y > decalHeight && c.y < decalHeight + button_height(b)) {
            (*b->action)(b);
            return true;
        }

    return false;
}

void button_change_color(Button* b, SDL_Color c){
    b->color = c;
}


void button_change_textColor(Button* b, SDL_Color c){
    SDL_Surface* surf = TTF_RenderText_Blended(lablib_get_font(button_lablib(b)), button_get_text(b), c);  
    b->texture = SDL_CreateTextureFromSurface(lablib_get_ren(button_lablib(b)), surf);
}

void display_button(Button* b) {
    (*b->display)(b);
}


void button_change_texture(Button* b, SDL_Texture* new_texture) {
    SDL_DestroyTexture(b->texture);
    b->texture = new_texture;
}

void default_display_button(Button* b) {
  Lablib* lablib = button_lablib(b);
  button_set_height(b, lablib_w_height(lablib)*button_rheight(b));
  button_set_width(b,  lablib_w_width(lablib) *button_rwidth(b)); 

  int decalWidth, decalHeight;
  compute_button_decal(b, &decalWidth, &decalHeight);
  SDL_SetRenderDrawColor(lablib_get_ren(lablib), button_color(b)->r, button_color(b)->g, button_color(b)->b, button_color(b)->a);
  SDL_Rect r = (SDL_Rect){.h = button_height(b), .w = button_width(b), .x = decalWidth, .y = decalHeight};
  SDL_RenderFillRect(lablib_get_ren(lablib), &r);
  SDL_RenderDrawRect(lablib_get_ren(lablib), &r);  
  SDL_RenderCopy(lablib_get_ren(lablib), button_get_texture(b), NULL, &r);
  
  display_input(button_get_input(b)); // If the button doesn't have input it do nothing
  display_cursor(button_get_cursor(b));
}

Cursor* button_get_cursor(Button* b) {
    return b->cur;
}

void button_set_inp_active(Button* b) {
    input_set_activity(button_get_input(b), true);
}

void button_set_cursor_active(Button* b) {
    cursor_change_activity(button_get_cursor(b), true);
}

char* button_get_text(Button* b){
    return b->text;
}

void button_desactivate_cursor(Button* b) {
    if (b) cursor_change_activity(button_get_cursor(b), false);
}

void button_move_cursor(Button* b, SDL_Point pt) {
    if (b) cursor_move(button_get_cursor(b), pt);
}

void button_set_ry(Button* b, float new_ry) {
    b->ry = new_ry;
}
