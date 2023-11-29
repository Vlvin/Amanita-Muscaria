#pragma once

#include <iostream>
#include <list>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

/**
 * RoT class Represents Rotating object Texture
 * 
 * Really it becames to drawable entity 
 * with own position, speeed, rotation degrees, 
 * key Check and much more
*/

class RoT {
    // @e contain all RoT object pointers
    static list<RoT*> dogE;

    // RealTime coordinates
    double x, y;

    // RealTime boxBody parameters
    double w, h;

    // RealTime speed
    double speed;

    // RealTime rotation
    double rotation;

    // struct contains position and box parameters to draw
    SDL_Rect realBody;

    // own texture to draw
    SDL_Texture* tex;

    // keyStates pointers
    const Uint8 *keyStates;
public:

    // Constructor, Destructor
    RoT(int x, int y, int w, int h, int speed, SDL_Texture* flower);
    ~RoT();

    // getters
    double getX();
    double getY();
    double getW();
    double getH();
    double getRot();
    SDL_Rect* getRect();
    SDL_Texture* getTex();

    // self update
    void upd(float DELTA);

    // self draw
    void drw(SDL_Renderer* ren);

    // update iterator
    static void update(float DELTA);

    // draw iterator
    static void draw(SDL_Renderer* ren);

};