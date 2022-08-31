#include "../inc/fractol.h"

void mandelbrot(t_mystruct *mystruct, t_SDL_struct *SDL_struct)
{
    float   x0, y0, x, y, xtemp;
    int64_t     i, e;
    t_pixel p;
    uint8_t color_scale;

    x0 = 0.0f;
    y0 = 0.0f;
    x = 0.0f;
    y = 0.0f;
    xtemp = 0.0f;
    i = 0;
    e = 0;

    x0 = (float)mystruct->Px * ((2.00f + 0.47f) / (float)WINDOW_WIDTH) - 2.0f;
    y0 = (float)mystruct->Py * ((1.12f + 1.12f) / (float)WINDOW_HEIGHT) - 1.12f;

    while (((x * x) + (y * y) <= 4) && (i < MAX_ITER))
    {
        xtemp = (x * x) - (y * y) + x0;
        y = (2 * x * y) + y0;
        x = xtemp;
        i++;
    }
    e++;
    
    if (i < MAX_ITER)
    {
        color_scale = 255 * (((float)i / (float)MAX_ITER) * 10);
        p.channel[RED] = color_scale + 20;
        p.channel[GREEN] = color_scale + 40;
        p.channel[BLUE] = color_scale + 80;
    }
    else
    {
        p.color = 0x00000000;
    }
    set_pixel(SDL_struct->surface, mystruct->Px, mystruct->Py, p);
}
