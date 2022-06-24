#include "../inc/fractol.h"

void mandelbrot(SDL_Window *window, SDL_Surface *surface, t_pixel *pixel)
{
    float x0, y0, x, y, xtemp;
    int i, e;
    t_pixel p;

    pixel = NULL;
    x0 = 0.0f;
    y0 = 0.0f;
    x = 0.0f;
    y = 0.0f;
    i = 0;
    e = 0;

    for (int Py = 0; Py < WINDOW_HEIGHT; Py++)
    {
        for (int Px = 0; Px < WINDOW_WIDTH; Px++)
        {
            x0 = (float)Px * ((2.00f + 0.47f) / (float)WINDOW_WIDTH) - 2.0f;
            y0 = (float)Py * ((1.12f + 1.12f) / (float)WINDOW_HEIGHT) - 1.12f;
           // x0 = 1.5f * (float)(Px - 375) / 750 - 0.7;
           // y0 = (float)(Py - 250) / 500;
            i = 0;
            x = 0.0f;
            y = 0.0f;
            //printf("x0 = %f\ty0 = %f\n\n", x0, y0);
            while (((x * x) + (y * y) <= 4) && (i < MAX_ITER))
            {
                xtemp = (x * x) - (y * y) + x0;
                y = (2 * x * y) + y0;
                x = xtemp;
                //printf("x = %f\ty = %f\tx2 + y2 = %f\ti = %d\n", x, y, (x * x + y * y), i);
                i++;
            }
            e++;
            
            if (i < MAX_ITER)
            {
                p.color = 0xffffffff;
            }
            else
            {
                p.color = 0x00000000;
            }
            set_pixel(surface, Px, Py, p);
        }
    }
    SDL_UpdateWindowSurface(window);
}
