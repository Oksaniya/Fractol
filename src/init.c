#include "../inc/fractol.h"

void time_init(void)
{
    
}

void init(t_mystruct *mystruct, t_SDL_struct *SDL_struct)
{
    SDL_struct->my_window = NULL;
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
    SDL_struct->my_window = SDL_CreateWindow(mystruct->window_name, 
                                SDL_WINDOWPOS_CENTERED, 
                                SDL_WINDOWPOS_CENTERED, 
                                WINDOW_WIDTH, 
                                WINDOW_HEIGHT, 
                                SDL_WINDOW_ALLOW_HIGHDPI);

    if (SDL_struct->my_window == NULL)
    {
        fprintf(stderr, "could not create a window: %s\n", SDL_GetError());
        exit(1);
    }
    SDL_struct->surface = NULL;
    SDL_struct->surface = SDL_GetWindowSurface(SDL_struct->my_window);

    /* init surface with 0 */
    SDL_LockSurface(SDL_struct->surface);
    SDL_memset(SDL_struct->surface->pixels, 0, SDL_struct->surface->h * SDL_struct->surface->pitch);
    SDL_UnlockSurface(SDL_struct->surface);
    SDL_UpdateWindowSurface(SDL_struct->my_window);
}

void surface(t_mystruct *mystruct, t_pixel *pixel, t_SDL_struct *SDL_struct)
{
    SDL_LockSurface(SDL_struct->surface);
    for (int64_t x = 300; x < 450; x++)
    {
        for (int64_t y = 175; y < 325; y++)
        {
            set_pixel(SDL_struct->surface, x, y, *pixel);
        }
    }
    SDL_UnlockSurface(SDL_struct->surface);
    SDL_UpdateWindowSurface(SDL_struct->my_window);
    
}