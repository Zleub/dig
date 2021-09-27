#ifndef ENTITY_H
#define ENTITY_H

#include <utility>
#include <iostream>

typedef std::pair<int, int> Position;

class Entity
{
public:
    class Stats {
    public:
        int strength;
        int agility;
        int intelligence;

        Stats();
        Stats(int, int, int);
        ~Stats();
    };

private:
    std::string symbol;

    Position position;
    Stats stats;

public:
    Entity();
    Entity(std::string, Position, Stats);
    ~Entity();
};

#endif