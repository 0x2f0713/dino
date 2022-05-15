#include "SDL2/SDL.h"
#include "math.h"
#include <queue>
#include <iostream>

#include "include/constant.h"
#include "include/ui/ui.h"

namespace GamePlay
{
    SDL_Rect objectSrcLocation[28] = {
        {0, 0, 73, 65},     // REPLAY
        {76, 6, 90, 90},    // DINO_NORMAL
        {166, 2, 92, 27},   // CLOUD
        {954, 29, 381, 21}, // GAMEOVER
        {260, 15, 92, 67},  // BIRD_1
        {352, 2, 92, 60},   // BIRD_2
        {446, 2, 34, 70},   // TREE_MEDIUM_1
        {480, 2, 34, 70},   // TREE_MEDIUM_2
        {514, 2, 34, 70},   // TREE_MEDIUM_3
        {548, 2, 34, 70},   // TREE_MEDIUM_4
        {582, 2, 34, 70},   // TREE_MEDIUM_5
        {616, 2, 34, 70},   // TREE_MEDIUM_6
        // {650, 2, 34, 70},
        {652, 2, 50, 100},   // TREE_BIG_1
        {702, 2, 50, 100},   // TREE_BIG_2
        {752, 2, 50, 100},   // TREE_BIG_3
        {802, 2, 50, 100},   // TREE_BIG_4
        {850, 2, 102, 100},  // TREE_BIG_5
        {1338, 2, 88, 94},   // DINO_1
        {1426, 2, 88, 94},   // DINO_2
        {1514, 2, 88, 94},   // DINO_3
        {1602, 2, 88, 94},   // DINO_4
        {1782, 2, 88, 94},   // DINO_5
        {1866, 36, 118, 60}, // DINO_6
        {1984, 36, 118, 60}, // DINO_7
        {2, 104, 2400, 24}   // GROUND
    };
    SDL_Rect objectDestLocation[28] = {
        {0, 0, 73, 65},                                      // REPLAY
        {76, 6, 90, 90},                                     // DINO_NORMAL
        {166, 2, 92, 27},                                    // CLOUD
        {954, 29, 381, 21},                                  // GAMEOVER
        {SCREEN_WIDTH, SCREEN_HEIGHT / 3 * 2 - 170, 92, 67}, // BIRD_1
        {SCREEN_WIDTH, SCREEN_HEIGHT / 3 * 2 - 170, 92, 60}, // BIRD_2
        {SCREEN_WIDTH, SCREEN_HEIGHT / 3 * 2 - 55, 34, 70},  // TREE_MEDIUM_1
        {SCREEN_WIDTH, SCREEN_HEIGHT / 3 * 2 - 55, 34, 70},  // TREE_MEDIUM_2
        {SCREEN_WIDTH, SCREEN_HEIGHT / 3 * 2 - 55, 34, 70},  // TREE_MEDIUM_3
        {SCREEN_WIDTH, SCREEN_HEIGHT / 3 * 2 - 55, 34, 70},  // TREE_MEDIUM_4
        {SCREEN_WIDTH, SCREEN_HEIGHT / 3 * 2 - 55, 34, 70},  // TREE_MEDIUM_5
        {SCREEN_WIDTH, SCREEN_HEIGHT / 3 * 2 - 55, 34, 70},  // TREE_MEDIUM_6
        // {650, 2, 34, 70},
        {SCREEN_WIDTH, SCREEN_HEIGHT / 3 * 2 - 79, 50, 100},  // TREE_BIG_1
        {SCREEN_WIDTH, SCREEN_HEIGHT / 3 * 2 - 79, 50, 100},  // TREE_BIG_2
        {SCREEN_WIDTH, SCREEN_HEIGHT / 3 * 2 - 79, 50, 100},  // TREE_BIG_3
        {SCREEN_WIDTH, SCREEN_HEIGHT / 3 * 2 - 79, 50, 100},  // TREE_BIG_4
        {SCREEN_WIDTH, SCREEN_HEIGHT / 3 * 2 - 79, 102, 100}, // TREE_BIG_5
        {160, SCREEN_HEIGHT / 3 * 2 - 80, 88, 94},            // DINO_1
        {1426, 2, 88, 94},                                    // DINO_2
        {160, SCREEN_HEIGHT / 3 * 2 - 80, 88, 94},
        {160, SCREEN_HEIGHT / 3 * 2 - 80, 88, 94},
        // {1514, 2, 88, 94},      // DINO_3
        // {1602, 2, 88, 94},      // DINO_4
        {1782, 2, 88, 94},                       // DINO_5
        {1866, 36, 118, 60},                     // DINO_6
        {1984, 36, 118, 60},                     // DINO_7
        {0, SCREEN_HEIGHT / 3 * 2 - 9, 2400, 24} // GROUND
    };
    void drawScore(context *ctx)
    {
        std::string s;
        char const *pchar;
        SDL_Rect dest = {0, 0, 0, 0};
        ctx->current_score++;
        ctx->high_score = std::max(ctx->high_score, ctx->current_score);
        s = std::to_string(ctx->current_score);
        pchar = s.c_str();
        UI::showText(ctx->renderer, ctx->font, pchar, UI::getTextColor(), &dest);
    }
    void drawReplay(context *ctx)
    {
        UI::showObject(ctx->renderer, object::REPLAY);
    }
    void drawTest(context *ctx)
    {
        for (auto i = 0; i < 28; i++)
        {
            UI::showObject(ctx->renderer, i);
        }
    }
    void drawDinoNormal(context *ctx)
    {
        UI::showObject(ctx->renderer, object::DINO_NORMAL);
    }
    void drawDinoRunning(context *ctx)
    {
        // if (ctx->jump)
        // {
        //     if (ctx->jumped == true && ctx->dinoDest.y >= objectDestLocation[object::DINO_3].y)
        //     {
        //         ctx->jump = false;
        //         ctx->jumped = false;
        //         UI::showObject(ctx->renderer, ctx->oddSteps ? object::DINO_3 : object::DINO_4);
        //     }
        //     else
        //     {
        //         ctx->dinoDest.y += ctx->v_y;
        //         ctx->v_y += ACCELERATION;
        //         std::cout << ctx->dinoDest.y << std::endl;
        //         UI::showObject(ctx->renderer, object::DINO_1, &ctx->dinoDest);
        //         ctx->jumped = true;
        //         // ctx->jump = false;
        //     }
        // }
        // else
        // {
            UI::showObject(ctx->renderer, ctx->oddSteps ? object::DINO_3 : object::DINO_4);
            ctx->oddSteps = !ctx->oddSteps;
        // }
    }
    void drawEnemy(context *ctx)
    {
        if (ctx->tick >= ctx->maxTick)
        {
            // add Enemy
            int object = rand() % 13;
            ctx->enemies.push_back(enemy(object + 4, objectDestLocation[object + 4]));
            ctx->tick = 0;
            ctx->maxTick = rand() % 100 + (rand() % 6 + 5) * 100;
        }
        else
        {
            for (size_t i = 0; i < ctx->enemies.size(); i++)
            {
                if (ctx->enemies[i].location.x + ctx->enemies[i].location.w > 0)
                {
                    ctx->enemies[i].location.x--;
                }
                else
                {
                    ctx->enemies.pop_front();
                }
                UI::showObject(ctx->renderer, ctx->enemies[i].enemyObject, &ctx->enemies[i].location);
            }
            ctx->tick++;
        }
    }
    void drawGround(context *ctx)
    {
        SDL_Rect groundDest2 = {2400, SCREEN_HEIGHT / 3 * 2 - 9, 2400, 24};
        if (ctx->groundDest.front().x <= -2400)
        {
            ctx->groundDest.pop();
            ctx->groundDest.push(groundDest2);
        }
        else
        {
            ctx->groundDest.front().x--;
            ctx->groundDest.back().x--;
        };
        UI::showObject(ctx->renderer, object::GROUND, &ctx->groundDest.front());
        UI::showObject(ctx->renderer, object::GROUND, &ctx->groundDest.back());
    }
    void redraw(context *ctx)
    {
        SDL_SetRenderDrawColor(ctx->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(ctx->renderer);
        drawScore(ctx);
        drawGround(ctx);
        drawEnemy(ctx);
        drawDinoRunning(ctx);
        SDL_RenderPresent(ctx->renderer);
    }
} // namespace GamePlay
