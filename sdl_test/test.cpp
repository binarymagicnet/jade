#include "../cppbas.inc"
#include "sdl.inc"

DIM AS CHAR string[128]; // String used by txtIt & SDL_ttf

// Converts Variable Argument(s) into a string
SUB txtIt(CSTRING pStr , ...) BEGIN
    DIM AS va_list valist; // Type to hold information about variable arguments
    va_start(valist, pStr); // Initialize a variable argument list
    vsprintf( string , pStr.c_str() , valist ); // Print formatted variable argument list to string
    va_end(valist); // This macro should be executed before the function
ENDSUB

DIM AS INT FPS = 40;    // Assign a FPS
DIM AS INT NextTick , interval; // Used by FPS_Fn

// Initialize FPS_Fn( )
SUB FPS_Initialize() BEGIN
    NextTick = 0;
    interval = 1 * 1000 / FPS;
ENDSUB

// Frame Per Second Function  , put this in a loop
SUB FPS_Fn() BEGIN
    IF ( NextTick > SDL_GetTicks( ) ) THEN
        SDL_Delay( NextTick - SDL_GetTicks( ) );
    ENDIF
    NextTick = SDL_GetTicks( ) + interval;
ENDSUB

// This function load a image file to a surface
// Set bCKey with colorkey (R,G,B) to clear a color on the image
// Set alpha value FOR transparency 0(No transparent) ~ 255(Ivisible)
FUNCTION PSURFACE ImgLoader(CSTRING file, BOOL bCKey, INT r, INT g, INT b, INT alpha) BEGIN
	DIM AS PSURFACE pic;
	pic = IMG_Load(file.c_str()); // From SDL_image.h , load the image to pic
	IF (pic==NULL) THEN
	    fprintf(stderr,"Missing image %s : %s\n",file.c_str(),IMG_GetError());
	ENDIF
	IF ( bCKey ) THEN
		SDL_SetColorKey(pic,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(pic->format,r,g,b));
 	ENDIF
	IF (alpha) THEN
	    SDL_SetAlpha(pic, SDL_SRCALPHA|SDL_RLEACCEL , 255 - alpha);
	ENDIF
	pic = SDL_DisplayFormat(pic);
	RETURN (pic);
ENDFUNCTION

// Load a normal picture into a surface
FUNCTION PSURFACE ImgLoader(CSTRING file) BEGIN
    RETURN ImgLoader(file.c_str(),1,0,0,0,0);
ENDFUNCTION

// Load a pic & set the transparent color to (255,255,255) , no alpha
FUNCTION PSURFACE ImgLoader(CSTRING file,bool bCKey) BEGIN
    RETURN ImgLoader(file.c_str(),1,255,255,255,0);
ENDFUNCTION


MAIN

    DIM AS TTF_Font *font; // Declare a SDL_ttf font : font
    TTF_Init(); // Initilize SDL_ttf
    font = TTF_OpenFont("./font/cour.ttf",16); // Open a font & set the font size
    DIM AS PSURFACE imgTxt; // Store image of the text FOR blit
    DIM AS RECT txtRect; // Store (x,y) of text FOR blit
    DIM AS COLOR fColor , fColorW , fColorR , fColorG; // Font color (R,G,B)
    txtRect.x = 10;
    txtRect.y = 250;
    fColor.r = fColor.g = fColor.b = 245; // Set font to white color
    fColorW.r = 250;
    fColorW.g = 250;
    fColorW.b = 250;
    fColorR.r = 250;
    fColorR.g = 25;
    fColorR.b = 25;
    fColorG.r = 25;
    fColorG.g = 250;
    fColorG.b = 25;

    DIM AS SDL_Event event; // FOR keyboard event
    DIM AS BOOL bRun = 1; // The SELECT  of WHILE  loop
    // bKeyXXX Present state of keyboard
    DIM AS BOOL bKeyUP = 0 , bKeyDOWN = 0 , bKeyLEFT = 0 , bKeyRIGHT = 0;
    DIM AS INT aTick = 0;
    DIM AS SHORT dx = 2; // The movement value when moving the object anim[ ]
    PSURFACE screen;
    
    ENUM 
        pic1,
        pic_No
    ENDENUM

    DIM AS PSURFACE anim[pic_No];
    DIM AS RECT animRect; // The coordinate of anim[ ]
    animRect.x = 160;
    animRect.y = 160;

    atexit(SDL_Quit);

    IF( SDL_Init(SDL_INIT_VIDEO) < 0 ) EXIT(1);

    SDL_WM_SetCaption("SDL Window - Multiplication Table", NULL);

    screen = SDL_SetVideoMode( 400 , 300 , 32 , SDL_DOUBLEBUF|SDL_HWSURFACE|SDL_ANYFORMAT);

    anim[0] = ImgLoader("./anim/icon.gif");

    FPS_Initialize( );

    DIM AS INT xi=1 , yi=1; // Use FOR display picture

    WHILE (bRun) BEGIN
        aTick++;
        SDL_FillRect(screen , NULL , 0x221122);

        IF ( aTick % 6 == 1) xi++;

        IF ( xi > 9 ) THEN
            xi = 1;
            yi++;
        ENDIF

        IF ( yi > 9 ) yi = 1;

        FOR(INT i=0 TO i < yi STEP i++ ) BEGIN
            animRect.x = 10 + i * 40;
            animRect.y = 200;
            SDL_BlitSurface( anim[0] , NULL , screen , &animRect );
        END

        FOR (INT i=0 TO i < xi STEP i++ ) BEGIN
            animRect.x = 10 + i * 40;
            animRect.y = 240;
            SDL_BlitSurface( anim[0] , NULL , screen , &animRect );
        END

        // A Multiplication Table
        FOR (INT i = 1 TO i <= 9 STEP i++) BEGIN
            FOR( INT j = 1 TO j <= 9 STEP j++) BEGIN
                txtIt("%2d" , i*j );
                fColor = fColorW; // Default is white color
                IF ( i==1 AND j==yi ) fColor = fColorG;
                IF( j==1 AND i==xi ) fColor = fColorG;
                IF( i == xi AND j == yi ) fColor = fColorR;
                imgTxt = TTF_RenderText_Solid( font , string , fColor );
                txtRect.x = 30 + i*30;
                txtRect.y = 30 + j*15;
                SDL_BlitSurface( imgTxt , NULL , screen , &txtRect );
            END 
        END 

        txtIt("%1d %1d %1d %1d", bKeyUP , bKeyDOWN , bKeyLEFT , bKeyRIGHT);
        fColor = fColorW; // Default is white color
        imgTxt = TTF_RenderText_Solid( font , string , fColor );
        SDL_BlitSurface( imgTxt , NULL , screen , NULL );
        SDL_Flip(screen);
        FPS_Fn();

        WHILE ( SDL_PollEvent( &event ) ) BEGIN
            SELECT ( event.type ){
                CASE SDL_KEYDOWN:
                    SELECT ( event.key.keysym.sym ) BEGIN
                        CASE SDLK_UP:
                            bKeyUP = 1;
                        ENDCASE
                        CASE SDLK_DOWN:
                            bKeyDOWN = 1;
                        ENDCASE
                        CASE SDLK_LEFT:
                            bKeyLEFT = 1;
                        ENDCASE
                        CASE SDLK_RIGHT:
                            bKeyRIGHT = 1;
                        ENDCASE
                        CASE SDLK_ESCAPE:
                            bRun = 0;
                        ENDCASE
                        CASE_ELSE:
                        ENDCASE
                    ENDSELECT
                ENDCASE 

                CASE SDL_KEYUP:
                    SELECT ( event.key.keysym.sym ){
                        CASE SDLK_UP:
                            bKeyUP = 0;
                        ENDCASE
                        CASE SDLK_DOWN:
                            bKeyDOWN = 0;
                        ENDCASE
                        CASE SDLK_LEFT:
                            bKeyLEFT = 0;
                        ENDCASE
                        CASE SDLK_RIGHT:
                            bKeyRIGHT = 0;
                        ENDCASE
                        CASE_ELSE:
                        ENDCASE
                    ENDSELECT 
                ENDCASE
                
                CASE SDL_QUIT:
                    bRun = 0;
                ENDCASE
                
                CASE_ELSE:
                ENDCASE
            ENDSELECT
        WEND 

        // Deal with key states
        IF (bKeyUP) animRect.y = animRect.y - dx;
        IF (bKeyDOWN) animRect.y = animRect.y + dx;
        IF (bKeyLEFT) animRect.x = animRect.x - dx;
        IF (bKeyRIGHT) animRect.x = animRect.x + dx;

    WEND


    RETURN 0;
END
