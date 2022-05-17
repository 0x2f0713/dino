
#include <iostream>

#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "include/constant.h"
#include "include/object_location.h"

#include "include/ui/ui.h"

namespace UI
{
    SDL_Texture *objectSrc;
    bool init(context *ctx)
    {
        return initWindow(ctx) && initTTF() && initIMGLoader() && loadFont(ctx->font);
    }
    bool initWindow(context *ctx)
    {
        // Initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            // TODO: Implement log here
            return false;
        }
        else
        {
            int result = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT,
                                                     SDL_WINDOW_SHOWN, &(ctx->window),
                                                     &(ctx->renderer));
            if (ctx->window == NULL || ctx->renderer == NULL || result != 0)
            {
                std::cout << "Failed to create window and renderer: " << SDL_GetError()
                          << std::endl;
                return false;
            }
        }
        return true;
    }

    bool initTTF()
    {
        if (TTF_Init() < 0)
        {
            SDL_Log("%s", TTF_GetError());
            return false;
        }
        return true;
    }
    bool loadFont(TTF_Font *&font)
    {
        font = TTF_OpenFont("resources/fonts/PressStart2P-Regular.ttf", 24);
        if (!font)
        {
            SDL_LogError(1, "Failed to load font: %s", TTF_GetError());
            return false;
        }
        return true;
    }
    bool initIMGLoader()
    {
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags))
        {
            printf("SDL_image could not initialize! SDL_image Error: %s\n",
                   IMG_GetError());
            return false;
        }
        return true;
    }

    void destroyWindow(context *ctx)
    {
        SDL_DestroyWindow(ctx->window);

        // Quit SDL subsystems
        SDL_Quit();
    }

    SDL_Texture *loadMedia(std::string mediaPath, SDL_Renderer *renderer)
    {
        SDL_Texture *tmpTexture = nullptr;

        // Load image at specified path
        SDL_Surface *loadedSurface = IMG_Load(mediaPath.c_str());
        if (loadedSurface == NULL)
        {
            printf("Unable to load image %s! SDL_image Error: %s\n", mediaPath.c_str(),
                   IMG_GetError());
        }
        else
        {
            // Convert surface to screen format
            tmpTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
            if (tmpTexture == NULL)
            {
                printf("Can not create texture from surface. %s\n", mediaPath.c_str(),
                       SDL_GetError());
            }

            // Get rid of old loaded surface
            SDL_FreeSurface(loadedSurface);
        }

        return tmpTexture;
    }

    bool showText(SDL_Renderer *renderer, TTF_Font *font, char const *text, SDL_Color color, SDL_Rect *dst_rect)
    {

        SDL_Surface *textSurface;

        textSurface = TTF_RenderText_Solid(font, text, color);
        if (!textSurface)
        {
            SDL_LogError(1, "Failed to render text: %s", TTF_GetError());
        }
        dst_rect->w = textSurface->w;
        dst_rect->h = textSurface->h;
        SDL_Texture *text_texture;
        text_texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (SDL_RenderCopy(renderer, text_texture, NULL, dst_rect) != 0)
        {
            SDL_LogError(1, "Failed to render copy: %s", SDL_GetError());
            return false;
        }
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(text_texture);
        // SDL_RenderPresent(renderer);
        return true;
    }

    void updateSurface(SDL_Surface *src, SDL_Surface *des, int x, int y, int w,
                       int h)
    {
        SDL_Rect offset;
        offset.x = x;
        offset.y = y;
        offset.w = w;
        offset.h = h;
        // SDL_BlitSurface(src, NULL, des, &offset);
        SDL_BlitScaled(src, NULL, des, &offset);
    }

    void updateRenderer()
    {
        // SDL_RenderPresent( renderer );
    }

    SDL_Color getTextColor()
    {
        SDL_Color color = {83,83,83};
        return color;
    }
    SDL_Texture *loadObject(SDL_Renderer *renderer)
    {
        UI::objectSrc = UI::loadMedia("resources/images/offline-sprite-2x.png", renderer);
        return UI::objectSrc;
        // SDL_Rect image_src = {0, 0, 100, 100};
        // SDL_Rect image_dest = {160, SCREEN_HEIGHT / 3 * 2 - 160, 160, 160};
        // SDL_RenderCopy(renderer, texture, NULL, &image_dest);
    }
    void showObject(SDL_Renderer *renderer, int objectIndex)
    {
        SDL_RenderCopy(renderer, objectSrc, &objectSrcLocation[objectIndex], &objectDestLocation[objectIndex]);
        // SDL_RenderPresent(renderer);
    }
    void showObject(SDL_Renderer *renderer, int objectIndex, SDL_Rect *dst_rect)
    {
        SDL_RenderCopy(renderer, objectSrc, &objectSrcLocation[objectIndex], dst_rect);
    }
} // namespace UI
