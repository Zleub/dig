#ifndef TILESET_H
#define TILESET_H

#include <iostream>
#include <filesystem>
#include <fstream>
#include <iomanip>

#include <nlohmann/json.hpp>
#include <SDL_image.h>

#include <color.hpp>

SDL_Texture *loadTexture(std::string path, SDL_Renderer *renderer);

namespace fs = std::filesystem;

class Tileset
{
    struct Set {
        SDL_Texture *tex;
        bool CP437;
        nlohmann::json config;
    };


private:
    /* data */
    std::map<std::string, Set> textureMap;
    SDL_Renderer *renderer;

    int width;
    int height;
public:
    nlohmann::json tile_config;
    std::map<std::string, nlohmann::json> tileMap;
 
    // Tileset(std::string);
    Tileset(fs::path, SDL_Renderer *);
    ~Tileset();

    void draw(unsigned char, SDL_Rect *);
    void draw(std::string, SDL_Rect *);
    void draw(unsigned char, SDL_Rect *, Color);

};

#endif