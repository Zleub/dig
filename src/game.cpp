#include <game.hpp>

std::vector<std::string> get_directories(const std::string &s)
{
    std::vector<std::string> r;
    std::cout << s << std::endl;
    for (auto &p : std::filesystem::recursive_directory_iterator(s))
        if (p.is_directory())
            r.push_back(p.path().string());
    return r;
}

SDL_Texture *loadTexture(std::string path, SDL_Renderer *renderer)
{
    SDL_Texture *newTexture = NULL;
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());

    SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0x0, 0x0 ) );
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    } 
    else
    {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

Game::Game() : 
	heros(std::string("@"), Position(0, 0), Entity::Stats(0, 0, 0))
{
    init_ttf();
    init_constants();
    init_sdl();

	tileset = new Tileset("gfx/NeoDaysTileset", renderer);

    running = true;

    term_renderer = std::vector<Tile>(TERM_WIDTH * TERM_HEIGHT);
    // term = std::vector<int>(TERM_WIDTH * TERM_HEIGHT);
    // term_text = std::vector<int>(TERM_WIDTH * TERM_HEIGHT);

    for (int y = 0; y < TERM_HEIGHT; y++)
    {
        for (int x = 0; x < TERM_WIDTH; x++)
        {

            Tile & tile = term_renderer[x + y * TERM_WIDTH];
            tile.fg_color = {
                .r = 0x00u + (255 / ((TERM_WIDTH + TERM_HEIGHT) / 2)) * (x + y) / 2,
                .g = 0x00u + (255 / TERM_WIDTH) * x,
                .b = 0x00u + (255 / TERM_HEIGHT) * y,
                .a = 255
            };
            tile.tile_index = 176 + rand() % 3;
            // term[x + y * TERM_WIDTH] = r + (g << 8) + (b << 16);
            // term_text[x + y * TERM_WIDTH] = 179 + rand() % 40;
        }
    }

    term_print();
    SDL_UpdateWindowSurface(window);
}

Game::~Game()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::run()
{
    while (running)
    {
        Uint64 start = SDL_GetPerformanceCounter();

        if (events.size() > 0)
            std::cout << events.size() << " element in stack call" << std::endl;

        std::vector<std::vector<Event *>::iterator> erase;
        for (auto it = events.begin(); it != events.end(); ++it)
        {
            if ((*(*it))(*this) != 0)
                erase.push_back(it);
            // it = array_test.erase(it);
        }

        for (auto it = erase.begin(); it != erase.end(); ++it)
            events.erase(*it);

        input();

        SDL_SetRenderDrawColor(renderer, BLACK.r, BLACK.g, BLACK.b, BLACK.a);
        SDL_RenderClear(renderer);
        term_print();

        SDL_Rect dest = {
            .x = 12 * STEP_WIDTH + OFFSET_WIDTH / 2,
            .y = 12 * STEP_HEIGHT + OFFSET_HEIGHT / 2,
            STEP_WIDTH,
            STEP_HEIGHT};
        tileset->draw("player_male", &dest);

        int rand_dst = rand() % (TERM_WIDTH * TERM_HEIGHT);
        term_renderer[rand_dst].tile_index = 176 + rand() % 3;

        Uint64 end = SDL_GetPerformanceCounter();
        float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;

        int delay = floor(16.666f - elapsedMS) < 0 ? 0 : floor(16.666f - elapsedMS);
        SDL_Delay(delay);

        // end = SDL_GetPerformanceCounter();
        // float elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();
        // int fps = 1.0f / elapsed;

        // SDL_Rect _dest = {10, 10, 0, 0};
        // renderText(std::to_string(fps), &_dest);
        SDL_RenderPresent(renderer);
    }
}

void Game::input()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            SDL_Log("Program quit after %i ticks", e.quit.timestamp);
            SDL_DestroyWindow(window);
            SDL_Quit();
            exit(0);
        }
        // else if (e.type == SDL_MOUSEBUTTONDOWN) {
        // 	events.push_back(new Circle(e, 40));
        // }
    }

    return;
}

void Game::term_print()
{
    for (int term_y = 0; term_y < TERM_HEIGHT; term_y += 1)
    {
        for (int term_x = 0; term_x < TERM_WIDTH; term_x += 1)
        {
            SDL_Rect rect = {
                .x = term_x * STEP_WIDTH + OFFSET_WIDTH / 2,
                .y = term_y * STEP_HEIGHT + OFFSET_HEIGHT / 2,
                .w = STEP_WIDTH,
                .h = STEP_HEIGHT};

            Tile & tile = term_renderer[term_x + term_y * TERM_WIDTH];
            tileset->draw(tile.tile_index, &rect, tile.fg_color);
        }
    }

    return;
}

void Game::renderText(std::string text, SDL_Rect *dest)
{
    SDL_Color fg = {255, 255, 255};
    SDL_Surface *surf = TTF_RenderGlyph_Solid(font, text.c_str()[0], fg);

    dest->w = surf->w;
    dest->h = surf->h;

    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surf);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, dest);

    SDL_RenderCopy(renderer, tex, NULL, dest);
    SDL_DestroyTexture(tex);
    SDL_FreeSurface(surf);
}
