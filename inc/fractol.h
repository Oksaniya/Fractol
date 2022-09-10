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

//#define MULTITHREAD

#define TRUE                1
#define MAX_ITER            1000
#define MAX_RGB_COLOR       255

#define R_CONST_JULIA       1.5f
#define X_START_POS_JUL     -0.4f
#define Y_START_POS_JUL     0.6f
#define X0_CALC_CONST       2.0f
#define Y0_CALC_CONST       1.12f
#define X0_CONST            0.47f
#define DIV_CONST           1000.0f
#define X_TEMP_CALC_CONST   -0.7f
#define Y0_CONST            0.27015f

#ifndef MULTITHREAD
#define PIX_SET() if_no_multithr(s_calculation_values, thread_id)
#else
#define PIX_SET() if_multithr(s_calculation_values, thread_id)
#endif

#define CLOCK_START  clock_t begin; begin = clock();
#define CLOCK_END clock_t end; end = clock(); 
#define TIME_SPENT double time_spent = (double)(end - begin) / CLOCKS_PER_SEC; printf("time = %f \n", time_spent);

enum mandelbrot_color_scale_bright
{
    BRIGHT_SCALE_MAND   =   10,
    BRIGHT_RED_MAND     =   20,
    BRIGHT_GREEN_MAND   =   40,
    BRIGHT_BLUE_MAND    =   80,
};

enum julia_color_scale_bright
{
    BRIGHT_SCALE_JUL    =   50,
    BRIGHT_RED_JUL      =   0,
    BRIGHT_GREEN_JUL    =   10,
    BRIGHT_BLUE_JUL     =   60,
};

enum enum_window_size
{
    WINDOW_WIDTH        =   800,
    WINDOW_HEIGHT       =   800,
};

enum enum_colours
{
                        BLUE,
                        GREEN,
                        RED,
                        OPACITY,
};

typedef union           u_pixel
{ 
    uint8_t             channel[4];
    uint32_t            color;
}                       t_pixel;

typedef struct          s_SDL_struct
{ 
    SDL_Window          *my_window;
    SDL_Event           window_event;
    SDL_Surface		    *surface;
}                       t_SDL_struct;

typedef struct          s_iterators
{ 
    uint8_t             numCPU;
    uint64_t            pix_num;
    uint64_t            iterator;
    uint8_t             fract_change;
}                       t_iterators;

typedef struct          s_calculation_values
{
    uint64_t            Mouse_pos;
    int                 mouse_x;
    int                 mouse_y;
    float               Px;
    float               Py;
    char                window_name[10];
    t_iterators         struct_iterators;
    t_SDL_struct        SDL_data;
}                       t_calculation_values;


void    set_pixel(SDL_Surface *surface, int x, int y, t_pixel pixel);
void    init(t_calculation_values *s_calculation_values, t_SDL_struct *s_SDL_struct);
void    mandelbrot(t_calculation_values *s_calculation_values, t_SDL_struct *s_SDL_struct);
void    *coord_calc(void *my_s);
void    julia(t_calculation_values *s_calculation_values, t_SDL_struct *s_SDL_struct);
void    zoom(int button, int state, int x, int y);
void    if_multithr(t_calculation_values *s_calculation_values, pthread_t *thread_id);
void    if_no_multithr(t_calculation_values *s_calculation_values, pthread_t *thread_id);
void    fractol_type_ident(char **argv, t_calculation_values *s_calculation_values);
clock_t window_update(t_calculation_values *s_calculation_values);

#endif 