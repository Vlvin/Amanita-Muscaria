#include <iostream>
#include <list>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

#include "headers/RoT.h"

list<RoT*> RoT::dogE = {};

RoT::RoT(int x, int y, int w, int h, int speed, SDL_Texture* flower)
    : x(x), y(y), w(w), h(h), speed(speed), tex(flower) {
    keyStates = SDL_GetKeyboardState(NULL);
    realBody = SDL_Rect{x, y, w, h};
    dogE.push_back(this);
}

RoT::~RoT() {
    SDL_DestroyTexture(tex);
    tex = NULL;
    dogE.remove(this);
}


double RoT::getX() {
    return x;
}
double RoT::getY() {
    return y;
}
double RoT::getW() {
    return w;
}
double RoT::getH() {
    return h;
}
double RoT::getRot() {
    return rotation;
}
SDL_Rect* RoT::getRect() {
    return &realBody; 
}

void RoT::upd(float DELTA) {
        if (keyStates[SDL_SCANCODE_W]) {
            y -= sin((rotation+90)/(180/M_PI)) * DELTA * speed;
            x -= cos((rotation+90)/(180/M_PI)) * DELTA * speed;
        }

        if (keyStates[SDL_SCANCODE_S]) {
            y += sin((rotation+90)/(180/M_PI)) * DELTA * speed;
            x += cos((rotation+90)/(180/M_PI)) * DELTA * speed;
        }

        if (keyStates[SDL_SCANCODE_A]) {
            y -= sin((rotation)/(180/M_PI)) * DELTA * speed;
            x -= cos((rotation)/(180/M_PI)) * DELTA * speed;
        }

        if (keyStates[SDL_SCANCODE_D]) {
            y += sin((rotation)/(180/M_PI)) * DELTA * speed;
            x += cos((rotation)/(180/M_PI)) * DELTA * speed;
        }

        if (keyStates[SDL_SCANCODE_Z]) {
            rotation -= 1 * DELTA * speed;
        }
        if (keyStates[SDL_SCANCODE_X]) {
            rotation += 1 * DELTA * speed;
        }
        if (rotation > 360) rotation -= 360;
        if (rotation < 0) rotation += 360;
    realBody.x = x;
    realBody.y = y;
    realBody.w = w;
    realBody.h = h;
}

void RoT::update(float DELTA) {
    for (auto i = dogE.begin(); i != dogE.end(); i ++) {
        (*i)->upd(DELTA);
    }
}

SDL_Texture* RoT::getTex() {
    return tex;
}

void RoT::drw(SDL_Renderer* ren) {
    SDL_RenderCopyEx(ren, this->getTex(), NULL, this->getRect(), this->getRot(), NULL, SDL_FLIP_NONE);
}

void RoT::draw(SDL_Renderer* ren) {
    for (auto i = dogE.begin(); i != dogE.end(); i ++) {
        (*i)->drw(ren);
    }
}