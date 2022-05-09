#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

struct context
{
    bool quit;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event e;
    TTF_Font *font;
    uint64_t high_score;
    uint64_t current_score;
    bool isPlaying;
    context()
    {
        quit = false;
        window = NULL;
        renderer = NULL;
        font = NULL;
        high_score = 0;
        current_score = 0;
        isPlaying = false;
    }
};

namespace UI
{
    /* Initializer */
    bool init(context *ctx);
    bool initWindow(context *ctx);
    bool initTTF();
    bool loadFont(TTF_Font *&font);
    bool initIMGLoader();

    /* Destroyer */
    void destroyWindow(context *ctx);

    /* Utilities */
    SDL_Texture *loadMedia(std::string mediaPath, SDL_Renderer *renderer);
    bool showText(SDL_Renderer *renderer, TTF_Font *font, char const *text, SDL_Color color, SDL_Rect *dst_rect);
    void updateSurface(SDL_Surface *src, SDL_Surface *des, int x, int y, int w, int h);
    void updateRenderer();
    SDL_Color getTextColor();
} // namespace UI