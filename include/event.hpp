#ifndef EVENT_H
#define EVENT_H

// #include <game.hpp>

class Game;

class Event
{
public:
    virtual int operator()(Game &) = 0;
};

#endif