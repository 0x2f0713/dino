
#include <cstdio>
#include <math.h>
// #include "include/object_location.h"
#include "include/constant.h"
#include "include/screen/lobby.h"
#include "include/screen/gameplay.h"
#include "include/ui/ui.h"
int main()
{
  Uint32 start, end, cnt = 0;
  float elapsedMS;
  context ctx = context();
  bool initState = UI::init(&ctx);
  if (initState)
  {
    ctx.object = UI::loadObject(ctx.renderer);
    initScreen(ctx.window, ctx.renderer, ctx.font16);
    SDL_RenderPresent(ctx.renderer);
  }
  else
  {
    ctx.quit = true;
    // Implement logging here
  }
  ctx.lastUpdate = SDL_GetTicks();
  while (!ctx.quit)
  {
    // printf("%d\n", cnt);
    // cnt++;
    start = SDL_GetTicks();
    if (ctx.isPlaying)
    {
      // TODO: Redraw game screen
      GamePlay::redraw(&ctx);
    }

    while (SDL_PollEvent(&(ctx.e)) != 0)
    {
      switch (ctx.e.type)
      {
      case SDL_QUIT:
        // User requests quit
        ctx.quit = true;
        break;
      case SDL_KEYDOWN:
        switch (ctx.e.key.keysym.sym)
        {
        case SDLK_LEFT:
          break;
        case SDLK_RIGHT:
          ctx.isPlaying = true;
          break;
        case SDLK_UP:
          if (ctx.isPlaying)
          {
            ctx.jump = true;
            UI::playPressSound();
          }
          else
          {
            ctx.lastUpdate = SDL_GetTicks();
          }
          if (ctx.gameover)
          {
            ctx.resetContext();
          }
          ctx.isPlaying = true;
          break;
        case SDLK_DOWN:
          ctx.cowering = true;
          break;
        default:
          break;
        }
        break;

      case SDL_KEYUP:
        if (ctx.cowering)
          ctx.cowering = false;
        break;
      case SDL_MOUSEBUTTONDOWN:
        // printf("SDL_MOUSEBUTTONDOWN\n");
        if (ctx.gameover)
        {
          ctx.resetContext();
          ctx.isPlaying = true;
          ctx.lastUpdate = SDL_GetTicks();
        }
      default:
        break;
      }
    }

    end = SDL_GetTicks();

    // elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;

    // Cap to 60 FPS
    // Uint32 delay  = 1000/FPS-end+start;
    if (end - start < 1000 / FPS)
    {
      printf("%zu %zu %zu\n",end, start, 1000 / FPS - (end - start)); 
      if(1000 / FPS - (end - start) < 17) {
        SDL_Delay(1000 / FPS - (end - start));
      }
    }
  }

  UI::destroyWindow(&ctx);

  return 0;
}