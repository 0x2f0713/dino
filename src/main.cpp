
#include <cstdio>
#include <math.h>
// #include "include/object_location.h"

#include "include/screen/lobby.h"
#include "include/screen/gameplay.h"
int main()
{
  context ctx = context();
  bool initState = UI::init(&ctx);
  if (initState)
  {
    initScreen(ctx.window, ctx.renderer, ctx.font);
    SDL_RenderPresent(ctx.renderer);
    ctx.object = UI::loadObject(ctx.renderer);
  }
  else
  {
    ctx.quit = true;
    // Implement logging here
  }
  ctx.lastUpdate = SDL_GetTicks();
  while (!ctx.quit)
  {
    Uint64 start = SDL_GetPerformanceCounter();
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
          // alien_x -= 1;
          // printf("LEFT\n");
          break;
        case SDLK_RIGHT:
          ctx.isPlaying = true;
          // printf("RIGHT\n");
          break;
        case SDLK_UP:
          // printf("UP\n");
          if (ctx.isPlaying)
          {
            ctx.jump = true;
            ctx.v_y = V_JUMP;
          }
          ctx.isPlaying = true;

          break;
        case SDLK_DOWN:
          // printf("DOWN\n");
          break;
        default:
          break;
        }
        break;

      case SDL_KEYUP:
        // printf("Key release detected\n");
        break;
      default:
        break;
      }
    }

	Uint64 end = SDL_GetPerformanceCounter();

	float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;

	// Cap to 60 FPS
	SDL_Delay(floor(16.666f - elapsedMS));
  }

  UI::destroyWindow(&ctx);

  return 0;
}