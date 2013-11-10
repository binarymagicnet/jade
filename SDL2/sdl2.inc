#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

typedef SDL_Window* PWINDOW;
typedef SDL_Surface* PSURFACE;
typedef SDL_Renderer* PRENDERER;
typedef SDL_Event EVENT;
typedef SDL_Rect RECT;

#define SetRenderDrawColor SDL_SetRenderDrawColor
#define RenderClear SDL_RenderClear
#define RenderDrawRect SDL_RenderDrawRect
#define RenderFillRect SDL_RenderFillRect
#define RenderDrawLine SDL_RenderDrawLine
#define RenderPresent SDL_RenderPresent
#define Delay SDL_Delay
#define Quit SDL_Quit
#define CreateWindow SDL_CreateWindow
#define CreateRenderer SDL_CreateRenderer
#define PollEvent SDL_PollEvent
#define KEYDOWN SDL_KEYDOWN
#define KEYUP SDL_KEYUP
#define Init SDL_Init
#define Rect SDL_Rect
