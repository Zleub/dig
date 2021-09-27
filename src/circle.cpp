#include <circle.hpp>

Circle::Circle(SDL_Event e, int timer) : e(e), timer(timer)
{
}

Circle::~Circle()
{
}

int Circle::operator()(Game &game)
{
    // int term_x = e.button.x / game.STEP_WIDTH;
    // int term_y = e.button.y / game.STEP_HEIGHT;

    // for (auto &pair : restore)
    // {
    //     game.term[pair.first] = pair.second;
    // }

    // restore.clear();

    // if (timer == 0)
    // {
    //     return 1;
    // }

    // int rad = timer / 2;
    // for (int y = (term_y - rad < 0 ? 0 : term_y - rad); y <= (term_y + rad < game.TERM_HEIGHT - 1 ? term_y + rad : game.TERM_HEIGHT - 1); y++)
    // {
    //     for (int x = (term_x - rad < 0 ? 0 : term_x - rad); x <= (term_x + rad < game.TERM_WIDTH - 1 ? term_x + rad : game.TERM_WIDTH - 1); x++)
    //     {
    //         int r = 0xFF;
    //         int g = 0x00;
    //         int b = 0x00;

    //         if (
    //             pow(abs(x - term_x), 2) + pow(abs(y - term_y), 2) <= pow(rad, 2) &&
    //             pow(abs(x - term_x), 2) + pow(abs(y - term_y), 2) > pow(rad - 1, 2)

    //         )
    //         {
    //             restore[x + y * game.TERM_WIDTH] = game.term[x + y * game.TERM_WIDTH];
    //             game.term[x + y * game.TERM_WIDTH] = r + (g << 8) + (b << 16);
    //         }
    //     }
    // }

    // timer -= 1;
    return 0;
}