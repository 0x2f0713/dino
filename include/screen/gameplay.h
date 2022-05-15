#include "SDL2/SDL.h"
#include "include/ui/ui.h"

#ifndef GAMEPLAY_H
#define GAMEPLAY_H
namespace GamePlay
{
    void redraw(context *ctx);
    void drawScore(context *ctx);
} // namespace GamePlay
#endif