#ifndef SAFE_LABLIB
#define SAFE_LABLIB
#include "struct.h"


/**
 * @brief Render the entire app: display the button, the background and actualise the size of each element 
 * @param lablib The lablib
 */
void lablib_render(Lablib * lablib);


void* lablib_get_env(Lablib* lablib);

/**
 * @brief Gonna process a single event
 * @param lablib The lablib
 * @param e The event
 */
void lablib_process(Lablib * lablib, SDL_Event * e);

/**
 * @brief Allocate the entire lablib and return it.
 * @param win The sdl window
 * @param ren The sdl renderer 
 * @param filename The path to the default game
 * @details Set the game as game_default if the path is empty
 * @return The lablib
 */
Lablib * lablib_init(void* env, SDL_Window* win, SDL_Renderer* ren, int nb_scene);


/**
 * @brief Destroy the entire lablib
 * @param lablib The lablib
 */
void lablib_destroy(Lablib* lablib);

/**
 * @brief Get the sdl window of the lablib
 * @param lablib The lablib
 * @return The sdl window
 */
SDL_Window* lablib_win(Lablib* lablib);


/**
 * @brief Get the height of the window
 * @param lablib The lablib
 * @return The height of the window
 */
int lablib_w_height(Lablib* lablib);

/**
 * @brief Get the width of the window
 * @param lablib The lablib
 * @return The width of the window
 */
int lablib_w_width(Lablib* lablib);

/**
 * @brief Get the number of button of the current scene
 * @param lablib The lablib
 * @return The number of button of the current scene
 */
int lablib_nb_button(Lablib* lablib);


/**
 * @brief Get the ith button of the current scene
 * @param lablib The lablib
 * @param index The requested button index
 * @return The ith button of the current scene
 */
Button* lablib_get_button(Lablib* lablib, int index);

/**
 * @brief Get the index of the current scene
 * @param lablib The lablib
 * @return the index of the current scene
 */
SceneI lablib_get_scene_index(Lablib* lablib);

/**
 * @brief Get the ith scene
 * @param lablib The lablib
 * @param i The index of the scene by using the enum type SceneI
 * @details If you want the current scene use get_current scene, use this function only if you want a specific one
 * @return The ith scene
 */
Scene* lablib_get_scene(Lablib* lablib, SceneI i);

/**
 * @brief Get the current scene, not his index but the pointer on the current scene itself
 * @param lablib The lablib
 * @return The current scene
 */
Scene* lablib_get_current_scene(Lablib* lablib);

/**
 * @brief Get the sdl renderer of the lablib
 * @param lablib The lablib
 * @return The sdl renderer
 */
SDL_Renderer* lablib_get_ren(Lablib* lablib);

/**
 * @brief Get the text font stored in the lablib
 * @param lablib The lablib
 * @return The font
 */
TTF_Font* lablib_get_font(Lablib* lablib);

/**
 * @brief Change the index of the current scene
 * @param lablib The lablib
 * @param new_scene The new scene
 * @details Care, this function take the INDEX of the new scene, not the scene itself.
 */
void lablib_change_scene(Lablib* lablib, SceneI new_scene);

/**
 * @brief handle the press of a key on the application
 * @param lablib The lablib
 * @param c   The contents of the key just pressed as a char 
 */
void lablib_kpress(Lablib* lablib, char c);

/**
 * @brief Get the active input on the current scene
 * @param lablib 
 * @details return null if there is none active input
 * @return Button* 
 */
Button* lablib_get_active_input(Lablib* lablib);

/**
 * @brief Active the current active input
 * 
 * @param lablib The lablib
 * @details Do nothing if there is none active input
 */
void lablib_activate_input(Lablib* lablib);

/**
 * @brief Set the coordonate of the last click
 * 
 * @param lablib The lablib
 * @param mouse The new last coordonate
 */
void lablib_set_last_coordinate(Lablib* lablib, SDL_Point mouse);


/**
 * @brief Get the coordonate of the last click
 * 
 * @param lablib The lablib
 * @return SDL_Point 
 */
SDL_Point lablib_get_last_coordinate(Lablib* lablib);

/**
 * @brief This function try to click on all the displayed button
 * 
 * @param lablib 
 */
void lablib_new_clic(Lablib* lablib);

/**
 * @brief Change the current game with a game with the same parameters
 * @param rows the number of rows of the game
 * @param cols the number of cols of the game
 */
void lablib_change_current_game(Lablib* lablib, int rows, int cols);

/**
 * @brief If there is an active cursor, gonna actualise it.
 * 
 * @param lablib 
 * @param mp 
 */
void lablib_mouse_move(Lablib* lablib, SDL_Point mp);


/**
 * @brief If there is an active cursor, gonna set it as inactive.
 * 
 * @param lablib 
 */
void lablib_click_release(Lablib* lablib);


Button* lablib_get_active_cursor(Lablib* lablib);


/**
 * @brief Create and return a new rect with the same width and the same height (maybe we could change the name XD)
 * @param x The x coord
 * @param y The y coord
 * @param w The width (so the height)
 * @return The rect
 */
SDL_Rect lablib_init_rect(int x, int y, int w);

/**
 * @brief Return the sdl color with r, g, b
 * @param r The red intensity
 * @param g The greeb intensity
 * @param b The blue intensity
 * @param a The oppacity of the color
 * @return The sdl color
 */
SDL_Color lablib_create_color(int r, int g, int b, int a);


/**
 * @brief Check if the given pointer is null, if yes exit with sdl_geterror msg
 * @param p The pointer
 * @return p itself
 */
void* cp(void* p);

void cc(int c);

/**
 * @brief Main loop: process the app, render the app and reloop
 * @param lablib The lablib
 * @return 0 if everything passed well otherwise an error code 
 */
int lablib_event_loop(Lablib* lablib);


/**
 * @brief Displays everything from the current scene (buttons, backgrounds...)
 * @param lablib The lablibironement
*/

void lablib_display_scenes(Lablib* lablib);

unsigned int lablib_nb_scene(Lablib* lablib);

/**
 * @brief Displays the current by loading the texture of the scene
 * @param lablib The lablibironement
*/
void display_current_scene(Lablib* lablib);


/**
 * @brief Check if i is out of range, if it is we exit with an error message.
*/
void lablib_check_scene(Lablib* lablib, SceneI i);


/**
 * @brief Set a scene at the index i, exit if the scene index is out of range.
*/
SceneI lablib_add_scene(Lablib* lablib, Scene* scene);

int Lablib_PollEvent(Lablib* lablib, SDL_Event* e);


#endif
