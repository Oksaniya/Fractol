#ifndef FRACTOL_H
#define FRACTOL_H

#include <SDL2/SDL.h>
#include "../my_stdlib/header/my_stdlib.h"

#define TRUE 1
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

#define RED 2
#define GREEN 1
#define BLUE 0
#define OPACITY 3

#define MAX_ITER 1000

typedef union   s_pixel
{ 
    uint8_t     channel[4];
    uint32_t    color;
}               t_pixel;

typedef struct      s_mystruct
{ 
    SDL_Window      *my_window;
    SDL_Event       window_event;
    SDL_Surface		*surface;
    char            window_name[10];
}                   t_mystruct;

void set_pixel(SDL_Surface *surface, int x, int y, t_pixel pixel);
void init(t_mystruct *mystruct);
void pix_colour(t_pixel *pixel);
void surface(t_mystruct *mystruct, t_pixel *pixel);
void mandelbrot(SDL_Window *window, SDL_Surface *surface, t_pixel *pixel);


#endif 