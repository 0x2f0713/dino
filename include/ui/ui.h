#include <string>
#include <queue>
#include <math.h>
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
    TTF_Font *font16;
    TTF_Font *font24;
    SDL_Texture *object;
    uint64_t high_score;
    uint64_t current_score;
    Uint32 lastUpdate;
    SDL_Rect dinoDest;
    bool isPlaying;
    bool oddSteps;
    int dinoStatus;
    bool jump;
    bool jumping;
    bool gameover;
    int v_y;
    float v;
    int enemyTick;
    int cloudTick;
    int maxEnemyTick;
    int maxCloudTick;
    std::deque<SDL_Rect> groundDest;
    std::deque<enemy> enemies;
    std::deque<SDL_Rect> clouds;
    void resetContext() {
        high_score = std::max(current_score, high_score);
        SDL_Rect groundDest1 = {0, SCREEN_HEIGHT / 3 * 2 - 9, 2400, 24};
        SDL_Rect groundDest2 = {2400, SCREEN_HEIGHT / 3 * 2 - 9, 2400, 24};
        dinoDest = {160, SCREEN_HEIGHT / 3 * 2 - 80, 88, 94};
        isPlaying = false;
        current_score = 0;
        oddSteps = false;
        dinoStatus = DINO_STATUS_RUNNING;
        jump = false;
        jumping = false;
        gameover = false;
        lastUpdate = SDL_GetTicks();
        v = 10;
        v_y = V_JUMP;
        enemyTick = 0;
        cloudTick = 0;
        maxEnemyTick = 50;
        maxCloudTick = 30;
        groundDest.clear();
        enemies.clear();
        groundDest.push_back(groundDest1);
        groundDest.push_back(groundDest2);
    }
    context()
    {
        quit = false;
        window = NULL;
        renderer = NULL;
        font16 = NULL;
        font24 = NULL;
        high_score = 0;
        current_score = 0;
        resetContext();
    }
};
enum object
{
    REPLAY,
    DINO_NORMAL,
    CLOUD,
    GAMEOVER,
    BIRD_1,
    BIRD_2,
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
    bool initIMGLoader();
    bool initMixer();
    bool loadFont(TTF_Font *&font, int size);
    bool loadSoundEffect();

    /* Destroyer */
    void destroyWindow(context *ctx);

    /* Utilities */
    SDL_Texture *loadMedia(std::string mediaPath, SDL_Renderer *renderer);
    bool showText(SDL_Renderer *renderer, TTF_Font *font, char const *text, SDL_Color color, SDL_Rect *dst_rect);
    void updateSurface(SDL_Surface *src, SDL_Surface *des, int x, int y, int w, int h);
    void updateRenderer();
    SDL_Color getTextColor();
    int playPressSound();
    int playHitSound();
    int playReachedSound();
    SDL_Texture* loadObject(SDL_Renderer * renderer);
    void showObject(SDL_Renderer *renderer, int objectIndex);
    void showObject(SDL_Renderer *renderer, int objectIndex, SDL_Rect *dst_rect);
} // namespace UI

#endif