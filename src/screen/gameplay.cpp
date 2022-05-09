#include "SDL2/SDL.h"
#include "include/ui/ui.h"

namespace GamePlay
{
    void redraw(context *ctx)
    {
        std::string s;
        char const *pchar;
        SDL_Rect dest = {0, 0, 0, 0};
        SDL_RenderClear(ctx->renderer);
        ctx->current_score++;
        ctx->high_score = std::max(ctx->high_score, ctx->current_score);
        s = std::to_string(ctx->current_score);
        pchar = s.c_str();
        UI::showText(ctx->renderer, ctx->font, pchar, UI::getTextColor(), &dest);
    }
} // namespace GamePlay
