# **Lablib: SDL Wrapper for Interactive UIs in C**

Lablib is a lightweight SDL2 wrapper designed to simplify the creation of interactive graphical user interfaces (GUIs) using SDL2. The wrapper provides tools for handling scenes, buttons, inputs, and cursors in a flexible and modular manner.
Features

    Scene management with background images and user-defined render functions.
    Button creation with text or image, and support for button actions and resizing.
    Input fields that can handle text entry, with active and inactive states.
    Cursor for draggable objects with custom actions on drag and release.
    Dynamic resizing of UI elements based on window size.

**Requirements**

    SDL2
    SDL2_image
    SDL2_ttf

**Installation**

    Clone the repository:

```bash
git clone https://github.com/yourusername/Lablib.git
cd Lablib
```

Install the required libraries (SDL2, SDL2_image, SDL2_ttf).

Compile the project:

```bash
gcc -o my_game main.c -lSDL2 -lSDL2_image -lSDL2_ttf
```

Run your game:

    ./my_game

Basic Usage Example

Here’s an example of how to initialize the Lablib environment and create a simple interactive scene with buttons.
main.c

```c
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "lablib.h"

// Function to handle button click
void on_button_click(Button* button) {
    printf("Button clicked!\n");
}

int main() {
    // Initialize SDL and TTF
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }
    
    if (TTF_Init() == -1) {
        printf("TTF could not initialize! TTF_Error: %s\n", TTF_GetError());
        return -1;
    }

    // Create SDL window and renderer
    SDL_Window* window = SDL_CreateWindow("Lablib Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Create Lablib environment
    Lablib* lablib = lablib_init(NULL, window, renderer, 1);  // 1 scene

    // Create a scene
    Scene* scene = create_scene(lablib, 1);

    // Add a button to the scene
    Button* button = scene_add_button(scene, 0.2, 0.3, 0.6, 0.1, "Click Me", on_button_click);

    // Set the scene background
    set_scene_background(scene, "background.png");

    // Set the current scene
    lablib_change_scene(lablib, 0);

    // Main loop
    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }

            // Process input and events
            lablib_process(lablib, &e);
        }

        // Render the current scene
        lablib_render(lablib);

        // Delay to limit frame rate
        SDL_Delay(16);
    }

    // Cleanup
    lablib_destroy(lablib);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
```
**Explanation:**

    Initialization:
        SDL and TTF libraries are initialized.
        A window and renderer are created.
        Lablib is initialized with one scene.

    Scene and Button Creation:
        A scene is created with a single button.
        The button is positioned at 20% of the window width and 30% of the height, with 60% width and 10% height.
        A function on_button_click is associated with the button, which prints a message when clicked.

    Event Loop:
        The event loop processes user inputs, such as clicks, and renders the scene.

    Rendering:
        The scene, including all buttons and background, is rendered on the screen.

    Cleanup:
        Resources are cleaned up after exiting the main loop.

**Button Actions**

  In this example, the button triggers a on_button_click function when clicked. You can define your own actions for each button, allowing you to customize the behavior of the interface.

**Additional Features**

    Input Fields: Create interactive text input fields that can be activated and filled by the user.
    Cursor: Implement draggable cursors on the UI with specific actions when moved or released.
    Dynamic Resizing: Buttons and other UI elements automatically resize when the window size changes.

