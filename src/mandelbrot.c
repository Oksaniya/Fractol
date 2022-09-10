#include "../inc/fractol.h"

void mandelbrot(t_calculation_values *s_calculation_values, t_SDL_struct *s_SDL_struct)
{
    float       x0, y0, x, y, xtemp;
    int64_t     i, e;
    t_pixel     p;
    uint8_t     color_scale;

    x0      =   0.0f;
    y0      =   0.0f;
    x       =   0.0f;
    y       =   0.0f;
    xtemp   =   0.0f;
    i       =   0;
    e       =   0;

    x0 = (float)s_calculation_values->Px * ((X0_CALC_CONST + X0_CONST) / (float)WINDOW_WIDTH) - X0_CALC_CONST;
    y0 = (float)s_calculation_values->Py * ((Y0_CALC_CONST + Y0_CALC_CONST) / (float)WINDOW_HEIGHT) - Y0_CALC_CONST;

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
        color_scale = MAX_RGB_COLOR * (((float)i / (float)MAX_ITER) * BRIGHT_SCALE_MAND);
        p.channel[RED] = color_scale + BRIGHT_RED_MAND;
        p.channel[GREEN] = color_scale + BRIGHT_GREEN_MAND;
        p.channel[BLUE] = color_scale + BRIGHT_BLUE_MAND;
    }
    else
    {
        p.color = 0x00000000;
    }
    set_pixel(s_SDL_struct->surface, s_calculation_values->Px, s_calculation_values->Py, p);
}
