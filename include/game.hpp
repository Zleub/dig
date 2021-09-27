#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <iostream>
#include <vector>

#include <circle.hpp>
#include <entity.hpp>
#include <event.hpp>
#include <tileset.hpp>
#include <tile.hpp>

class Game
{
public:
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;

    int _TERM_WIDTH;
    int _TERM_HEIGHT;

    int TERM_WIDTH;
    int TERM_HEIGHT;

    int STEP_WIDTH;
    int STEP_HEIGHT;

    int OFFSET_WIDTH;
    int OFFSET_HEIGHT;

    int height;
    int line_skip;
    int minx, maxx, miny, maxy, advance;

    std::vector<Tile> term_renderer;
    // std::vector<int> term_text;

private:
    SDL_Window *window = NULL;
    SDL_Surface *windowSurface = NULL;

    SDL_Renderer *renderer;
    SDL_Texture *box;
    TTF_Font *font;

    SDL_Texture *texture;

    bool running;

    std::vector<Event *> events;

    Entity heros;
    Tileset *tileset;

public:
    Game();
    ~Game();

    void init_constants();
    void init_sdl();
    void init_ttf();
    void init_tileset();

    void run();
    void input();
    void term_print();
    void renderTile(char, SDL_Rect *);
    void renderTile(int, SDL_Rect *);
    void renderText(std::string, SDL_Rect*);
};

#endif