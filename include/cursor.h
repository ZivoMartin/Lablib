#ifndef CURSOR_SAFE
#define CURSOR_SAFE

#include "struct.h"

Cursor* create_cursor(Button* b, float rh,  void (*move_cursor_action)(Button* b), void (*release_cursor_action)(Button* b));

void destroy_cursor(Cursor* cur);

void display_cursor(Cursor* cur);

bool cursor_is_active(Cursor* cur);

void cursor_change_activity(Cursor* cur, bool act);

void cursor_move(Cursor* cur, SDL_Point pt);

SDL_Texture* cursor_get_texture(Cursor* cur);

void cursor_set_height(Cursor* cur, int new_h);

void cursor_set_width(Cursor* cur, int new_w);

float cursor_rheight(Cursor* cur);

int cursor_width(Cursor* cur);

int cursor_height(Cursor* cur);

float cursor_rx(Cursor* cur);

float cursor_ry(Cursor* cur);

Button* cursor_button(Cursor* cur);

Lablib* cursor_lablib(Cursor* cur);

SDL_Texture* cursor_get_texture(Cursor* cur);

void cursor_set_last_h(Cursor* cur, int last_h);


float cursor_value(Cursor* cur);
#endif
