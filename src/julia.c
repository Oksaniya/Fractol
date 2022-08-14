#include "../inc/fractol.h"

void julia(t_mystruct *mystruct, t_SDL_struct *SDL_struct, int Px, int Py)
{
    float       x0, y0, x, y, xtemp, R;
    uint64_t    i;
    t_pixel     p;
    uint8_t     color_scale;
    float       color_scale_f;

    R = 1.5f;
    x0 = 0.0f;
    y0 = 0.0f;
    x = -0.4f;
    y = 0.6f;
    i = 0;
    color_scale_f = 0.0f;

    // choose R > 0 such that R**2 - R >= sqrt(cx**2 + cy**2)

    x0 = (float)Px * ((R + R) / (float)WINDOW_WIDTH) - 2.0f;
    y0 = (float)Py * ((R + R) / (float)WINDOW_HEIGHT) - 1.12f;
   // printf("Mouse pos x = %d, \n", mystruct->mouse_x);
    if (((R * R - R) * (R * R - R) < x * x + y * y) || (R < 0))
    {
        printf("Please, choose another value of R in julia.c. It should be not %f \n", R);
        exit(1);
    }
    while ((((x0 * x0) + (y0 * y0)) < (R * R)) && (i < MAX_ITER)) 
    {
        xtemp = (x0 * x0) - (y0 * y0) + (-0.7f) + mystruct->mouse_x/1000.0f;
        y0 = (2 * x0 * y0) + 0.27015f + mystruct->mouse_y/1000.0f; 
        x0 = (xtemp + x);
        i++;
    }
    
    if (i < MAX_ITER)
    {
        color_scale = 255 * (((float)i / (float)MAX_ITER) * 50);
        p.channel[RED] = color_scale + 0;
        p.channel[GREEN] = color_scale + 10;
        p.channel[BLUE] = color_scale + 60;
        //p.color = (uint32_t)((float)0xffffffff * (((float)i / (float)MAX_ITER)));
    }
    else
    {
        p.color = 0x00000000;
    }
    // color_scale_f = (float)i / (float)MAX_ITER;
    // if (color_scale_f < 0.33f)
    // {
    //     p.channel[RED] = color_scale_f * 255.f + 20;
    //     p.channel[GREEN] = 0;
    //     p.channel[BLUE] = 0;
    // }
    // else if ((color_scale_f >= 0.33f) && (color_scale_f < 0.66f))
    // {
    //     p.channel[RED] = color_scale_f * 255.f + 30;
    //     p.channel[GREEN] = color_scale_f * 255.f + 40;
    //     p.channel[BLUE] = 0;
    // }
    // else if ((color_scale_f >= 0.66f) && (color_scale_f < 1))
    // {
    //     p.channel[RED] = color_scale_f * 255.f + 50;
    //     p.channel[GREEN] = color_scale_f * 255.f + 60;
    //     p.channel[BLUE] = color_scale_f * 255.f + 70;
    // }
    // else
    // {
    //     p.color = 0x00000000;
    // }
    set_pixel(SDL_struct->surface, Px, Py, p);
}
