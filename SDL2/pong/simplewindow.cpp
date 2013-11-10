#include "../jade.h"
#include "sdl2.inc"

// SCREEN DIMENSIONS
CONSTANT INT SCREEN_WIDTH = 640;
CONSTANT INT SCREEN_HEIGHT = 480;

MAIN
    DIM AS PWINDOW window = NULL;
    DIM AS PSURFACE screenSurface = NULL;
    DIM AS BOOL quit = false;
    DIM AS SDL_Event e;
    
    IF ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) THEN
        PRINT( SDL_GetError() );
    ELSE
        //Create Window
        window = SDL_CreateWindow( "SDL Simple Window",
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SCREEN_WIDTH,
                                    SCREEN_HEIGHT,
                                    SDL_WINDOW_SHOWN);
        
        IF ( window == NULL ) THEN
            PRINT( SDL_GetError() );
        ELSE
            // Get Window Surface
            screenSurface = SDL_GetWindowSurface( window );

            
            WHILE (NOT quit) BEGIN
                WHILE ( SDL_PollEvent( ADDR e) != 0 ) BEGIN
                    SELECT (e.type) BEGIN
                        CASE SDL_QUIT:
                            quit = true;
                        ENDCASE
                    ENDSELECT
                WEND
                // Fill the surface with White
                SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 255, 255, 255 ) );
                // Update the Surface
                SDL_UpdateWindowSurface( window );
            
            WEND
        ENDIF
    ENDIF
    
    //Destroy Window
    SDL_DestroyWindow( window );
    
    // Shutdown SDL
    SDL_Quit();
    
    RETURN 0;
    
END