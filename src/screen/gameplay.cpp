#include "SDL2/SDL.h"
#include "include/ui/ui.h"
#include "include/constant.h"

SDL_Rect groundDest = {0, SCREEN_HEIGHT / 3 * 2 - 170, 2400, 24};
namespace GamePlay
{
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
            UI::showObject(ctx->renderer,i);
        }
        
    }
    void drawDinoNormal(context *ctx)
    {
        UI::showObject(ctx->renderer, object::DINO_NORMAL);
    }
    void drawDinoRunning(context *ctx)
    {
        UI::showObject(ctx->renderer, ctx->oddSteps ? object::DINO_3 : object::DINO_4);
        ctx->oddSteps = !ctx->oddSteps;
    }
    void drawGround(context *ctx)
    {
        UI::showObject(ctx->renderer,object::GROUND);
    }
    void redraw(context *ctx)
    {
        SDL_SetRenderDrawColor(ctx->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(ctx->renderer);
        drawScore(ctx);
        drawGround(ctx);
        drawDinoRunning(ctx);
        SDL_RenderPresent(ctx->renderer);
    }
} // namespace GamePlay
