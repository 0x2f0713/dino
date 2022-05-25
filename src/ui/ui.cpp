
#include <iostream>
#include <cstdio>

#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"
#include "include/constant.h"
#include "include/object_location.h"

#include "include/ui/ui.h"

SDL_Rect objectSrcLocation[28] = {
    {0, 0, 73, 65},     // REPLAY
    {76, 6, 90, 90},    // DINO_NORMAL
    {166, 2, 92, 27},   // CLOUD
    {954, 29, 381, 21}, // GAMEOVER
    {260, 15, 92, 67},  // BIRD_1
    {352, 2, 92, 60},   // BIRD_2
    {446, 2, 34, 70},   // TREE_MEDIUM_1
    {480, 2, 34, 70},   // TREE_MEDIUM_2
    {514, 2, 34, 70},   // TREE_MEDIUM_3
    {548, 2, 34, 70},   // TREE_MEDIUM_4
    {582, 2, 34, 70},   // TREE_MEDIUM_5
    {616, 2, 34, 70},   // TREE_MEDIUM_6
    // {650, 2, 34, 70},
    {652, 2, 50, 100},   // TREE_BIG_1
    {702, 2, 50, 100},   // TREE_BIG_2
    {752, 2, 50, 100},   // TREE_BIG_3
    {802, 2, 50, 100},   // TREE_BIG_4
    {850, 2, 102, 100},  // TREE_BIG_5
    {1338, 2, 88, 94},   // DINO_1
    {1426, 2, 88, 94},   // DINO_2
    {1514, 2, 88, 94},   // DINO_3
    {1602, 2, 88, 94},   // DINO_4
    {1782, 2, 88, 94},   // DINO_5
    {1866, 36, 118, 60}, // DINO_6
    {1984, 36, 118, 60}, // DINO_7
    {2, 104, 2400, 24}   // GROUND
};
SDL_Rect objectDestLocation[28] = {
    {CENTER_HORIZONTAL(73), CENTER_VERTICAL(65), 73, 65},         // REPLAY
    {160, SCREEN_HEIGHT / 3 * 2 - 80, 90, 90},                                              // DINO_NORMAL
    {SCREEN_WIDTH, SCREEN_HEIGHT / 3, 92, 27},                                             // CLOUD
    {CENTER_HORIZONTAL(381), CENTER_VERTICAL(21) - 100, 381, 21}, // GAMEOVER
    {SCREEN_WIDTH, SCREEN_HEIGHT / 3 * 2 - 170, 92, 67},          // BIRD_1
    {SCREEN_WIDTH, SCREEN_HEIGHT / 3 * 2 - 170, 92, 60},          // BIRD_2
    {SCREEN_WIDTH, SCREEN_HEIGHT / 3 * 2 - 55, 34, 70},           // TREE_MEDIUM_1
    {SCREEN_WIDTH, SCREEN_HEIGHT / 3 * 2 - 55, 34, 70},           // TREE_MEDIUM_2
    {SCREEN_WIDTH, SCREEN_HEIGHT / 3 * 2 - 55, 34, 70},           // TREE_MEDIUM_3
    {SCREEN_WIDTH, SCREEN_HEIGHT / 3 * 2 - 55, 34, 70},           // TREE_MEDIUM_4
    {SCREEN_WIDTH, SCREEN_HEIGHT / 3 * 2 - 55, 34, 70},           // TREE_MEDIUM_5
    {SCREEN_WIDTH, SCREEN_HEIGHT / 3 * 2 - 55, 34, 70},           // TREE_MEDIUM_6
    // {650, 2, 34, 70},
    {SCREEN_WIDTH, SCREEN_HEIGHT / 3 * 2 - 79, 50, 100},  // TREE_BIG_1
    {SCREEN_WIDTH, SCREEN_HEIGHT / 3 * 2 - 79, 50, 100},  // TREE_BIG_2
    {SCREEN_WIDTH, SCREEN_HEIGHT / 3 * 2 - 79, 50, 100},  // TREE_BIG_3
    {SCREEN_WIDTH, SCREEN_HEIGHT / 3 * 2 - 79, 50, 100},  // TREE_BIG_4
    {SCREEN_WIDTH, SCREEN_HEIGHT / 3 * 2 - 79, 102, 100}, // TREE_BIG_5
    {160, SCREEN_HEIGHT / 3 * 2 - 80, 88, 94},            // DINO_1
    {1426, 2, 88, 94},                                    // DINO_2
    {160, SCREEN_HEIGHT / 3 * 2 - 80, 88, 94},
    {160, SCREEN_HEIGHT / 3 * 2 - 80, 88, 94},
    // {1514, 2, 88, 94},      // DINO_3
    // {1602, 2, 88, 94},      // DINO_4
    {1782, 2, 88, 94},                       // DINO_5
    {1866, 36, 118, 60},                     // DINO_6
    {1984, 36, 118, 60},                     // DINO_7
    {0, SCREEN_HEIGHT / 3 * 2 - 9, 2400, 24} // GROUND
};

namespace UI
{
    SDL_Texture *objectSrc;
    Mix_Music *soundHit, *soundPress, *soundReached;
    bool init(context *ctx)
    {
        bool res;
        res =  initWindow(ctx) && initTTF() && initIMGLoader() && initMixer() && loadSoundEffect() && loadFont(ctx->font16, 16) && loadFont(ctx->font24, 24);
        return res;
    }
    bool initWindow(context *ctx)
    {
        // Initialize SDL
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
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
    bool loadFont(TTF_Font *&font, int size)
    {
        font = TTF_OpenFont("resources/fonts/PressStart2P-Regular.ttf", size);
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
    bool initMixer()
    {
        int flags = MIX_INIT_OGG;
        if (flags != Mix_Init(flags))
        {
            printf("Could not initialize mixer.\n");
            printf("Mix_Init: %s\n", Mix_GetError());
            return false;
        }

        if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 1, 4096) == -1)
        {
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
    bool loadSoundEffect()
    {
        soundHit = Mix_LoadMUS("resources/sounds/sound-hit.ogx");
        soundPress = Mix_LoadMUS("resources/sounds/sound-press.ogx");
        soundReached = Mix_LoadMUS("resources/sounds/sound-reached.ogx");
        if ((soundHit == NULL) || (soundPress == NULL) || (soundReached == NULL))
        {
            return false;
        }
        return true;
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
        SDL_Color color = {83, 83, 83};
        return color;
    }
    int playPressSound() {
        return Mix_PlayMusic(soundPress, 1);
    }
    int playHitSound() {
        return Mix_PlayMusic(soundHit, 1);
    }
    int playReachedSound() {
        return Mix_PlayMusic(soundReached, 1);
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
