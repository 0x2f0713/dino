#include <string>
#include <queue>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "include/constant.h"
// #include "include/object_location.h"

#ifndef UI_H
#define UI_H
struct enemy {
    SDL_Rect location;
    int enemyObject;
    enemy(int _enemyObject, SDL_Rect _location) {
        enemyObject = _enemyObject;
        location = _location;
    }
};
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
    Uint32 lastUpdate;
    SDL_Rect dinoDest;
    bool isPlaying;
    int oddSteps;
    bool jump;
    bool jumped;
    int v_y;
    int tick;
    int maxTick;
    std::queue<SDL_Rect> groundDest;
    std::deque<enemy> enemies;
    context()
    {
        SDL_Rect groundDest1 = {0, SCREEN_HEIGHT / 3 * 2 - 9, 2400, 24};
        SDL_Rect groundDest2 = {2400, SCREEN_HEIGHT / 3 * 2 - 9, 2400, 24};
        dinoDest = {160, SCREEN_HEIGHT / 3 * 2 - 80, 88, 94};
        quit = false;
        window = NULL;
        renderer = NULL;
        font = NULL;
        high_score = 0;
        current_score = 0;
        isPlaying = false;
        oddSteps = 0;
        jump = false;
        jumped = false;
        // v_y = -1000;
        tick = 0;
        maxTick = RANDOM_ENEMY;
        groundDest.push(groundDest1);
        groundDest.push(groundDest2);
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
    void showObject(SDL_Renderer *renderer, int objectIndex, SDL_Rect *dst_rect);
} // namespace UI

#endif