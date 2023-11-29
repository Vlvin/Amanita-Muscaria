/*************************
 * This project is called Rotate and Go Forward
 * In this small project i want to realize sprite that will
 * be rotated whenever user want it and go forward in any rotation angle
 * 
 * Small Proj realized in C++ with using SDL2 with SDL_image addon and OOP paradigm
*************************/


#include <iostream>
#include <string>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

#include "headers/RoT.h"

// Global variables presenting window, renderer and texture
SDL_Window* mainWindow = NULL;
SDL_Renderer* ren = NULL;
SDL_Texture* flower;

// Global variables with Charactonim names
int SCR_WIDTH = 640, SCR_HEIGHT = 480;


/**
 * Initializing function with all checks
 * 
 * returns true when all initialized well
 * returns false on fail
*/
bool init() {
    bool ok = true;
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        ok = false;
        cout << "Can't init SDL: " << SDL_GetError() << endl;
    }

    int flags = IMG_INIT_PNG;
    if (!(IMG_Init(flags) & flags)) {
        ok = false;
        cout << "Can't init SDL_image: " << IMG_GetError() << endl;
    }

    mainWindow = SDL_CreateWindow("Rotate'n'Go", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCR_WIDTH, SCR_HEIGHT, SDL_WINDOW_SHOWN);
    if (mainWindow == NULL) {
        ok = false;
        cout << "Can't create Window: " << SDL_GetError() << endl;
    }

    ren = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == NULL) {
        ok = false;
        cout << "Can't create Renderer: " << SDL_GetError() << endl;
    }

    return ok;
}

/**
 * Loading function with all checks
 * 
 * returns true when all initialized well
 * returns false on fail
*/
bool load() {
    bool ok = true;
    SDL_Surface* tempSurf = NULL;
    tempSurf = IMG_Load("./res/sprites/Arrow.png");
    if (tempSurf == NULL) {
        ok = false;
        cout << "Can't load img: " << IMG_GetError() << endl;
    }

    flower = SDL_CreateTextureFromSurface(ren, tempSurf);
    if (flower == NULL) {
        ok = false;
        cout << "Can't create Texture from surface: " << SDL_GetError() << endl;
    }
    SDL_FreeSurface(tempSurf);
    tempSurf = NULL;

    return ok;
}

/**
 * quit() function destroying 
 * all global pointed objects
 * 
*/
void quit() {
    SDL_DestroyRenderer(ren);
    ren = NULL;

    SDL_DestroyTexture(flower);
    flower = NULL;

    SDL_DestroyWindow(mainWindow);
    mainWindow = NULL;

    SDL_Quit();
    IMG_Quit();
}

int main() {
    if (!init()) {
        quit();
        return 1;
    }

    if (!load()) {
        quit();
        return 1;
    }

    // local vars
    SDL_Event event;
    RoT mc(100, 100, 100, 100, 150, flower);
    const Uint8 *keyStates = SDL_GetKeyboardState(NULL);
    Uint8 r = 0, g = 0, b = 0;

    // some time stuff
    Uint64 NOW = SDL_GetTicks64(), PRE = NOW;
    int FPS = 60;
    float DELTA, DESIRED_DELTA = 1000/FPS;

    bool running = true;

    // Game Loop
    while (running) {

        // calculating frames delta
        NOW = SDL_GetTicks64();
        DELTA = NOW - PRE;
        PRE = NOW;

        // delay for frame cap
        if (DELTA < DESIRED_DELTA) {
            SDL_Delay(DESIRED_DELTA - DELTA);
        }

        // Event check
        while (SDL_PollEvent(&event)) {

            // quit() on cross button click
            if (event.type == SDL_QUIT) {
                quit();
                return 0;
            }
        }

        // updaiting RoT's positions
        RoT::update(DELTA * 0.001f);

        if (keyStates[SDL_SCANCODE_R]) {
            if (keyStates[SDL_SCANCODE_UP]) {
                r += 1;
            }
            if (keyStates[SDL_SCANCODE_DOWN]) {
                r -= 1;
            }
        }        

        if (keyStates[SDL_SCANCODE_G]) {
            if (keyStates[SDL_SCANCODE_UP]) {
                g += 1;
            }
            if (keyStates[SDL_SCANCODE_DOWN]) {
                g -= 1;
            }
        }    

        if (keyStates[SDL_SCANCODE_B]) {
            if (keyStates[SDL_SCANCODE_UP]) {
                b += 1;
            }
            if (keyStates[SDL_SCANCODE_DOWN]) {
                b -= 1;
            }
        }

        r = max(min(r,(Uint8)254), (Uint8)1);
        g = max(min(g,(Uint8)254), (Uint8)1);
        b = max(min(b,(Uint8)254), (Uint8)1);


        // quit() on escape button
        if (keyStates[SDL_SCANCODE_ESCAPE]) {
            running = false;
            quit();
            return 0;
        }

        // filling ren background with one color
        SDL_SetRenderDrawColor(ren, r, g, b, 0xFF);
        SDL_RenderClear(ren);

        // drawing all RoT objects on ren
        RoT::draw(ren);

        // Presenting ren on main window surface
        SDL_RenderPresent(ren);
    }
    quit();

}