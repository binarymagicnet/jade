#include "../../jade.h"
#include "../sdl2.inc"


MAIN
  /* Variable declarations, SDL2 initialization */
    Init(SDL_INIT_VIDEO);
    DIM AS PWINDOW window;
    DIM AS PRENDERER renderer;
    DIM AS BOOL p1_up = false;
    DIM AS BOOL p1_down = false;
    DIM AS BOOL p2_up = false;
    DIM AS BOOL p2_down = false;

    DIM AS INT p1_y = 199;
    DIM AS INT p2_y = 199;

    DIM AS INT p1_vel = 0;
    DIM AS INT p2_vel = 0;

    DIM AS BOOL quit = false;

    DIM AS INT ball_x = 639 / 2;
    DIM AS INT ball_y = 479 / 2;

    DIM AS INT ball_w = 8;
    DIM AS INT ball_h = 8;

    DIM AS INT ball_x_vel = 5;
    DIM AS INT ball_y_vel = 0;

    DIM AS INT delay = 30;

    DIM AS INT p1_score = 0;
    DIM AS INT p2_score = 0;

    DIM AS INT BALL_WIDTH = 10;
    DIM AS INT BALL_HEIGHT = 10;

    CONSTANT INT Y_MIN = 0;
    CONSTANT INT Y_MAX = 399;

    CONSTANT INT P1_X = 0;
    CONSTANT INT P2_X = 629;

    CONSTANT INT VEL_POS = 10;
    CONSTANT INT VEL_NEG = 0 - VEL_POS;

    window = CreateWindow("Pong",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              640,
                              480,
                              SDL_WINDOW_SHOWN);

    renderer = CreateRenderer(window, -1, 0);

    PRINT("Press Q to quit.");

    /* Main Game Loop */
    WHILE (NOT quit) BEGIN
        EVENT event;

        WHILE (PollEvent(ADDR event)) BEGIN
            SELECT (event.type) BEGIN
                CASE KEYDOWN:
                    SELECT (event.key.keysym.sym) BEGIN
                        CASE SDLK_w:
                          p1_vel = VEL_NEG;
                        ENDCASE

                        CASE SDLK_s:
                          p1_vel = VEL_POS;
                        ENDCASE

                        CASE SDLK_UP:
                          p2_vel = VEL_NEG;
                        ENDCASE

                        CASE SDLK_DOWN:
                          p2_vel = VEL_POS;
                        ENDCASE

                        CASE SDLK_q:
                          quit = true;
                        ENDCASE

                        CASE SDLK_EQUALS:
                          delay++;
                        ENDCASE

                        CASE SDLK_MINUS:
                          IF (delay > 1) delay--;
                        ENDCASE

                        CASE_ELSE:
                        ENDCASE
                    ENDSELECT
                ENDCASE

                CASE KEYUP:
                    SELECT (event.key.keysym.sym) BEGIN

                        CASE SDLK_w:
                          IF (p1_vel == VEL_NEG) p1_vel = 0;
                        ENDCASE

                        CASE SDLK_s:
                          IF (p1_vel == VEL_POS) p1_vel = 0;
                        ENDCASE

                        CASE SDLK_UP:
                          IF (p2_vel == VEL_NEG) p2_vel = 0;
                        ENDCASE

                        CASE SDLK_DOWN:
                          IF (p2_vel == VEL_POS) p2_vel = 0;
                        ENDCASE

                        CASE_ELSE:
                        ENDCASE
                    ENDSELECT
                ENDCASE

                CASE_ELSE:
                ENDCASE

            ENDSELECT
        WEND

        /* Clears the screen */
        SetRenderDrawColor(renderer, 0, 0, 0, 255);
        RenderClear(renderer);
        DIM AS RECT midline = {640/2-4, 0, 9, 479};
        SetRenderDrawColor(renderer, 90, 90, 90, 255);
        RenderDrawRect(renderer, &midline);
        RenderFillRect(renderer, &midline);

        /* Manipulate paddle positions */
        p1_y = p1_y + p1_vel;
        p2_y = p2_y + p2_vel;
        IF (p1_y < Y_MIN) p1_y = Y_MIN;
        IF (p1_y > Y_MAX) p1_y = Y_MAX;
        IF (p2_y < Y_MIN) p2_y = Y_MIN;
        IF (p2_y > Y_MAX) p2_y = Y_MAX;


        /* Draw the paddles */
        SetRenderDrawColor(renderer, 255, 255, 255, 255);
        DIM AS Rect rect1 = {P1_X, p1_y, 10, 80};
        DIM AS Rect rect2 = {P2_X, p2_y, 10, 80};
        RenderDrawRect(renderer, &rect1);
        RenderDrawRect(renderer, &rect2);
        RenderFillRect(renderer, &rect1);
        RenderFillRect(renderer, &rect2);

        /* Manipulate the ball position */
        ball_x = ball_x + ball_x_vel;
        ball_y = ball_y + ball_y_vel;

        IF (ball_x + 4 >= 630 && ball_x <= 639 && ball_y + 4 < p2_y + 80 && ball_y - 4 > p2_y) THEN
            ball_x_vel = -ball_x_vel;
            ball_y_vel = ball_y_vel + (ball_y - (p2_y + 40)) / 10;
            IF (ball_x_vel < 0) ball_x_vel--;
            IF (ball_x_vel > 0) ball_x_vel++;
        ENDIF

        IF (ball_x - 4 <= 9 && ball_x >= 0 && ball_y + 4 < p1_y + 80 && ball_y - 4 > p1_y) THEN
            ball_x_vel = -ball_x_vel;
            ball_y_vel = ball_y_vel + (ball_y - (p1_y + 40)) / 10;
            IF (ball_x_vel < 0 && ball_x_vel > -8) ball_x_vel--;
            IF (ball_x_vel > 0 && ball_x_vel < 8) ball_x_vel++;
        ENDIF

        IF (ball_y - 4 <= 0 OR ball_y + 4 >= 479) THEN
          ball_y_vel = -ball_y_vel;
        ENDIF

        RenderDrawLine(renderer, ball_x, ball_y - 4, ball_x, ball_y + 4);
        RenderDrawLine(renderer, ball_x - 4, ball_y, ball_x + 4, ball_y);

        IF (ball_x < 0) THEN
          p2_score++;
          ball_x = 639 / 2;
          ball_y = 439 / 2;
          ball_x_vel = -6;
          ball_y_vel = 0;
          p1_y = 199;
          p2_y = 199;
        ENDIF

        IF (ball_x > 639) THEN
          p1_score++;
          ball_x = 639 / 2;
          ball_y = 439 / 2;
          ball_x_vel = 6;
          ball_y_vel = 0;
          p1_y = 199;
          p2_y = 199;
        ENDIF

        /* Draw everything to the screen */
        RenderPresent(renderer);

        Delay(delay);
    WEND

    Quit();
    RETURN 0;
ENDMAIN
