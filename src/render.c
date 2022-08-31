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
    int32_t i;
    int64_t increment;
    t_mystruct *mystruct;
    t_SDL_struct SDL_struct;

    mystruct = (t_mystruct *)my_s;
    SDL_struct = mystruct->SDL_data;
    mystruct->Px = 0.0f;
    mystruct->Py = 0.0f;
    mystruct = my_s;
    i = mystruct->iterator * (WINDOW_WIDTH * WINDOW_HEIGHT / mystruct->numCPU);
    increment = mystruct->numCPU;
    while (i < mystruct->pix_num)
    {
        mystruct->Py = i / WINDOW_WIDTH;
        mystruct->Px = i % WINDOW_WIDTH;

        switch (mystruct->fract_change)
        {
        case 0:
            mandelbrot(mystruct, &SDL_struct);
            break;
        case 1:
            julia(mystruct, &SDL_struct);
        default:
            break;
        }

        i += increment;
    }
    return NULL;
}

clock_t win_still_and_update(t_mystruct *mystruct)
{
    int64_t mouse_x_prev, mouse_y_prev;
    
    mouse_x_prev = 0;
    mouse_y_prev = 0;
    pthread_t       *thread_id;

    thread_id = (pthread_t *)malloc(sizeof(pthread_t) * mystruct->numCPU);

    PIX_SET();
    CLOCK_END;
    while (TRUE)
    {
        mystruct->Mouse_pos = SDL_GetMouseState(&mystruct->mouse_x, &mystruct->mouse_y);
        if (mystruct->mouse_x != mouse_x_prev || mystruct->mouse_y != mouse_y_prev)
        {
            PIX_SET();

            SDL_UpdateWindowSurface(mystruct->SDL_data.my_window);
            mouse_x_prev = mystruct->mouse_x;
            mouse_y_prev = mystruct->mouse_y;
        }
        if (SDL_PollEvent(&(mystruct->SDL_data.window_event)))
        {
            if (SDL_QUIT == mystruct->SDL_data.window_event.type)
            {
                break ;
            }
        }
    }
    return end;
}