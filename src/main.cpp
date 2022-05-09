// #include "include/ui/ui.h"

#include "include/screen/lobby.h"
#include "include/screen/gameplay.h"

#include <cstdio>
#include <math.h>


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
    if (ctx.isPlaying)
    {
      // TODO: Redraw game screen
      GamePlay::redraw(&ctx);
      // ctx.current_score++;
      // ctx.high_score = std::max(ctx.high_score,ctx.current_score);
      // s = std::to_string(ctx.current_score);
      // pchar = s.c_str();
      // UI::showText(ctx.renderer, ctx.font, pchar, UI::getTextColor(), &dest);
      // printf("%i\n", ctx.current_score);
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
          printf("LEFT\n");
          break;
        case SDLK_RIGHT:
          ctx.isPlaying = true;
          printf("RIGHT\n");
          break;
        case SDLK_UP:
          printf("UP\n");
          ctx.isPlaying = true;
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