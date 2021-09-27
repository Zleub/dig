#include <game.hpp>

void Game::init_constants()
{
    STEP_WIDTH = 20;
    STEP_HEIGHT = 20;

    // std::cout << "STEP_WIDTH: " << STEP_WIDTH << std::endl;
    // std::cout << "STEP_HEIGHT: " << STEP_HEIGHT << std::endl;

    SCREEN_WIDTH = 800;
    SCREEN_HEIGHT = 600;

    // std::cout << "SCREEN_WIDTH: " << SCREEN_WIDTH << std::endl;
    // std::cout << "SCREEN_HEIGHT: " << SCREEN_HEIGHT << std::endl;

    _TERM_WIDTH = SCREEN_WIDTH / STEP_WIDTH;
    _TERM_HEIGHT = SCREEN_HEIGHT / STEP_HEIGHT;

    // std::cout << "_TERM_WIDTH: " << _TERM_WIDTH << std::endl;
    // std::cout << "_TERM_HEIGHT: " << _TERM_HEIGHT << std::endl;

    TERM_WIDTH = _TERM_WIDTH;   //+ (1 - _TERM_WIDTH % 2);
    TERM_HEIGHT = _TERM_HEIGHT; //+ (1 - _TERM_HEIGHT % 2);

    // std::cout << "TERM_WIDTH: " << TERM_WIDTH << std::endl;
    // std::cout << "TERM_HEIGHT: " << TERM_HEIGHT << std::endl;

    OFFSET_WIDTH = SCREEN_WIDTH % STEP_WIDTH;
    OFFSET_HEIGHT = SCREEN_HEIGHT % STEP_HEIGHT;

    // std::cout << "OFFSET_WIDTH: " << OFFSET_WIDTH << std::endl;
    // std::cout << "OFFSET_HEIGHT: " << OFFSET_HEIGHT << std::endl;

    return;
}

void Game::init_sdl()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        exit(-1);
    }

    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        exit(-2);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
        exit(-4);
    }

    windowSurface = SDL_GetWindowSurface(window);
    // SDL_SetSurfaceBlendMode(windowSurface, SDL_BLENDMODE_BLEND);
    // SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

void Game::init_ttf()
{
    if (TTF_Init() < 0)
    {
        std::cout << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;
        exit(-3);
    }

    font = TTF_OpenFont("Anonymous.ttf", 24);
    if (!font)
    {
        std::cout << "Error loading font: " << TTF_GetError() << std::endl;
        exit(-4);
    }

    if (TTF_FontFaceIsFixedWidth(font))
        std::cout << "The font is fixed width." << std::endl;
    else
        std::cout << "The font is not fixed width." << std::endl;

    height = TTF_FontHeight(font);
    printf("The font max height is: %d\n", height);
    line_skip = TTF_FontLineSkip(font);
    printf("The font line skip is: %d\n", line_skip);

    printf("The font ascent is: %d\n", TTF_FontAscent(font));
    printf("The font descent is: %d\n", TTF_FontDescent(font));

    if (TTF_GlyphMetrics(font, 'g', &minx, &maxx, &miny, &maxy, &advance) == -1)
        printf("%s\n", TTF_GetError());
    else
    {
        printf("minx    : %d\n", minx);
        printf("maxx    : %d\n", maxx);
        printf("miny    : %d\n", miny);
        printf("maxy    : %d\n", maxy);
        printf("advance : %d\n", advance);
    }
}