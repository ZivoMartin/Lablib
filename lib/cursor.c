#include "../include/settings.h"
#define FIRST_MOVE -1

Cursor* create_cursor(Button* b, float rh, void (*move_cursor_action)(Button* b), 
                                           void (*release_cursor_action)(Button* b)) {
    Cursor* res = malloc(sizeof(Cursor));
    res->b = b;
    res->rh = rh;
    res->rx = button_rx(b) + CURSOR_WIDTH/4;
    res->ry = button_ry(b) - rh/2;
    res->is_active = false;
    res->move_cursor_action = move_cursor_action;
    res->release_cursor_action = release_cursor_action;
    return res;
}


void cursor_set_last_h(Cursor* cur, int last_h) {
    cur->last_h = last_h;
}

int cursor_last_h(Cursor* cur) {
    return cur->last_h;
}

void destroy_cursor(Cursor* cur) {
    if (!cur) return;
    SDL_DestroyTexture(cursor_get_texture(cur));
    free(cur);
}

void cursor_set_height(Cursor* cur, int new_h) {
    cur->h = new_h;
}

void cursor_set_width(Cursor* cur, int new_w) {
    cur->w = new_w; 
}

float cursor_rheight(Cursor* cur) {
    return cur->rh;
}

int cursor_width(Cursor* cur) {
    return cur->w;
}

int cursor_height(Cursor* cur) {
    return cur->h;
}

float cursor_rx(Cursor* cur) {
    return cur->rx;
}

float cursor_ry(Cursor* cur) {
    return cur->ry;
}

Button* cursor_button(Cursor* cur) {
    return cur->b;
}

Lablib* cursor_lablib(Cursor* cur) {
    return button_lablib(cursor_button(cur));
}

#define MINIMAL_WIDTH 0.007

void display_cursor(Cursor* cur) {
    if (!cur) return;
    Lablib* lablib = cursor_lablib(cur);
    cursor_set_height(cur, lablib_w_height(lablib)*cursor_rheight(cur));
    cursor_set_width(cur,  lablib_w_width(lablib) *MINIMAL_WIDTH); 
    SDL_SetRenderDrawColor(lablib_get_ren(lablib), CURSOR_DEFAULT_COLOR, DEFAULT_OPPACITY);
    SDL_Rect r = (SDL_Rect){.h = cursor_height(cur)+button_height(cursor_button(cur))/2, .w = cursor_width(cur), .x = lablib_w_width(lablib)*cursor_rx(cur), .y = lablib_w_height(lablib)*cursor_ry(cur)};
    SDL_RenderFillRect(lablib_get_ren(lablib), &r);
    SDL_RenderDrawRect(lablib_get_ren(lablib), &r);  
    SDL_RenderCopy(lablib_get_ren(lablib), NULL, NULL, &r);
}

bool cursor_is_active(Cursor* cur) {
    return cur && cur->is_active;
}

void cursor_change_activity(Cursor* cur, bool act) {
    if (!act && cur->release_cursor_action) (*cur->release_cursor_action)(cursor_button(cur));
    cursor_set_last_h(cur, FIRST_MOVE);
    cur->is_active = act;
}

#define CURSOR_DECALL 0.0006

void cursor_move(Cursor* cur, SDL_Point pt) {
    Button* b = cursor_button(cur);
    float new_ratio = button_ry(b)+CURSOR_DECALL*(pt.y-cursor_last_h(cur));
    if (cursor_last_h(cur) != -1 && new_ratio > cursor_ry(cur) && new_ratio < (cursor_ry(cur)+cursor_rheight(cur)))
        button_set_ry(b, new_ratio);
    cursor_set_last_h(cur, pt.y);
    if (cur->move_cursor_action) (*cur->move_cursor_action)(b);
}

float cursor_value(Cursor* cur){
    Button* b = cursor_button(cur);
    int h = lablib_w_height(button_lablib(b));
    return (button_ry(b)*h - cursor_ry(cur)*h) / (cursor_rheight(cur)*h) ;    
}
