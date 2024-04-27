#ifndef LABLIB_SCENE_SAFE
#define LABLIB_SCENE_SAFE

/**
 * @brief Allocate a scene and return it
 * @param buttons The buttons array of the scene
 * @param nb_buttons The number of button in this array
 * @details The button array can contains input, its not a problem at all
 * @return The scene
 */
Scene* create_scene(Lablib* lablib, int nb_buttons);

Button* scene_add_button(Scene* scene,  float rx, float ry, float rw, float rh, const char* path, void(*act)(Button* b));

SceneI scene_id(Scene* scene);

int scene_current_nb_button(Scene* scene);

/**
 * @brief Return the number of button of the scene
 * @param scene The scene
 * @return The number of button of the scene
 */  
int scene_nb_buttons(Scene* scene);
   
/**
 * @brief Return the ith button of the scene
 * @param scene The scene
 * @param i the index of the button we want
 * @return The requested button
 */
Button* scene_get_button(Scene* scene, int i);
    
/**
 * @brief Destroy the entire scene
 * @param scene The scene
 */
void destroy_scene(Scene* scene);


/**
 * @brief sets the background of the scene passed in paramter
 * @param lablib The Lablib
 * @param scene The scene
 * @param path the relative filepath towards the image to be loaded
 * @details if scene is null or the path is incorrect, the function does nothing and the background stays NULL
 */
void set_scene_background(Lablib* lablib, Scene* scene, const char* path);

/**
 * @brief Returns the background of the scene passed in parameter
 * @param scene The scene
 * @return The texture representing the background of the scene, and NULL if it doesnt have one.
 */
SDL_Texture* scene_get_background(Scene* scene);


#endif
