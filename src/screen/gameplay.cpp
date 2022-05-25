#include "SDL2/SDL.h"
#include "math.h"
#include <queue>
#include <iostream>

#include "include/constant.h"
#include "include/object_location.h"
#include "include/ui/ui.h"

namespace GamePlay
{
    float animatedDinoFPS = 10.0f;
    float animatedBirdFPS = 9.0f;
    SDL_Rect hiText = {SCREEN_WIDTH / 2 + 300, SCREEN_HEIGHT / 2 - 250, 0, 0};
    SDL_Rect destHighScore = {SCREEN_WIDTH / 2 + 400, SCREEN_HEIGHT / 2 - 250, 0, 0};
    SDL_Rect destCurrentScore = {SCREEN_WIDTH / 2 + 400, SCREEN_HEIGHT / 2 - 200, 0, 0};
    const SDL_Rect groundDest2 = {2400, SCREEN_HEIGHT / 3 * 2 - 9, 2400, 24};
    // SDL_Rect objectSrcLocation[28] = {
    //     {0, 0, 73, 65},     // REPLAY
    //     {76, 6, 90, 90},    // DINO_NORMAL
    //     {166, 2, 92, 27},   // CLOUD
    //     {954, 29, 381, 21}, // GAMEOVER
    //     {260, 15, 92, 67},  // BIRD_1
    //     {352, 2, 92, 60},   // BIRD_2
    //     {446, 2, 34, 70},   // TREE_MEDIUM_1
    //     {480, 2, 34, 70},   // TREE_MEDIUM_2
    //     {514, 2, 34, 70},   // TREE_MEDIUM_3
    //     {548, 2, 34, 70},   // TREE_MEDIUM_4
    //     {582, 2, 34, 70},   // TREE_MEDIUM_5
    //     {616, 2, 34, 70},   // TREE_MEDIUM_6
    //     // {650, 2, 34, 70},
    //     {652, 2, 50, 100},   // TREE_BIG_1
    //     {702, 2, 50, 100},   // TREE_BIG_2
    //     {752, 2, 50, 100},   // TREE_BIG_3
    //     {802, 2, 50, 100},   // TREE_BIG_4
    //     {850, 2, 102, 100},  // TREE_BIG_5
    //     {1338, 2, 88, 94},   // DINO_1
    //     {1426, 2, 88, 94},   // DINO_2
    //     {1514, 2, 88, 94},   // DINO_3
    //     {1602, 2, 88, 94},   // DINO_4
    //     {1782, 2, 88, 94},   // DINO_5
    //     {1866, 36, 118, 60}, // DINO_6
    //     {1984, 36, 118, 60}, // DINO_7
    //     {2, 104, 2400, 24}   // GROUND
    // };
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
        UI::showText(ctx->renderer, ctx->font24, "HI", UI::getTextColor(), &hiText);
        UI::showText(ctx->renderer, ctx->font24, std::to_string(ctx->high_score).c_str(), UI::getTextColor(), &destHighScore);
        UI::showText(ctx->renderer, ctx->font24, std::to_string(ctx->current_score).c_str(), UI::getTextColor(), &destCurrentScore);
    }
    void drawReplay(context *ctx)
    {
        UI::showObject(ctx->renderer, object::REPLAY);
    }
    // void drawTest(context *ctx)
    // {
    //     for (auto i = 0; i < 28; i++)
    //     {
    //         UI::showObject(ctx->renderer, i);
    //     }
    // }
    void drawClouds(context *ctx)
    {
        if (ctx->cloudTick >= ctx->maxCloudTick)
        {
            // add Enemy
            int object = rand() % 13;
            SDL_Rect dest = objectDestLocation[object::CLOUD];
            dest.y += rand() % 50;
            ctx->clouds.push_back(dest);
            ctx->cloudTick = 0;
            ctx->maxCloudTick = RANDOM_CLOUD_INTERVAL;
        }
        else
        {
            for (size_t i = 0; i < ctx->clouds.size(); i++)
            {
                if (ctx->clouds[i].x + ctx->clouds[i].w > 0)
                {
                    ctx->clouds[i].x -= ctx->v;
                }
                else
                {
                    ctx->clouds.pop_front();
                }
                // else
                UI::showObject(ctx->renderer, object::CLOUD, &ctx->clouds[i]);
            }
            ctx->cloudTick++;
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
            if (ctx->jumping == true && ctx->dinoDest.y >= objectDestLocation[object::DINO_3].y)
            {
                ctx->jump = false;
                ctx->jumping = false;
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
                    // ctx->v_y = -V_JUMP;
                    ctx->v_y = 2; // Reset v_y
                    UI::playPressSound();
                }
                // UI::showObject(ctx->renderer, object::DINO_1, &ctx->dinoDest);
                ctx->jumping = true;
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
            UI::playHitSound();
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
        if (ctx->enemyTick >= ctx->maxEnemyTick)
        {
            // add Enemy
            int object = rand() % 13;
            ctx->enemies.push_back(enemy(object + 4, objectDestLocation[object + 4]));
            ctx->enemyTick = 0;
            ctx->maxEnemyTick = RANDOM_ENEMY_INTERVAL;
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
            ctx->enemyTick++;
        }
    }
    void drawGround(context *ctx)
    {

        if (ctx->groundDest.front().x <= -2400)
        {
            ctx->groundDest.pop_front();
            ctx->groundDest.push_back(groundDest2);
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
        drawClouds(ctx);
        drawScore(ctx);
        drawGround(ctx);
        drawEnemy(ctx, dT);
        drawDinoRunning(ctx, dT, framesToUpdate);
        SDL_RenderPresent(ctx->renderer);
        if (framesToUpdate > 0)
        {
            // std::cout << ctx->current_score << std::endl;
            if (ctx->jumping)
            {
                ctx->v_y += ACCELERATION;
            }
            ctx->current_score++;
            if (ctx->current_score % 100 == 0 && ctx->current_score > 0)
            {
                ctx->v += 1;
                UI::playReachedSound();
            }
            ctx->lastUpdate = current;
        }
    }
} // namespace GamePlay
