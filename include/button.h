#ifndef BUTTON_SAFE
#define BUTTON_SAFE

#include "struct.h"


/**
 * @brief Allocate a button and return it.
 * @param lablib The lablib
 * @param rx The x position of the button relative to the window width from the left
 * @param ry The y position of the button relative to the window height from the top
 * @param rw The button width relative to the width of the window
 * @param rw The button height relative to the height of the window
 * @param text The text inside of the button (if is_path is false), and the image path otherwise
 * @param is_path boolean precising if the text is an image path or just simply the text to be put in the button
 * @param act A pointer to a function to be activated with each click
 * @details The field display is by default set as default_display_button, use button_set_display to change it.
 * @details The default text in an empty case is a single space.
 * @return the button.
 */
Button* create_button(Lablib* lablib, float x, float y, float rw, float rh, const char* text, bool is_path, void (*act)(Button* b));

/**
 * @brief Change the display method of the button.
 * @param b The button
 * @param dis the new display function of the button
 */
void set_display(Button* b, void (*dis)(Button* b));


/**
 * @brief Free the entire button.
 * @param b The button
 */
void destroy_button(Button* b);


/**
 * @brief Set the height of the button.
 * @param b The button
 * @param h The new height
 */
void button_set_height(Button* b, int h);


/**
 * @brief Set the width of the button.
 * @param b The button
 * @param h The new width
 */
void button_set_width(Button* b, int w);

/**
 * @brief get the texture.
 * @param b The button
 * @return The texture of the button
 */
SDL_Texture* button_get_texture(Button* b);

/**
 * @brief get the lablib.
 * @param b The button
 * @return The lablib of the button
 */
Lablib* button_lablib(Button* b);


/**
 * @brief get the width of the window using the lablib inside of the button.
 * @param b The button
 * @return The width of the window
 */
int button_get_win_w(Button* b);

/**
 * @brief get the height of the window using the lablib inside of the button.
 * @param b The button
 * @return The height of the window
 */
int button_get_win_h(Button* b);


/**
 * @brief Return the relative x position of the button
 * 
 * @param b 
 * @return float 
 */
float button_rx(Button* b);


/**
 * @brief Return the relative y position of the button
 * 
 * @param b 
 * @return float 
 */
float button_ry(Button* b);

/**
 * @brief Return the relative width of the button
 * 
 * @param b 
 * @return float 
 */
float button_rwidth(Button* b);


/**
 * @brief Return the relative height position of the button
 * 
 * @param b 
 * @return float 
 */
float button_rheight(Button* b);


/**
 * @brief get the width of the button.
 * @param b The button
 * @return The width of the button
 */
int button_width(Button* b);

/**
 * @brief get the height of the button.
 * @param b The button
 * @return The height of the button
 */
int button_height(Button* b);

/**
 * @brief get the color of the button.
 * @param b The button
 * @return The color of the button
 */
SDL_Color* button_color(Button* b);

/**
 * @brief Set the button as an input.
 * @param b The button
 * @param inp The input 
 */
void make_as_input(Button* b, Input* inp);

/**
 * @brief get the input of the button.
 * @param b The button
 * @details if the button isn't an input the function return NULL
 * @return The input of the button
 */
Input* button_get_input(Button* b);

/**
 * @brief Indicate if the button is an input
 * @param b The button
 * @return true if the button is an input false otherwase
 */
bool is_input(Button* b);

/**
 * @brief Change properly the texture of the button (free the old one)
 * @param b The button
 * @param new_texture The new texture
 */
void button_change_texture(Button* b, SDL_Texture* new_texture);

void compute_button_decal(Button* b, int* decalWidth, int* decalHeight);

Lablib* button_get_lablib(Button* b);

void destroy_button(Button* b);

/**
 * @brief If the coordinates of c are inside the button, call the activate function of the button and return true, otherwise return false
 * @param b The button
 * @param c The coordonate of the click
 * @return True if its a click on the given button otherwise false
 */
bool try_to_click(Button* b, SDL_Point c);

/**
 * @brief call the display function in the button with the given button in parameter.
 * @param b The button
 */
void display_button(Button* b);


/**
 * @brief Changes the color of a give button
 * @param b The button to be changed
 * @param c The new color to be set
*/
void button_change_color(Button* b, SDL_Color c);


/**
 * @brief Changes the text color inside the button
 * @param b The button to be changed
 * @param c The new color to be set
*/
void button_change_textColor(Button* b, SDL_Color c);

/**
 * @brief Return the current text of the button
 * 
 * @param b 
 * @return char* 
 */
const char* button_get_text(Button* b);

/**
 * @brief Default function for displaying a button, simply displays the rect with the right size and position it on the screen.
 * @param b The button
 */
void default_display_button(Button* b);

/**
 * @brief Set the input inside the button as active
 * 
 * @param b The button
 * @details Do nothing if the button isn't an input
 */
void button_set_inp_active(Button* b);

/**
 * @brief Change the relative width of the button
 * 
 * @param b 
 * @param rw 
 */
void button_set_rw(Button* b, float rw);


/**
 * @brief Change the relative height of the button
 * 
 * @param b 
 * @param rh 
 */
void button_set_rh(Button* b, float rh);

/**
 * @brief Return the cursor part of the button
 * 
 * @param b 
 * @return Cursor* 
 */
Cursor* button_get_cursor(Button* b);

void button_desactivate_cursor(Button* b);

void button_move_cursor(Button* b, SDL_Point pt);

void button_set_cursor_active(Button* b);


void make_as_cursor(Button* b, float rh, void (*move_cursor_action)(Button* b), void (*release_cursor_action)(Button* b));


void button_set_ry(Button* b, float new_ry);
#endif 
