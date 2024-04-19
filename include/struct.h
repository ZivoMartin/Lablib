#ifndef STRUCT_INTERFACE_SAFE
#define STRUCT_INTERFACE_SAFE

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>  // required to load transparent texture from PNG
#include <SDL_ttf.h>    // required to use TTF fonts
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define DEFAULT_OPPACITY 255

typedef struct Button Button;
typedef struct Input Input;
typedef struct Scene Scene;
typedef struct Cursor Cursor;
typedef unsigned int SceneI;

/**< Global environement of the game*/
typedef struct Lablib_t {
	int nb_scene;                   /** The total static number of scenes */
	int current_nb_scene;
    Scene** scene_arr;     /**< A buffer for each scene of the game*/
    SceneI current_scene;       /**< An index for get in constant time the current scene*/
    SDL_Texture* numbers[4][10];    /**< A buffer too store the constraints text numbers, there is digits for each colors and there is 4 colors*/
    TTF_Font* font;                 /**< The font used in the app*/
    SDL_Renderer* ren;              /**< The SDL renderer*/
    SDL_Window* win;                /**< The SDL window*/
    int w,h;                        /**< The CURRENT width and height of the window*/ 
    int last_x, last_y;             /**< Coordinates of the last click*/
}Lablib;

/**< A scene is an abstract object with some labels, to display a scene we just have to iterate through the elements and display each of them*/
struct Scene{
	SceneI id;
	Lablib* lablib;
	Button** buttons;         /**< The array of buttons of the scene */
	int nb_buttons;           /**< The number of button of the scene */
	int current_nb_button;
	SDL_Texture* background;  /**< The background of the scene, is an image in general, otherwise a default color*/
};

/**< The button struct is the heart of our app, basically a scene contains buttons and display each again and again,
a button can handle a click by doing a specific action on the game lablibironement. A button is automatically
resized when the app is resized. A button can have sublabbel like input or cursor. A click on an input button activate the input, a on on
a cursor button activate the cursor.*/
struct Button {
  Lablib* lablib;                   /**< The lablib */
  const char* text;                 /**< The current text of the button IF the button isn't an input*/
  SDL_Color color;            /**< The color of the button */
  float rx, ry, rw, rh;         /**< This is the data to safely and properly resize our button, rx represents
                              the x position of the button relatively too the width of the window. ry represents the position
                              of the button relatively too the height of the window. Finaly, rw and rh are the relative width and height
                              of the button.*/
  int w, h;                   /**< The CURRENT width and the height of the button */
  SDL_Texture* texture;       /**< The current texture of the button */
  void (*action)(Button* b);  /**< The action of the button when we click on it */
  void (*display)(Button* b); /**< The function who displays the button*/
  Input* input;               /**< The input part of the button, null if the button isn't an input*/
  Cursor* cur;                /**< The cursor part of the button, null if the button isn't an cursor*/
};

#define INPUT_MAX_LEN 30              /**< The max len of an input*/
#define EMPTY_TEXT "              "   /**< If a button receiv an empty text, we but this text inside of it*/
#define INPUT_WIDTH 300               /**< The static width of an input*/

/**< An input is a substruct of button, an input can be active (waiting for text) or not. If it is active,
the entry key gonna activate the input (not the button) and gonna do a specific job. The button action is 
to set the input as active, the input action is a job to execute when the user has finished to type.*/
struct Input {
  Button* b;                      /**< The associated button of the input*/
  char* placeholder;              /**< A default text in the input*/
  SDL_Color placeholder_color;    /**< The current color of the placeholder*/
  int nb_char;                    /**< The current number of char in the input */
  bool is_active;                 /**< Indicate if the input is active i.e if we can add text in it */
  char text[INPUT_MAX_LEN];       /**< The text buffer of the input */
  void (*action)(Button* b);      /**< The action to execute when the entry key is pressed*/
  int clock;                      /**< Use to know if we have to display the cursor*/
};

struct Cursor {
  Button* b;
  bool is_active;
  SDL_Texture* text;
  float rx, ry;
  float rh;
  int w, h;
  int last_h;
  void (*move_cursor_action)(Button* b);
  void (*release_cursor_action)(Button* b);
};

#endif
