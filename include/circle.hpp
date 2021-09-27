#ifndef CIRCLE_H
#define CIRCLE_H

#include <map>

#include <SDL.h>
#include <stdlib.h>
#include <math.h>

#include <event.hpp>
#include <game.hpp>

class Circle: public Event
{
private:
    int timer;
    SDL_Event e;

    std::map<int, int> restore;
public:
    Circle(SDL_Event, int);
    ~Circle();

    int operator()(Game &);
};

#endif