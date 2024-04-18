#ifndef SAFE_INPUT
#define SAFE_INPUT

#include "struct.h"

#define PLACEHOLDER_OPPACITY 50
#define DEFAULT_PLACEHOLDER_COLOR 0, 0, 0
#define PLACEHOLDER_ERROR_COLOR 255, 20, 20

/**
 * @brief Alloc a new input
 * @param b The button associate with the input
 * @return The input
 */
Input* create_input(Button* b, char* placeholder);


/**
 * @brief Destroy the entire input
 * @param inp The input
 * @param dest_button Indicate if we have to destroy the button too
 */
void destroy_input(Input* inp, bool dest_button);

/**
 * @brief add a char at the end of the input and incr the number of char
 * @param inp The input
 * @param c The new char
 * @details Do nothing if the input is null
 */
void input_new_char(Input* inp, char c);

/**
 * @brief Delete the last char of the input and decrement the number of char
 * @param inp The input
 * @details Do nothing if the input is null
 */
void input_delete_char(Input* inp);


/**
 * @brief Indicate if the input is active, i.e if press a keyword can change his content
 * @param inp The input
 * @details Return false if the input is null
 * @return true if the input is active otherwise false
 */
bool input_is_active(Input* inp);

/**
 * @brief Get the current number of char in the input 
 * @param inp The input
 * @details Return 0 if the input is null
 * @return The current number of char in the input
 */
int get_nb_char(Input* inp);

/**
 * @brief Get the current text in the input 
 * @param inp The input
 * @details Return a single space if the input is null
 * @return The current text in the input
 */
char* input_get_text(Input* inp);


/**
 * @brief increment the number of characters by x
 * @param inp The input
 * @details Do nothing if the input is null
 * @details x can be negative
 */
void char_nb_char(Input* inp, int x);

/**
 * @brief Set the current text as empty and the number of char as 0 
 * @param inp The input
 * @details Do nothing of the input is null
 */
void reset_txt(Input* inp);

/**
 * @brief Actualise the text of the texture after a text changement 
 * @param inp The input
 * @details If the text is empty or the input is null set the current text as a single space
 */
void input_actualise_texture(Input* inp);

/**
 * @brief Get the lablib of the input 
 * @param inp The input
 * @details Return null if the input is null
 * @return The lablib of the input
 */
Lablib* input_lablib(Input* inp);

/**
 * @brief Get the button of the input 
 * @param inp The input
 * @details Return null if the button is null
 * @return The button of the input
 */
Button* input_get_button(Input* inp);

/**
 * @brief Set the activity of the input
 * 
 * @param inp The input
 * @details Do nothing if input is null
 */
void input_set_activity(Input* inp, bool act) ;

/**
 * @brief Get the placeholder text of the input
 * 
 * @param inp The inp
 * @return char* The placeholder text
 */
char* input_get_placeholder(Input* inp);


/**
 * @brief Get the placeholder color
 * 
 * @param inp The inp 
 * @return The placeholder color
 */
SDL_Color input_get_paceholder_color(Input* inp);

/**
 * @brief Change the placeholder text
 * 
 * @param inp The inp
 * @param new_txt The new txt
 */
void input_change_placeholder(Input* inp, char *new_txt);

/**
 * @brief Change the placeholder color
 * 
 * @param inp The inp
 * @param new_c The new color
 */
void input_change_placeholder_color(Input* inp, SDL_Color new_c);

/**
 * @brief This function display the input itself, 
 * @details If the input is null it do nothing.
 */
void display_input(Input* inp);


/**
 * @brief Get the input clock
 * 
 * @param inp 
 * @return int 
 */
int input_clock(Input* inp); 


/**
 * @brief Increment the input clock and reset it if its superior than the clock limit
 * 
 * @param inp 
 */
void input_inc_clock(Input* inp);


/**
 * @brief Display the input
 * 
 * @param inp 
 */
void display_input(Input* inp);


/**
 * @brief Simply change the placeholder and his color with an error color
 * @param err error msg
 */
void input_set_placeholder_error(Input* inp, char* err);

#endif
