#include "SDL2/SDL.h"
#include "math.h"
#include <queue>
#include <iostream>

#include "include/constant.h"
#include "include/ui/ui.h"

namespace GamePlay
{
    float animatedDinoFPS = 10.0f;
    float animatedBirdFPS = 9.0f;
    SDL_Rect hiText = {SCREEN_WIDTH / 2 + 300, SCREEN_HEIGHT / 2 - 250, 0, 0};
    SDL_Rect destHighScore = {SCREEN_WIDTH / 2 + 400, SCREEN_HEIGHT / 2 - 250, 0, 0};
    SDL_Rect destCurrentScore = {SCREEN_WIDTH / 2 + 400, SCREEN_HEIGHT / 2 - 200, 0, 0};
    const SDL_Rect groundDest2 = {2400, SCREEN_HEIGHT / 3 * 2 - 9, 2400, 24};
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
        {CENTER_HORIZONTAL(73), CENTER_VERTICAL(65), 73, 65},         // REPLAY
        {76, 6, 90, 90},                                              // DINO_NORMAL
        {166, 2, 92, 27},                                             // CLOUD
        {CENTER_HORIZONTAL(381), CENTER_VERTICAL(21) - 100, 381, 21}, // GAMEOVER
        {SCREEN_WIDTH, SCREEN_HEIGHT / 3 * 2 - 170, 92, 67},          // BIRD_1
        {SCREEN_WIDTH, SCREEN_HEIGHT / 3 * 2 - 170, 92, 60},          // BIRD_2
        {SCREEN_WIDTH, SCREEN_HEIGHT / 3 * 2 - 55, 34, 70},           // TREE_MEDIUM_1
        {SCREEN_WIDTH, SCREEN_HEIGHT / 3 * 2 - 55, 34, 70},           // TREE_MEDIUM_2
        {SCREEN_WIDTH, SCREEN_HEIGHT / 3 * 2 - 55, 34, 70},           // TREE_MEDIUM_3
        {SCREEN_WIDTH, SCREEN_HEIGHT / 3 * 2 - 55, 34, 70},           // TREE_MEDIUM_4
        {SCREEN_WIDTH, SCREEN_HEIGHT / 3 * 2 - 55, 34, 70},           // TREE_MEDIUM_5
        {SCREEN_WIDTH, SCREEN_HEIGHT / 3 * 2 - 55, 34, 70},           // TREE_MEDIUM_6
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
    /*
        Check collision algo: https://developer.mozilla.org/en-US/docs/Games/Techniques/2D_collision_detection
     */
    bool checkCollision(SDL_Rect dinoDest, SDL_Rect enemy)
    {
        bool collide = false;

        if (dinoDest.x < enemy.x + enemy.w - TRASH_PIXEL &&
            dinoDest.x + dinoDest.w - TRASH_PIXEL > enemy.x &&
            dinoDest.y < enemy.y + enemy.h - TRASH_PIXEL &&
            dinoDest.h + dinoDest.y - TRASH_PIXEL > enemy.y)
        {
            // collision detected!
            collide = true;
        }
        else
        {
            // no collision
            collide = false;
        }

        return collide;
    }
    void drawScore(context *ctx)
    {
        if(ctx->current_score % 500 == 0) {
            ctx->v += 1;
        }
        UI::showText(ctx->renderer, ctx->font, "HI", UI::getTextColor(), &hiText);
        UI::showText(ctx->renderer, ctx->font, std::to_string(ctx->high_score).c_str(), UI::getTextColor(), &destHighScore);
        UI::showText(ctx->renderer, ctx->font, std::to_string(ctx->current_score).c_str(), UI::getTextColor(), &destCurrentScore);
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
    void drawDinoRunning(context *ctx, float dT, int framesToUpdate)
    {
        if (ctx->jump)
        {
            if (ctx->jumped == true && ctx->dinoDest.y >= objectDestLocation[object::DINO_3].y)
            {
                ctx->jump = false;
                ctx->jumped = false;
                ctx->v_y = V_JUMP;
                ctx->dinoDest = objectDestLocation[object::DINO_3];
                ctx->dinoStatus = DINO_STATUS_RUNNING;
            }
            else
            {

                ctx->dinoDest.y += ctx->v_y;
                // std::cout << ctx->dinoDest.y << " " << ctx->v_y << std::endl;
                if (ctx->dinoDest.y <= 200)
                {
                    ctx->v_y = -V_JUMP;
                }
                // UI::showObject(ctx->renderer, object::DINO_1, &ctx->dinoDest);
                ctx->jumped = true;
                //         // ctx->jump = false;
                ctx->dinoStatus = DINO_STATUS_JUMPING;
            }
        }
        else
        {
            if (framesToUpdate > 0)
            {
                ctx->oddSteps = !ctx->oddSteps;
            }
        }
        for (int i = 0; i < ctx->enemies.size(); i++)
        {
            ctx->gameover |= checkCollision(ctx->dinoDest, ctx->enemies[i].location);
        }
        if (ctx->gameover)
        {
            ctx->isPlaying = false;
            ctx->dinoStatus = DINO_STATUS_DIE;
        }
        switch (ctx->dinoStatus)
        {
        case DINO_STATUS_DIE:
            UI::showObject(ctx->renderer, object::DINO_5, &ctx->dinoDest);
            UI::showObject(ctx->renderer, object::REPLAY);
            UI::showObject(ctx->renderer, object::GAMEOVER);
            break;
        case DINO_STATUS_RUNNING:
            UI::showObject(ctx->renderer, ctx->oddSteps ? object::DINO_3 : object::DINO_4);
            break;
        case DINO_STATUS_JUMPING:
            UI::showObject(ctx->renderer, object::DINO_1, &ctx->dinoDest);
            break;
        }
    }
    void drawEnemy(context *ctx, float dT)
    {
        int framesToUpdate = floor(dT / (1.0f / animatedBirdFPS));
        // std::cout << framesToUpdate << std::endl;
        if (ctx->tick >= ctx->maxTick)
        {
            // add Enemy
            int object = rand() % 13;
            ctx->enemies.push_back(enemy(object + 4, objectDestLocation[object + 4]));
            ctx->tick = 0;
            ctx->maxTick = RANDOM_ENEMY_INTERVAL;
        }
        else
        {
            for (size_t i = 0; i < ctx->enemies.size(); i++)
            {
                if (ctx->enemies[i].location.x + ctx->enemies[i].location.w > 0)
                {
                    ctx->enemies[i].location.x -= ctx->v;
                }
                else
                {
                    ctx->enemies.pop_front();
                }
                if (ctx->enemies[i].enemyObject == object::BIRD_2 || ctx->enemies[i].enemyObject == object::BIRD_1)
                {
                    if (framesToUpdate > 0)
                    {
                        if (ctx->enemies[i].enemyObject == object::BIRD_2)
                        {
                            ctx->enemies[i].enemyObject = object::BIRD_1;
                            ctx->enemies[i].location.y += 12;
                            ctx->enemies[i].location.w = objectDestLocation[object::BIRD_1].w;
                            ctx->enemies[i].location.h = objectDestLocation[object::BIRD_1].h;
                        }
                        else
                        {
                            ctx->enemies[i].enemyObject = object::BIRD_2;
                            ctx->enemies[i].location.y -= 12;
                            ctx->enemies[i].location.w = objectDestLocation[object::BIRD_2].w;
                            ctx->enemies[i].location.h = objectDestLocation[object::BIRD_2].h;
                        }
                        // UI::showObject(ctx->renderer, ctx->enemies[i].enemyObject, &ctx->enemies[i].location);
                    }
                }
                // else
                UI::showObject(ctx->renderer, ctx->enemies[i].enemyObject, &ctx->enemies[i].location);
            }
            ctx->tick++;
        }
    }
    void drawGround(context *ctx)
    {

        if (ctx->groundDest.front().x <= -2400)
        {
            ctx->groundDest.pop();
            ctx->groundDest.push(groundDest2);
        }
        else
        {
            ctx->groundDest.front().x -= ctx->v;
            ctx->groundDest.back().x -= ctx->v;
        };
        UI::showObject(ctx->renderer, object::GROUND, &ctx->groundDest.front());
        UI::showObject(ctx->renderer, object::GROUND, &ctx->groundDest.back());
    }
    void redraw(context *ctx)
    {
        Uint32 current = SDL_GetTicks();
        float dT = (current - ctx->lastUpdate) / 1000.0f;
        int framesToUpdate = floor(dT / (1.0f / animatedDinoFPS));
        SDL_SetRenderDrawColor(ctx->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(ctx->renderer);
        drawScore(ctx);
        drawGround(ctx);
        drawEnemy(ctx, dT);
        drawDinoRunning(ctx, dT, framesToUpdate);
        SDL_RenderPresent(ctx->renderer);
        if (framesToUpdate > 0)
        {
            // object.lastFrame += framesToUpdate;
            // object.lastFrame %= object.numFrames;
            // ctx->current_score++;
            ctx->current_score ++;
            ctx->lastUpdate = current;
        }
    }
} // namespace GamePlay
