#ifndef TILESET_H
#define TILESET_H

#include <iostream>
#include <filesystem>
#include <fstream>
#include <iomanip>

#include <nlohmann/json.hpp>

#include <SDL_image.h>

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

    void draw(unsigned char c, SDL_Rect *dst);
    void draw(std::string id, SDL_Rect *dst);
    void draw(unsigned char c, SDL_Rect *dst, int color_mod);

};

#endif