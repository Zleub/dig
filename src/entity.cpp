#include <entity.hpp>

Entity::Entity() {}
Entity::Entity(std::string symbol, Position position, Stats stats) :
    symbol(symbol), position(position), stats(stats)
{}

Entity::~Entity() {}

Entity::Stats::Stats() {}
Entity::Stats::Stats(int str, int agi, int intel) :
    strength(str), agility(agi), intelligence(intel)
{}
Entity::Stats::~Stats() {}