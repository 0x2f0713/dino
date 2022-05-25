
#include <map>
#include <string>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "include/ui/ui.h"
#include "include/constant.h"

#include "include/screen/lobby.h"

std::map<std::string, std::string> mediaLists{
    {"DINO-DOWN", "resources/images/object/dino-down.png"},
    {"DINO-UP", "resources/images/object/dino-up.png"}};

void initScreen(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font)
{
  // Fill the window
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(renderer);

  // UI::showObject(renderer, object::DINO_NORMAL);

  // SDL_Texture *texture = UI::loadMedia(mediaLists["DINO-UP"], renderer);
  // SDL_Rect image_src = {0, 0, 100, 100};
  // SDL_Rect image_dest = {160, SCREEN_HEIGHT / 3 * 2 - 160, 160, 160};
  // SDL_RenderCopy(renderer, texture, NULL, &image_dest);

  // SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  // SDL_RenderDrawLine(renderer, 0,SCREEN_HEIGHT / 3 * 2-10,SCREEN_WIDTH, SCREEN_HEIGHT / 3 * 2);
  // // Test write text
  // SDL_Color color = {0, 0, 0};
  // SDL_Rect dest = {SCREEN_WIDTH/2 - 200, SCREEN_HEIGHT/2, 0, 0};
  // UI::showText(renderer, font, "Press Arrow Up button to Play", color, &dest);

  UI::showObject(renderer, object::DINO_NORMAL);
  SDL_Color color = {0, 0, 0};
  SDL_Rect dest = {SCREEN_WIDTH/2 - 300, SCREEN_HEIGHT/2 - 200, 0, 0};
  UI::showText(renderer, font, "Dino Game", color, &dest);

  SDL_Rect dest1 = {SCREEN_WIDTH/2 - 300, SCREEN_HEIGHT/2 - 150, 0, 0};
  UI::showText(renderer, font, "Instruction:", color, &dest1);

  SDL_Rect dest2 = {SCREEN_WIDTH/2 - 300, SCREEN_HEIGHT/2 - 100, 0, 0};
  UI::showText(renderer, font, "- Press Arrow Up button to Play and Jump in Game Play", color, &dest2);

  SDL_Rect dest3 = {SCREEN_WIDTH/2 - 300, SCREEN_HEIGHT/2 - 50, 0, 0};
  UI::showText(renderer, font, "- When game over, click on replay button to play again", color, &dest3);

  SDL_Rect dest4 = {SCREEN_WIDTH/2 - 300, SCREEN_HEIGHT/2, 0, 0};
  UI::showText(renderer, font, "- Close this window to quit the game", color, &dest4);

}
