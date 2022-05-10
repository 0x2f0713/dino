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
    SDL_Texture *object;
    uint64_t high_score;
    uint64_t current_score;
    bool isPlaying;
    bool oddSteps;
    int groundX;
    context()
    {
        quit = false;
        window = NULL;
        renderer = NULL;
        font = NULL;
        high_score = 0;
        current_score = 0;
        isPlaying = false;
        oddSteps = false;
        groundX = 0;
    }
};
enum object
{
    REPLAY,
    DINO_NORMAL,
    CLOUD,
    BIRD_1,
    BIRD_2,
    GAMEOVER,
    TREE_MEDIUM_1,
    TREE_MEDIUM_2,
    TREE_MEDIUM_3,
    TREE_MEDIUM_4,
    TREE_MEDIUM_5,
    TREE_MEDIUM_6,
    TREE_BIG_1,
    TREE_BIG_2,
    TREE_BIG_3,
    TREE_BIG_4,
    TREE_BIG_5,
    DINO_1,
    DINO_2,
    DINO_3,
    DINO_4,
    DINO_5,
    DINO_6,
    DINO_7,
    GROUND
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
    SDL_Texture* loadObject(SDL_Renderer * renderer);
    void showObject(SDL_Renderer *renderer, int objectIndex);
} // namespace UI