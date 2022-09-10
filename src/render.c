#include "../inc/fractol.h"

void set_pixel(SDL_Surface *surface, int x, int y, t_pixel pixel)
{
  Uint32 * const target_pixel = (Uint32 *) ((Uint8 *) surface->pixels
                                             + y * surface->pitch
                                             + x * surface->format->BytesPerPixel);
  *target_pixel = pixel.color;
}

void *coord_calc(void *my_s)
{
    int32_t                 i;
    int64_t                 increment;
    t_calculation_values    *s_calculation_values;
    t_SDL_struct            s_SDL_struct;

    s_calculation_values = (t_calculation_values *)my_s;
    s_SDL_struct = s_calculation_values->SDL_data;
    s_calculation_values->Px = 0.0f;
    s_calculation_values->Py = 0.0f;
    s_calculation_values = my_s;
    increment = s_calculation_values->struct_iterators.numCPU;

    i = s_calculation_values->struct_iterators.iterator * 
        (WINDOW_WIDTH * WINDOW_HEIGHT / s_calculation_values->struct_iterators.numCPU);

    while (i < s_calculation_values->struct_iterators.pix_num)
    {
        s_calculation_values->Py = i / WINDOW_WIDTH;
        s_calculation_values->Px = i % WINDOW_WIDTH;

        switch (s_calculation_values->struct_iterators.fract_change)
        {
        case 0:
            mandelbrot(s_calculation_values, &s_SDL_struct);
            break;
        case 1:
            julia(s_calculation_values, &s_SDL_struct);
        default:
            break;
        }

        i += increment;
    }
    return NULL;
}

clock_t window_update(t_calculation_values *s_calculation_values)
{
    int64_t         mouse_x_prev, mouse_y_prev;
    pthread_t       *thread_id;
    
    mouse_x_prev    =   0;
    mouse_y_prev    =   0;


    thread_id = (pthread_t *)malloc(sizeof(pthread_t) * s_calculation_values->struct_iterators.numCPU);

    PIX_SET();
    CLOCK_END;
    while (TRUE)
    {
        s_calculation_values->Mouse_pos = SDL_GetMouseState(&s_calculation_values->mouse_x, &s_calculation_values->mouse_y);
        if (s_calculation_values->mouse_x != mouse_x_prev || s_calculation_values->mouse_y != mouse_y_prev)
        {
            PIX_SET();
            SDL_UpdateWindowSurface(s_calculation_values->SDL_data.my_window);
            mouse_x_prev = s_calculation_values->mouse_x;
            mouse_y_prev = s_calculation_values->mouse_y;
        }
        if (SDL_PollEvent(&(s_calculation_values->SDL_data.window_event)))
        {
            if (SDL_QUIT == s_calculation_values->SDL_data.window_event.type)
            {
                break ;
            }
        }
    }
    return end;
}