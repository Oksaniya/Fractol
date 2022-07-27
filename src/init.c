#include "../inc/fractol.h"

void init(t_mystruct *mystruct)
{
    mystruct->my_window = NULL;
    mystruct->pix_num = (WINDOW_HEIGHT * WINDOW_WIDTH);
    mystruct->mouse_x = 0;
    mystruct->mouse_y = 0;
    mystruct->Mouse_pos = 0;
    
    ft_strcpy(mystruct->window_name, "my_window");
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
        exit(1);
    }
    mystruct->my_window = SDL_CreateWindow(mystruct->window_name, 
                                SDL_WINDOWPOS_CENTERED, 
                                SDL_WINDOWPOS_CENTERED, 
                                WINDOW_WIDTH, 
                                WINDOW_HEIGHT, 
                                SDL_WINDOW_ALLOW_HIGHDPI);

    if (mystruct->my_window == NULL)
    {
        fprintf(stderr, "could not create a window: %s\n", SDL_GetError());
        exit(1);
    }
    mystruct->surface = NULL;
    mystruct->surface = SDL_GetWindowSurface(mystruct->my_window);

    /* init surface with 0 */
    SDL_LockSurface(mystruct->surface);
    SDL_memset(mystruct->surface->pixels, 0, mystruct->surface->h * mystruct->surface->pitch);
    SDL_UnlockSurface(mystruct->surface);
    SDL_UpdateWindowSurface(mystruct->my_window);
}

void surface(t_mystruct *mystruct, t_pixel *pixel)
{
    SDL_LockSurface(mystruct->surface);
    for (int64_t x = 300; x < 450; x++)
    {
        for (int64_t y = 175; y < 325; y++)
        {
            set_pixel(mystruct->surface, x, y, *pixel);
        }
    }
    SDL_UnlockSurface(mystruct->surface);
    SDL_UpdateWindowSurface(mystruct->my_window);
    
}