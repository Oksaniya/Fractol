#ifndef FRACTOL_H
#define FRACTOL_H

#include <SDL2/SDL.h>
#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include "../my_stdlib/header/my_stdlib.h"

#define TRUE 1
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

#define RED 2
#define GREEN 1
#define BLUE 0
#define OPACITY 3

#define MAX_ITER 1000

//#define MULTITHREAD

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
    int             numCPU;
    int             pix_num;
    int             iterator;
    int             mouse_x;
    int             mouse_y;
    Uint32          Mouse_pos;
    int             fract_change;
}                   t_mystruct;

void set_pixel(SDL_Surface *surface, int x, int y, t_pixel pixel);
void init(t_mystruct *mystruct);
void surface(t_mystruct *mystruct, t_pixel *pixel);
void mandelbrot(t_mystruct *mystruct, int Px, int Py);
void *coord_calc(void *my_s);
void julia(t_mystruct *mystruct, int Px, int Py);
void zoom(int button, int state, int x, int y);

#endif 