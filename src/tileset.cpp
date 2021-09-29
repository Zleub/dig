#include <tileset.hpp>

// Tileset::Tileset(std::string path) :
//     Tileset( fs::path(path) )
// {}

Tileset::Tileset(fs::path path, SDL_Renderer *renderer) :
    renderer(renderer)
{
    path.make_preferred();

    std::cout << "Loading " << path << " as a tileset path" << std::endl;

    fs::path tile_config_path = path / "tile_config.json";
    fs::file_status s = fs::status(tile_config_path);

    if ( s.type() == fs::file_type::regular)
    {
        std::ifstream input(path / "tile_config.json");
        input >> tile_config;
    }
    else {
        std::cout << "Issue with the tile_config.json file" << std::endl;
    }

    std::cout <<  tile_config["tile_info"].dump() << std::endl;

    width = tile_config["tile_info"][0]["width"];
    height = tile_config["tile_info"][0]["height"];

    for (nlohmann::json j : tile_config["tiles-new"]) {
        std::cout << j["file"] << std::endl;
        
        std::string file = j["file"];
        std::string tex_path = (path / file).string();
        SDL_Texture *texture = loadTexture(tex_path, renderer);
        if (texture == NULL)
        {
            printf("Failed to load texture image!\n");
        }
        else 
        {
            textureMap[file] = {
                .tex = texture,
                .CP437 = !j["ascii"].empty(),
                .config = j
            };

            if (textureMap[file].CP437 == false) {
                auto conf = textureMap[file].config;
                for (auto tile : conf["tiles"]) {
                    tile["file"] = file;
                    if (tile["id"].is_array())
                    {
                        for (std::string id : tile["id"]) {
                            if (!tileMap[id].is_null())
                                std::cout << "Warning: Duplicate tile id: " << id << std::endl;
                            tileMap[id] = tile;
                        }
                    }
                    else {
                        std::string id = tile["id"];
                        if (!tileMap[id].is_null())
                            std::cout << "Warning: Duplicate tile id: " << id << std::endl;
                        tileMap[id] = tile;
                    }
                }
            }
        }
    }

    for (auto &[name, set] : textureMap) {
        std::cout << name << " : " << set.CP437 << std::endl;
    }

}

Tileset::~Tileset()
{
}

void Tileset::draw(unsigned char c, SDL_Rect *dst) {
    SDL_Rect src = { width * (c % 16), height * (c / 16), width, height };

    SDL_RenderCopy(renderer, textureMap["fallback.png"].tex, &src, dst);
}

void Tileset::draw(unsigned char c, SDL_Rect *dst, Color color) {
    SDL_Rect src = { width * (c % 16), height * (c / 16), width, height };


    SDL_SetTextureColorMod(textureMap["fallback.png"].tex, color.r, color.g, color.b);
    SDL_RenderCopy(renderer, textureMap["fallback.png"].tex, &src, dst);
}

void Tileset::draw(std::string id, SDL_Rect *dst) {
    nlohmann::json tile = tileMap[id];

    int index = tile["fg"];
    std::string file = tile["file"];
    SDL_Rect src = { width * (index % 16), height * (index / 16), width, height };

    SDL_RenderCopy(renderer, textureMap[file].tex, &src, dst);
}