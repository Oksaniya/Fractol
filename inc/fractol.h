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
#define MAX_ITER 1000

//#define MULTITHREAD


#ifndef MULTITHREAD
#define PIX_SET() if_no_multithr(mystruct, thread_id)
#else
#define PIX_SET() if_multithr(mystruct, thread_id)
#endif

#define CLOCK_START  clock_t begin; begin = clock();
#define CLOCK_END clock_t end; end = clock(); 
#define TIME_SPENT double time_spent = (double)(end - begin) / CLOCKS_PER_SEC; printf("time = %f \n", time_spent);


enum window_size
{
    WINDOW_WIDTH = 800,
    WINDOW_HEIGHT = 800,
};

enum colours
{
    BLUE,
    GREEN,
    RED,
    OPACITY,
};

typedef union   s_pixel
{ 
    uint8_t     channel[4];
    uint32_t    color;
}               t_pixel;

typedef struct      s_SDL_struct
{ 
    SDL_Window      *my_window;
    SDL_Event       window_event;
    SDL_Surface		*surface;
}                   t_SDL_struct;

typedef struct      s_mystruct
{
    Uint32          Mouse_pos;
    int             mouse_x;
    int             mouse_y;
    float           Px;
    float           Py;
    uint64_t        numCPU;
    uint64_t        pix_num;
    uint64_t        iterator;
    uint64_t        fract_change;
    char            window_name[10];
    t_SDL_struct    SDL_data;
}                   t_mystruct;

void set_pixel(SDL_Surface *surface, int x, int y, t_pixel pixel);
void init(t_mystruct *mystruct, t_SDL_struct *SDL_struct);
void mandelbrot(t_mystruct *mystruct, t_SDL_struct *SDL_struct);
void *coord_calc(void *my_s);
void julia(t_mystruct *mystruct, t_SDL_struct *SDL_struct);
void zoom(int button, int state, int x, int y);
void if_multithr(t_mystruct *mystruct, pthread_t *thread_id);
void if_no_multithr(t_mystruct *mystruct, pthread_t *thread_id);
void fractol_type_ident(char **argv, t_mystruct *mystruct);
clock_t win_still_and_update(t_mystruct *mystruct);

#endif 