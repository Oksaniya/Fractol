#include "../inc/fractol.h"

void julia(t_mystruct *mystruct, t_SDL_struct *SDL_struct)
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

    x0 = (float)mystruct->Px * ((R + R) / (float)WINDOW_WIDTH) - 2.0f;
    y0 = (float)mystruct->Py * ((R + R) / (float)WINDOW_HEIGHT) - 1.12f;
    
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
    }
    else
    {
        p.color = 0x00000000;
    }
    set_pixel(SDL_struct->surface, mystruct->Px, mystruct->Py, p);
}
