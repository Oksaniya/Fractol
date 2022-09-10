#include "../inc/fractol.h"

void julia(t_calculation_values *s_calculation_values, t_SDL_struct *s_SDL_struct)
{
    float       x0, y0, xtemp;
    uint64_t    i;
    t_pixel     p;
    uint8_t     color_scale;
    float       color_scale_f;

    x0              =   0.0f;
    y0              =   0.0f;
    i               =   0;
    color_scale_f   =   0.0f;

    x0 = (float)s_calculation_values->Px * ((R_CONST_JULIA + R_CONST_JULIA) / (float)WINDOW_WIDTH) - X0_CALC_CONST;
    y0 = (float)s_calculation_values->Py * ((R_CONST_JULIA + R_CONST_JULIA) / (float)WINDOW_HEIGHT) - Y0_CALC_CONST;
    
    if (((R_CONST_JULIA * R_CONST_JULIA - R_CONST_JULIA) * 
        (R_CONST_JULIA * R_CONST_JULIA - R_CONST_JULIA) < 
        X_START_POS_JUL * X_START_POS_JUL + Y_START_POS_JUL * Y_START_POS_JUL) ||
        (R_CONST_JULIA < 0))
    {
        printf("Please, choose another value of R_CONST_JULIA in julia.c(fractol.h). It should be not %f \n", R_CONST_JULIA);
        exit(1);
    }
    while ((((x0 * x0) + (y0 * y0)) < (R_CONST_JULIA * R_CONST_JULIA)) && (i < MAX_ITER)) 
    {
        xtemp = (x0 * x0) - (y0 * y0) + (X_TEMP_CALC_CONST) + s_calculation_values->mouse_x / DIV_CONST;
        y0 = (2 * x0 * y0) + Y0_CONST + s_calculation_values->mouse_y / DIV_CONST; 
        x0 = (xtemp + X_START_POS_JUL);
        i++;
    }
    
    if (i < MAX_ITER)
    {
        color_scale = MAX_RGB_COLOR * (((float)i / (float)MAX_ITER) * BRIGHT_SCALE_JUL);
        p.channel[RED] = color_scale + BRIGHT_RED_JUL;
        p.channel[GREEN] = color_scale + BRIGHT_GREEN_JUL;
        p.channel[BLUE] = color_scale + BRIGHT_BLUE_JUL;
    }
    else
    {
        p.color = 0x00000000;
    }
    set_pixel(s_SDL_struct->surface, s_calculation_values->Px, s_calculation_values->Py, p);
}
