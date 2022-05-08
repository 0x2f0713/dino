#include "include/ui/ui.h"
#include "include/screen/lobby.h"
#include <cstdio>

int main()
{
  context ctx = context();
  bool initState = UI::init(&ctx);
  if (initState)
  {
    initScreen(ctx.window, ctx.renderer, ctx.font);
  }
  else
  {
    ctx.quit = true;
    // Implement logging here
  }
  while (!ctx.quit)
  {
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
          printf("LEFT\n");
          break;
        case SDLK_RIGHT:
          printf("RIGHT\n");
          break;
        case SDLK_UP:
          printf("UP\n");
          break;
        case SDLK_DOWN:
          printf("DOWN\n");
          break;
        default:
          break;
        }
        break;

      case SDL_KEYUP:
        printf("Key release detected\n");
        break;
      default:
        break;
      }
    }
  }

  UI::destroyWindow(&ctx);

  return 0;
}